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
include_once("mica_client_facet_search_query_dto_builders.inc");

/**
 * Class MicaClient
 */
class MicaClient {
  const child = \obiba\mica\ParentChildFilterDto\Relationship::CHILD;
  const parent = \obiba\mica\ParentChildFilterDto\Relationship::PARENT;
  const AUTHORIZATION_HEADER = 'Authorization';

  const COOKIE_HEADER = 'Cookie';

  const SET_COOKIE_HEADER = 'Set-Cookie';

  const OBIBA_COOKIE = 'obibaid';

  const MICA_COOKIE = 'micasid';

  const HEADER_BINARY = 'application/x-protobuf';

  const HEADER_JSON = 'application/json';

  const SIZE_RESPONSE = 30;

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
  protected function getLastResponseHeaders() {
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
   * @param array $headers
   * @param $obibaid
   * @param $micasid
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


  protected function session_facets_builder($aggregations, $request_param = NULL) {
    foreach ($aggregations as $type_aggregations => $aggregation) {
      if (!empty($aggregation->totalHits)) {
        if ($type_aggregations == 'variableResultDto') {
          $_SESSION['variables']['studies'] = $aggregations->studyResultDto->{'obiba.mica.StudyResultDto.result'}->summaries;
          $_SESSION['variables']['datasets'] = $aggregations->datasetResultDto->{'obiba.mica.DatasetResultDto.result'}->datasets;
          $_SESSION['variables']['aggregations'] = $aggregation->aggs;
          $_SESSION['variables']['aggregations'][] = $aggregation->aggs;
          $_SESSION['variables']['aggregations']['totalHits'] = $aggregation->totalHits;
          $_SESSION['variables']['aggregations']['totalCount'] = $aggregation->totalCount;
          $_SESSION['variables']['request'] = !empty($request_param) ? $request_param : NULL;
        }

        if ($type_aggregations == 'studyResultDto') {
          $_SESSION['studies']['networks'] =
            !empty($aggregations->networkResultDto->{'obiba.mica.NetworkResultDto.result'}->networks) ?
              $aggregations->networkResultDto->{'obiba.mica.NetworkResultDto.result'}->networks : NULL;
          $_SESSION['studies']['aggregations'] = $aggregation->aggs;
          $_SESSION['studies']['aggregations']['totalHits'] = $aggregation->totalHits;
          $_SESSION['studies']['aggregations']['totalCount'] = $aggregation->totalCount;
          $_SESSION['studies']['request'] = !empty($request_param) ? $request_param : NULL;
        }
      }
    }
  }

  static function get_name_entity_by_id_aggregation($type, $agregation_facet, $id) {
    foreach ($_SESSION[$type][$agregation_facet] as $entity) {
      if ($entity->id == $id) {
        // dpm(mica_client_commons_get_localized_field($dataset,'name'));
        return mica_client_commons_get_localized_field($entity, 'name');
      }
    }
//dpm($type);
//dpm($id);

    return NULL;
  }

  static function normalize_parameters($request_param) {
    $requestArry = explode('&', $request_param);

    $formated_term = array();
    foreach ($requestArry as $term_association) {
      $term = explode('=', $term_association);
      if (!empty($term[1])) {

        if (strstr($term[0], '-range')) {
          $decoded_term = str_replace('-range[]', '', $term[0]);
          $decoded_term = $decoded_term . '-range';
          $vals = explode('to', $term[1]);
          $termval['min'] = preg_replace('/^[^\[]*\[\s*/', '', trim($vals[0]));
          $termval['max'] = str_replace(']', '', trim($vals[1]));
          $formated_term[preg_replace('/\[[^\]]*\]/', '', $decoded_term)] = $termval;
        }
        else {
          $term[0] = $term[0] . '-terms';
          $decoded_term = urldecode($term[0]);
          $formated_term[preg_replace('/\[[^\]]*\]/', '', $decoded_term)][] = $term[1];
        }
      }
    }
//dpm(json_encode($formated_term));
    return $formated_term;
  }

  public function pagination_parameters($current_page = NULL, $dto_type = NULL) {
    $nb_pages = ceil($_SESSION[strtolower($dto_type)]['aggregations']['totalHits'] / $this::SIZE_RESPONSE);
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) // Si la valeur de $pageActuelle (le numéro de la page) est plus grande que $nombreDePages...
      {
        $pageActuelle = $nb_pages;
      }
    }
    else {
      $pageActuelle = 1; // La page actuelle est la n°1
    }
    $premiereEntree = ($pageActuelle) * $this::SIZE_RESPONSE; // On calcul la première entrée à lire
    return $premiereEntree;
  }

  public function pagination_list_searcch_parameters($current_page = NULL, $type = NULL) {
    $nb_pages = ceil($_SESSION[strtolower($type)]['aggregations']['totalHits'] / 5);
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) // Si la valeur de $pageActuelle (le numéro de la page) est plus grande que $nombreDePages...
      {
        $pageActuelle = $nb_pages;
      }
    }
    else {
      $pageActuelle = 1; // La page actuelle est la n°1
    }
    $premiereEntree = ($pageActuelle) * 5; // On calcul la première entrée à lire
    return $premiereEntree;
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
  protected function dto_filter_construct($type, $request_param = NULL, $from = 0) {

    if (!empty($request_param)) {
      $queryDtoBuilder = JoinQueryDtoBuilder::newBuilder(json_decode($request_param), $this::SIZE_RESPONSE);

      Protobuf::setDefaultCodec(new Protobuf\Codec\Json);
      $json_query_encoded = //
        Protobuf::encode($queryDtoBuilder->documentQuery($type, $from, $this::SIZE_RESPONSE)->build());

      return $json_query_encoded;
    }
  }


  protected function _construct_filtered_query_dto($parent_child_field, $term_association) {
    if (!is_numeric(key($term_association))) {
      $filter_query_dto_relational_range = new \obiba\mica\FilterQueryDto;
      $filter_query_dto_relational_range->setField(str_replace('-', '.', $parent_child_field[1]));
      $range_filter_dto = new \obiba\mica\RangeFilterQueryDto;

      if (!empty($term_association['min'])) {
        $conditionmin = new \obiba\mica\RangeConditionDto;

        $conditionmin->setOp(\obiba\mica\RangeConditionDto\Operator::GTE);
        $conditionmin->setValue(trim($term_association['min']));
        $range_filter_dto->setFrom($conditionmin);
      }
      if (!empty($term_association['max'])) {
        $conditionmax = new \obiba\mica\RangeConditionDto;
        $conditionmax->setOp(\obiba\mica\RangeConditionDto\Operator::LTE);
        $conditionmax->setValue(trim($term_association['max']));
        $range_filter_dto->setTo($conditionmax);
      }

      $filter_query_dto_relational_range->setExtension("obiba.mica.RangeFilterQueryDto.range", $range_filter_dto);
      return $filter_query_dto_relational_range;
    }

    else {
      $filter_query_dto_relational = new \obiba\mica\FilterQueryDto;
      $filter_query_dto_relational->setField(str_replace('-', '.', $parent_child_field[1]));
      $terms_filter_dto = new \obiba\mica\TermsFilterQueryDto;
      foreach ($term_association as $term) {
        $terms_filter_dto->addValues(str_replace($parent_child_field[1] . '.', '', $term));
      }
      $filter_terms = $filter_query_dto_relational->setExtension("obiba.mica.TermsFilterQueryDto.terms", $terms_filter_dto);
      return $filter_terms;

    }


  }

}