<?php

/**
 * @file
 * AgateClient class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'mica_client_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');
include_once("mica_client_commons_query_dto_builders.inc");
include_once("mica_client_commons_query_response_wrappers.inc");
include_once("mica_client_commons_resource_paths.inc");

/**
 * Class MicaClient
 */
class MicaClient {
  const AUTHORIZATION_HEADER = 'Authorization';

  const COOKIE_HEADER = 'Cookie';

  const SET_COOKIE_HEADER = 'Set-Cookie';

  const OBIBA_COOKIE = 'obibaid';

  const MICA_COOKIE = 'micasid';

  const HEADER_BINARY = 'application/x-protobuf';

  const HEADER_JSON = 'application/json';

  const HEADER_CSV = 'text/csv';

  const SIZE_RESPONSE = 20;

  const PAGINATE_studies = 0;
  const PAGINATE_variables = 1;
  const PAGINATE_datasets = 2;
  const PAGINATE_networks = 3;

  protected $micaUrl;

  private $lastResponse;

  /**
   * Mica client from a given url or from the one retrieved from 'mica_url' variable.
   * @param null $mica_url
   */
  public function __construct($mica_url = NULL) {
    $this->micaUrl = (isset($mica_url) ? $mica_url : variable_get_value('mica_url')) . '/ws';
  }

  /**
   * Get the last response (if any).
   * @return mixed
   */
  public function getLastResponse() {
    return $this->lastResponse;
  }

  /**
   * Set the last response after a http call.
   * @param $lastResponse
   */
  protected function setLastResponse($lastResponse) {
    $this->lastResponse = $lastResponse;
    if (isset($lastResponse)) {
      $this->setLastResponseCookies();
    }
  }

  /**
   * Get the last response headers (if any).
   * @return array
   */
  public function getLastResponseHeaders() {
    if ($this->lastResponse != NULL) {
      $result = array();
      foreach (explode("\r\n", $this->lastResponse->headers) as $header) {
        $h = explode(":", $header, 2);
        if (count($h) == 2) {
          if (!array_key_exists($h[0], $result)) {
            $result[$h[0]] = array();
          }
          array_push($result[$h[0]], trim($h[1]));
        }
      }
      return $result;
    }
    return '';
  }

  /**
   * Get the header value(s) from the last response.
   * @param $header_name
   * @return array
   */
  protected function getLastResponseHeader($header_name) {
    $headers = $this->getLastResponseHeaders();

    if (array_key_exists($header_name, $headers)) {
      return $headers[$header_name];
    }
    return array();
  }

  /**
   * Forwards the 'Set-Cookie' directive(s) to the drupal client if the user was authenticated by Agate.
   */
  private function setLastResponseCookies() {
    foreach ($this->getLastResponseHeader(self::SET_COOKIE_HEADER) as $cookie_str) {
      $cookie = $this->parseCookie($cookie_str);
      $keys = array_keys($cookie);
      $name = $keys[0];
      $value = $cookie[$name];
      $expire = isset($cookie['Max-Age']) ? time() + intval($cookie['Max-Age']) : 0;
      $path = isset($cookie['Path']) ? $cookie['Path'] : '/';
      $domain = isset($cookie['Domstudyain']) ? $cookie['Domain'] : NULL;

      if (isset($_COOKIE[self::OBIBA_COOKIE])) {
        // forwards cookies to client if not anonymous user
        setcookie($name, $value, $expire, $path, $domain);
      }
      $_SESSION[$name] = $value;
    }
  }

  /**
   * Add authorization headers
   * @param array $headers
   * @return array
   */
  protected function authorizationHeader(array $headers) {
    if (isset($_COOKIE[self::OBIBA_COOKIE])) {
      // authenticate by cookies coming from request (case of regular user logged in via Agate)
      watchdog('obiba_mica', 'Auth by cookies from request');
      $obibaid = $_COOKIE[self::OBIBA_COOKIE];
      $micasid = isset($_COOKIE[self::MICA_COOKIE]) ? $_COOKIE[self::MICA_COOKIE] : NULL;
      $cookie = $this->cookieHeaderValue($obibaid, $micasid);

      if (isset($headers[self::COOKIE_HEADER])) {
        array_push($headers[self::COOKIE_HEADER], $cookie);
      }
      else {
        $headers[self::COOKIE_HEADER] = array($cookie);
      }
    }
    else {
      // authenticate by anonymous credentials
      watchdog('obiba_mica', 'Auth by anonymous credentials');
      $credentials = variable_get_value('mica_anonymous_name') . ':' . variable_get_value('mica_anonymous_password');
      $headers[self::AUTHORIZATION_HEADER] = array('Basic ' . base64_encode($credentials));
    }

    return $headers;
  }

  /**
   * Add authorization by cookies header.
   * @param $obibaid
   * @param $micasid
   * @internal param array $headers
   * @return string
   */
  private function cookieHeaderValue($obibaid, $micasid) {
    $cookie = self::OBIBA_COOKIE . '=' . $obibaid;

    if (isset($micasid)) {
      $cookie = $cookie . '; ' . self::MICA_COOKIE . '=' . $micasid;
    }

    return $cookie;
  }

  /**
   * Explode a cookie string in a array.
   * @param $cookie_str
   * @return array
   */
  private function parseCookie($cookie_str) {
    $cookie = array();
    foreach (explode(';', $cookie_str) as $entry_str) {
      $entry = explode('=', $entry_str);
      $cookie[$entry[0]] = $entry[1];
    }
    return $cookie;
  }

  /**
   * @return HttpClient
   */
  protected function client() {
    $client = new HttpClient($formatter = FALSE);

    if (!isset($client->options['curlopts'])) {
      $client->options['curlopts'] = array();
    }

    $client->options['curlopts'] += array(
      CURLOPT_SSLVERSION => 3,
      CURLOPT_SSL_VERIFYHOST => FALSE,
      CURLOPT_SSL_VERIFYPEER => FALSE
    );

    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());

    return $client;
  }


  protected function session_facets_builder($aggregations) {
    unset($_SESSION['variables']);
    unset($_SESSION['studies']);
    foreach ($aggregations as $type_aggregations => $aggregation) {
      if ($type_aggregations == 'variableResultDto') {
        $_SESSION['variables']['studies'] = array();
        $study_result = $aggregations->studyResultDto->{'obiba.mica.StudyResultDto.result'};
        if (!empty($study_result) && (!empty($study_result->summaries) || !empty($study_result->digests))) {
          $_SESSION['variables']['studies'] = //
            empty($study_result->summaries) //
              ? $study_result->digests //
              : $study_result->summaries;
        }

        $dataset_result = $aggregations->datasetResultDto->{'obiba.mica.DatasetResultDto.result'};
        $_SESSION['variables']['datasets'] = array();
        if (!empty($dataset_result) && (!empty($dataset_result->datasets) || !empty($dataset_result->digests))) {
          $_SESSION['variables']['datasets'] =
            empty($dataset_result->datasets)
              ? $dataset_result->digests
              : $dataset_result->datasets;
        }
        $_SESSION['variables']['aggregations'] = $aggregation->aggs;
        $_SESSION['variables']['aggregations']['totalHits'] = $aggregation->totalHits;
        $_SESSION['variables']['aggregations']['totalCount'] = $aggregation->totalCount;
      }
      if ($type_aggregations == 'studyResultDto') {
        if (!empty($aggregations->networkResultDto)) {
          $network_result = $aggregations->networkResultDto->{'obiba.mica.NetworkResultDto.result'};
          if (!empty($network_result) && (!empty($network_result->networks) || !empty($network_result->digests))) {
            $_SESSION['studies']['networks'] = array();
            $_SESSION['studies']['networks'] =
              empty($network_result->digests)
                ? $network_result->networks
                : $network_result->digests;
          }
        }

        if (!empty($aggregations->variableResultDto)) {
          $variable_studies_id_aggregations =
            $this->_get_aggregations_by_entity_dto($aggregations->variableResultDto->aggs, 'studyIds');
          $_SESSION['studies']['variables'] = !empty($variable_studies_id_aggregations) ?
            $variable_studies_id_aggregations : NULL;
        }

        if (!empty($aggregations->networkResultDto)) {
          $networks_studies_id_aggregations =
            $this->_get_aggregations_by_entity_dto($aggregations->networkResultDto->aggs, 'studyIds');
          $_SESSION['studies']['networks-studyId'] = !empty($networks_studies_id_aggregations) ?
            $networks_studies_id_aggregations : NULL;
        }

        if (!empty($aggregations->datasetResultDto)) {
          $datasets_studyTableSstudyIdstudies_id_aggregations =
            $this->_get_aggregations_by_entity_dto($aggregations->datasetResultDto->aggs, 'studyTable-studyId');
          $_SESSION['studies']['studyTable-studyId'] = !empty($datasets_studyTableSstudyIdstudies_id_aggregations) ?
            $datasets_studyTableSstudyIdstudies_id_aggregations : NULL;
        }

        $_SESSION['studies']['aggregations'] = $aggregation->aggs;
        $_SESSION['studies']['aggregations']['totalHits'] = $aggregation->totalHits;
        $_SESSION['studies']['aggregations']['totalCount'] = $aggregation->totalCount;
      }
    }
  }

  protected function _get_aggregations_by_entity_dto($entity_aggr, $aggregations_term) {
    foreach ($entity_aggr as $agg) {
      if ($agg->aggregation == $aggregations_term && !empty($agg->{'obiba.mica.TermsAggregationResultDto.terms'})) {

        return $agg->{'obiba.mica.TermsAggregationResultDto.terms'};
      }
    }
    return NULL;
  }

  static function get_name_entity_by_id_aggregation($type, $aggregation_facet, $id) {
    foreach ($_SESSION[$type][$aggregation_facet] as $entity) {
      if ($entity->id == $id) {
        return mica_client_commons_get_localized_field($entity, 'name');
      }
    }

    return NULL;
  }

  static function has_entity_by_id_aggregation($facet) {
    if (!empty($_SESSION['studies']['aggregations'])) {
      foreach ($_SESSION['studies']['aggregations'] as $entity) {
        if (!empty($entity->aggregation) && $entity->aggregation == $facet) {
          if (!empty($entity->{'obiba.mica.TermsAggregationResultDto.terms'}) ||
            !empty($entity->{'obiba.mica.StatsAggregationResultDto.stats'})
          ) {
            return TRUE;
          }
          else {
            return FALSE;
          }
        }
      }
    }
    if (!empty($_SESSION['variables']['aggregations'])) {
      foreach ($_SESSION['variables']['aggregations'] as $entity) {
        if (!empty($entity->aggregation) && $entity->aggregation == $facet) {
          if (!empty($entity->{'obiba.mica.TermsAggregationResultDto.terms'})) {
            return TRUE;
          }
          else {
            return FALSE;
          }
        }
      }
    }
    return FALSE;
  }

  static function mica_client_facet_search_get_item_count($type, $aggregation_facet, $id) {
    if (!empty($_SESSION[$type][$aggregation_facet])) {
      foreach ($_SESSION[$type][$aggregation_facet] as $value) {
        if ($value->key == $id) {
          return $value->count;
        }
      }
    }
    return NULL;
  }

  public function pagination_list_search_parameters($current_page = 0, $type = NULL, $size = self::SIZE_RESPONSE) {
    $nb_pages = ceil($_SESSION[strtolower($type)]['aggregations']['totalHits'] / $size);
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) {
        $pageActuelle = $nb_pages;
      }
    }
    else {
      $pageActuelle = 1;
    }
    $from = ($pageActuelle) * $size;
    return $from;
  }

  /**
   * Dto filter construction
   * @param $type
   * @param null $request_param url passed parameters,
   * @param $from
   * @internal param null $hierarchical_relation
   * @internal param null $type_dto_search must be 'study' or 'dataset',
   * @internal param null $spec_dto_params specific passed parameters,
   * @internal param null $size number of results
   * @internal param null $parent_child array must be 'parent'=>'<entity parent>' or 'child'=>'<entity parent>',
   * @return string
   */
  protected function dto_filter_construct($type, $request_param = NULL, $from = 0, $group_by = NULL) {
    if ($from == 0) {
      unset($_COOKIE['page_' . $type]);
      setcookie('page_' . $type, 0, time() - 3600); // empty value and old timestamp
    }
    else {
      setcookie('page_' . $type, $_GET['page'], time() + 3600 * 24 * 180);
    }

    global $language;
    $lang = $language->language;
    $queryDtoBuilder = JoinQueryDtoBuilder::newBuilder(json_decode($request_param), $this::SIZE_RESPONSE, $lang);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json);
    $json_query_encoded = //
      Protobuf::encode($queryDtoBuilder->documentQuery($type, $from, $this::SIZE_RESPONSE, $group_by)->build());

    return $json_query_encoded;
  }

  /**
   * Merge any associative array query parameters to current json parameter
   * @param array|associative $param_to_add associative array of param to add array('variables' =>array('terms'=>array('studyIds'=>'clsa-elcv-1')))
   * @return string
   */
  static function add_parameter_dto_query_link(array $param_to_add) {
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    if (!empty($url_parm[1])) {
      parse_str($url_parm[1], $parts);
      if (!empty($parts['query'])) {
        $array_current_query = json_decode($parts['query']);
      }
      else {
        $array_current_query = new stdClass();
      }
      MicaClient::add_parameter_terms($array_current_query, $param_to_add);
      return json_encode($array_current_query);
    }
    else {
      $array_current_query = new stdClass();
    }
    MicaClient::add_parameter_terms($array_current_query, $param_to_add);
    return json_encode($array_current_query);
  }

  public static function create_query_dto_as_string($param_to_add) {
    return json_encode(MicaClient::create_query_dto($param_to_add));
  }

  public static function create_query_dto($param_to_add) {
    $query = new stdClass();
    MicaClient::add_parameter_terms($query, $param_to_add);
    return $query;
  }

  public static function add_parameter_terms($array_current_query, $param_to_add) {
    foreach ($param_to_add as $entity_name => $entity) {
      foreach ($entity['terms'] as $term_name => $term_value) {
        $term_values = array($term_value);
        if (is_array($term_value)) {
          $term_values = $term_value;
        }
        foreach ($term_values as $value) {
          if (empty($array_current_query->{$entity_name}->terms->{$term_name}) //
            || !in_array($value, $array_current_query->{$entity_name}->terms->{$term_name}->values)
          ) { //

            $array_current_query->{$entity_name}->terms->{$term_name}->values[] = $value;
          }
        }

        if (empty($array_current_query->{$entity_name}->terms->{$term_name}->{'op'})) {
          $array_current_query->{$entity_name}->terms->{$term_name}->{'op'} = 'and';
        }
      }
    }
  }
}