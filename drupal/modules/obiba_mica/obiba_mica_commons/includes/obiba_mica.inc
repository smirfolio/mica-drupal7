<?php

/**
 * @file
 * AgateClient class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'obiba_mica_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');
include_once("obiba_mica_commons_query_dto_builders.inc");
include_once("obiba_mica_commons_query_response_wrappers.inc");
include_once("obiba_mica_commons_resource_paths.inc");


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
  const PAGINATE_studies = 0;
  const PAGINATE_variables = 1;
  const PAGINATE_datasets = 2;
  const PAGINATE_networks = 3;

  protected $mica_url;

  private $lastResponse;
  private static $response_page_size_small = 10;
  private static $response_page_size = 20;


  /**
   * Mica client from a given url or from the one retrieved from 'mica_url' variable.
   * @param null $mica_url
   */
  public function __construct($mica_url = NULL) {
    $this->micaUrl = (isset($mica_url) ? $mica_url : variable_get_value('mica_url')) . '/ws';
    self::$response_page_size = variable_get_value('mica_response_page_size');
    self::$response_page_size_small = variable_get_value('mica_response_page_size_small');
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
      $headers = $this->addCookieHeader($headers, $_COOKIE[self::OBIBA_COOKIE], isset($_COOKIE[self::MICA_COOKIE]) ? $_COOKIE[self::MICA_COOKIE] : NULL);
    }
    else {
      watchdog('obiba_mica', 'Auth by anonymous credentials');

      if (isset($_SESSION[self::MICA_COOKIE])) {
        $headers = $this->addCookieHeader($headers, NULL, $_SESSION[self::MICA_COOKIE]);
      }

      $credentials = variable_get_value('mica_anonymous_name') . ':' . variable_get_value('mica_anonymous_password');
      $headers[self::AUTHORIZATION_HEADER] = array('Basic ' . base64_encode($credentials));
    }

    return $headers;
  }

  private function addCookieHeader(array $headers, $obibaid, $micasid) {
    $cookie = $this->cookieHeaderValue($obibaid, $micasid);

    if (isset($headers[self::COOKIE_HEADER])) {
      array_push($headers[self::COOKIE_HEADER], $cookie);
    }
    else {
      $headers[self::COOKIE_HEADER] = array($cookie);
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
    $cookie_parts = array();

    if (isset($obibaid)) {
      $cookie_parts[] = self::OBIBA_COOKIE . '=' . $obibaid;
    }

    if (isset($micasid)) {
      $cookie_parts[] = self::MICA_COOKIE . '=' . $micasid;
    }

    return implode("; ", $cookie_parts);
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
    $default_headers_setter = function ($request) {
      $request->setHeader('Accept-Encoding', 'gzip, deflate');
    };

    $client = new HttpClient(NULL, NULL, $default_headers_setter);

    if (!isset($client->options['curlopts'])) {
      $client->options['curlopts'] = array();
    }

    $client->options['curlopts'] += array(
      CURLOPT_SSL_VERIFYHOST => FALSE,
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_ENCODING => TRUE
    );

    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());

    return $client;
  }

  protected function session_facets_bucket_construction($facets_bucket) {
    $facets_buckets = array();
    foreach ($facets_bucket as $bucket) {
      $facets_buckets[$bucket->aggregation] = array(
        'title' => obiba_mica_commons_get_localized_field($bucket, 'title'),
        'key' => $bucket->aggregation,
        'aggs' => $bucket->aggregation,
        'dto' => $bucket
      );

      if (!empty($bucket->children)) {
        $children = array();
        foreach ($bucket->children as $child) {
          array_push($children, array(
            'title' => obiba_mica_commons_get_localized_field($child, 'title'),
            'key' => $child->aggregation,
            'aggs' => $child->aggregation,
            'dto' => $child
          ));
        }

        $facets_buckets[$bucket->aggregation]['children'] = $children;
      }
    }
    return $facets_buckets;
  }

  protected function session_facets_builder($aggregations) {
    $network_buckets = array();
    $study_buckets = array();
    $dataset_buckets = array();
    $variable_buckets = array();
    unset($_SESSION['variables']);
    unset($_SESSION['studies']);
    unset($_SESSION['datasets']);
    unset($_SESSION['networks']);
    $networkAggregations = NULL;
    foreach ($aggregations as $type_aggregations => $aggregation) {
      if ($type_aggregations == 'networkResultDto') {
        $_SESSION['networks']['aggregations'] = $aggregation->aggs;
        $_SESSION['networks']['aggregations']['total_hits'] = $aggregation->totalHits;
        $_SESSION['networks']['aggregations']['total_count'] = $aggregation->totalCount;
        $networkAggregations = array_filter($aggregation->aggs, function ($agg) {
          return $agg->aggregation === "networkId";
        });
        $network_buckets = $this->session_facets_bucket_construction($aggregation->aggs);
      }

      if ($type_aggregations == 'datasetResultDto') {
        if (!empty($aggregation->aggs)) {
          $dataset_buckets = $this->session_facets_bucket_construction($aggregation->aggs);
          $_SESSION['datasets']['aggregations'] = $aggregation->aggs;
        }
        $_SESSION['datasets']['aggregations']['total_hits'] = $aggregation->totalHits;
        $_SESSION['datasets']['aggregations']['total_count'] = $aggregation->totalCount;
      }

      if ($type_aggregations == 'variableResultDto') {
        if (!empty($aggregation->aggs)) {
          $filtered = self::filter_variable_aggregations($aggregation->aggs);
          self::order_facet_taxonomies($filtered, function ($value) {
            return empty($value->aggregation) ? $value : $value->aggregation;
          });
          $variable_buckets = $this->session_facets_bucket_construction($filtered);
        }
        $_SESSION['variables']['studies'] = array();
        $study_result = isset($aggregations->studyResultDto->{'obiba.mica.StudyResultDto.result'}) ? $aggregations->studyResultDto->{'obiba.mica.StudyResultDto.result'} : NULL;
        if (!empty($study_result) && (!empty($study_result->summaries) || !empty($study_result->digests))) {
          $_SESSION['variables']['studies'] = //
            empty($study_result->summaries) //
              ? $study_result->digests //
              : $study_result->summaries;
        }

        $dataset_result = isset($aggregations->datasetResultDto->{'obiba.mica.DatasetResultDto.result'}) ? $aggregations->datasetResultDto->{'obiba.mica.DatasetResultDto.result'} : NULL;
        $_SESSION['variables']['datasets'] = array();
        if (!empty($dataset_result) && (!empty($dataset_result->datasets) || !empty($dataset_result->digests))) {
          $_SESSION['variables']['datasets'] =
            empty($dataset_result->datasets)
              ? $dataset_result->digests
              : $dataset_result->datasets;
        }
        $_SESSION['variables']['aggregations'] = $aggregation->aggs;
        $_SESSION['variables']['aggregations']['total_hits'] = $aggregation->totalHits;
        $_SESSION['variables']['aggregations']['total_count'] = $aggregation->totalCount;
      }
      if ($type_aggregations == 'studyResultDto') {
        $study_buckets = $this->session_facets_bucket_construction(self::filter_study_aggregations($aggregation->aggs));
        if (!empty($aggregations->networkResultDto)) {
          $network_result = isset($aggregations->networkResultDto->{'obiba.mica.NetworkResultDto.result'}) ? $aggregations->networkResultDto->{'obiba.mica.NetworkResultDto.result'} : NULL;
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

        if (!empty($aggregations->datasetResultDto) && !empty($aggregations->datasetResultDto->aggs)) {
          $datasets_studyTableSstudyIdstudies_id_aggregations =
            $this->_get_aggregations_by_entity_dto($aggregations->datasetResultDto->aggs, 'studyTable-studyId');
          $_SESSION['studies']['studyTable-studyId'] = !empty($datasets_studyTableSstudyIdstudies_id_aggregations) ?
            $datasets_studyTableSstudyIdstudies_id_aggregations : NULL;
        }

        $_SESSION['studies']['aggregations'] = $aggregation->aggs;
        $_SESSION['studies']['aggregations']['total_hits'] = $aggregation->totalHits;
        $_SESSION['studies']['aggregations']['total_count'] = $aggregation->totalCount;
      }
    }

    // move some facets
    $_SESSION['variables']['facets-buckets'] = array_merge($dataset_buckets, $variable_buckets);
    $moved_facets = array_filter($_SESSION['variables']['facets-buckets'], function ($facet) {
      return $facet['key'] === 'studyIds' || $facet['key'] === 'dceIds';
    });

    foreach ($moved_facets as $key => $facet) {
      unset($_SESSION['variables']['facets-buckets'][$key]);
    }
    $_SESSION['studies']['facets-buckets'] = array_merge(array_merge($network_buckets, $moved_facets), $study_buckets);

    if (!empty($networkAggregations)) {
      foreach ($networkAggregations as $networkAggregation) {
        array_push($_SESSION['studies']['aggregations'], $networkAggregation);
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

  public static function getResponsePageSizeSmall() {
    return self::$response_page_size_small;
  }

  public static function getResponsePageSize() {
    $size = empty($_GET['size']) ? self::$response_page_size : $_GET['size'];
    return $size;
  }

  /**
   * Removes the flagged aggs from the UI only
   * @param $aggs
   * @return array
   */
  private static function filter_variable_aggregations($aggs) {
    $filters = NULL;
    if (variable_get_value('search_datasets_autocomplete') == ObibaDatasetConstants::FACET_TYPE_HIDE) {
      $filters[] = "datasetId";
    }

    if (!variable_get_value('search_studies_dce_autocomplete')) {
      $filters[] = "dceIds";
    }

    return empty($filters) ? $aggs : array_filter($aggs, function ($agg) use ($filters) {
      return FALSE === array_search($agg->aggregation, $filters);
    });
  }

  /**
   * Removes the flagged aggs from the UI only
   * @param $aggs
   * @return array
   */
  private static function filter_study_aggregations($aggs) {
    $filters = NULL;
    if (!variable_get_value('search_general_population_sources_autocomplete')) {
      $filters[] = "populations-recruitment-generalPopulationSources";
    }

    return empty($filters) ? $aggs : array_filter($aggs, function ($agg) use ($filters) {
      return FALSE === array_search($agg->aggregation, $filters);
    });
  }

  public static function get_taxonomies_count() {
    return count(self::get_taxonomies_as_array(variable_get_value('mica_taxonomy_order')));
  }

  /**
   * Orders the matching taxonomies by based on the order defind in 'mica_taxonomy_order'
   * @param $taxonomies
   * @param $getter
   */
  public static function order_taxonomies(&$taxonomies, $getter) {
    $order_taxonomy_variable = variable_get_value('mica_taxonomy_order');

    if (!empty($taxonomies) && !empty($order_taxonomy_variable)) {
      $ordered_taxonomies = self::get_taxonomies_as_array($order_taxonomy_variable);

      $taxonomies = array_map(function ($n) use ($taxonomies, $getter) {
        $tmp = array_filter($taxonomies, function ($t) use ($n, $getter) {
          return $getter($t) === $n;
        });

        return reset($tmp);
      }, $ordered_taxonomies);

      $taxonomies = array_filter($taxonomies, function ($t) {
        return !empty($t);
      });
    }
  }

  public static function order_facet_taxonomies(&$taxonomies, $getter) {
    $order_taxonomy_variable = variable_get_value('mica_taxonomy_order');

    if (!empty($taxonomies) && !empty($order_taxonomy_variable)) {
      $ordered_taxonomies = self::get_taxonomies_as_array($order_taxonomy_variable);

      $taxonomies = array_filter($taxonomies, function ($taxonomy) use ($ordered_taxonomies, $getter) {
        return empty($taxonomy->children) || FALSE !== array_search($getter($taxonomy), $ordered_taxonomies);
      });

      $max_size = count($ordered_taxonomies);
      $indexes = array_fill(0, $max_size, NULL);
      $values = array_fill(0, $max_size, NULL);

      foreach ($taxonomies as $index => $value) {
        $position = array_search($getter($value), $ordered_taxonomies);
        if ($position !== FALSE) {
          $indexes[$position] = $index;
          $values[$position] = $value;
        }
      }

      // compact the index and value arrays by removing padding value -9999
      $indexes = array_filter($indexes, function ($e) {
        return $e !== NULL;
      });

      $values = array_filter($values, function ($e) {
        return $e !== NULL;
      });

      asort($indexes);

      // place the values at the proper position
      while (count($indexes) > 0) {
        $taxonomies[array_pop($indexes)] = array_pop($values);
      }
    }
  }

  static private function get_taxonomies_as_array($taxonomies) {
    return empty($taxonomies) ? array() : explode(',', preg_replace('/\s*,\s*/', ',', trim($taxonomies)));
  }

  static function get_name_entity_by_id_aggregation($type, $aggregation_facet, $id) {
    foreach ($_SESSION[$type][$aggregation_facet] as $entity) {
      if ($entity->id == $id) {
        return obiba_mica_commons_get_localized_field($entity, 'name');
      }
    }

    return NULL;
  }

  static function has_entity_aggregations($entity) {
    return !empty($entity->{'obiba.mica.TermsAggregationResultDto.terms'})
    || !empty($entity->{'obiba.mica.StatsAggregationResultDto.stats'});
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

  static function obiba_mica_search_get_item_count($type, $aggregation_facet, $id) {
    if (!empty($_SESSION[$type][$aggregation_facet])) {
      foreach ($_SESSION[$type][$aggregation_facet] as $value) {
        if ($value->key == $id) {
          return $value->count;
        }
      }
    }
    return NULL;
  }

  public function pagination_list_search_parameters($current_page = 0, $type = NULL, $size = NULL) {
    return self::next_page_offset( //
      empty($current_page) ? 0 : $current_page, //
      empty($size) ? MicaClient::getResponsePageSize() : $size, //
      $_SESSION[strtolower($type)]['aggregations']['total_hits'] //
    );
  }

  static function next_page_offset($current_page = 0, $size, $total) {
    $nb_pages = ceil($total / $size);

    $from = 0;
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) {
        $pageActuelle = $nb_pages;
      }

      $from = ($pageActuelle) * $size;
    }

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
  protected function dto_filter_construct($type, $request_param = NULL, $from = 0, $group_by = NULL, $withFacets = TRUE) {
    global $language;
    $lang = $language->language;
    $page_size = MicaClient::getResponsePageSize();
    $queryDtoBuilder = JoinQueryDtoBuilder::newBuilder(json_decode($request_param), $page_size, $lang, $withFacets);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json);
    $json_query_encoded = //
      Protobuf::encode($queryDtoBuilder->documentQuery($type, $from, $page_size, $group_by)->build());

    return $json_query_encoded;
  }

  /**
   * Merge any associative array query parameters to current json parameter
   * @param array|associative $param_to_add associative array of param to add array('variables' =>array('terms'=>array('studyIds'=>'clsa-elcv-1')))
   * @return string
   */
  static function add_parameter_dto_query_link(array $param_to_add) {
    $url_parm = explode('?', request_uri());
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

        if (!empty($array_current_query->{$entity_name}->terms->{$term_name}) &&
          empty($array_current_query->{$entity_name}->terms->{$term_name}->{'op'})
        ) {
          $array_current_query->{$entity_name}->terms->{$term_name}->{'op'} = 'and';
        }
      }
    }
  }

  public static function concatenate_parameter_terms($array_query, $param_to_add) {
    foreach ($param_to_add as $entity_name => $entity) {
      foreach ($entity['terms'] as $term_name => $term_value) {
        $term_values = array($term_value);
        if (is_array($term_value)) {
          $term_values = $term_value;
        }
        foreach ($term_values as $value) {
          if (empty($array_query->{$entity_name}->terms->{$term_name}) //
            || !in_array($value, $array_query->{$entity_name}->terms->{$term_name}->values)
          ) { //

            $array_query->{$entity_name}->terms->{$term_name}->values[] = $value;
          }
        }

        if (!empty($array_query->{$entity_name}->terms->{$term_name}) &&
          empty($array_query->{$entity_name}->terms->{$term_name}->{'op'})
        ) {
          $array_query->{$entity_name}->terms->{$term_name}->{'op'} = 'and';
        }
      }
    }
    return $array_query;
  }

  public static function chart_query_builders($query = NULL, $bucket = NULL, $taxonomy_name = NULL, $vocabulary_name = NULL, $terms = NULL) {
    $parameters = array();
    $current_path_alias = drupal_get_path_alias();
    $common_param =
      array(
        'variables' => array(
          'terms' => array(
            'attributes-'
            . $taxonomy_name . '__' .
            $vocabulary_name . '-und' => $terms
          )
        )
      );
    if (!empty($query)) {
      return json_encode(MicaClient::concatenate_parameter_terms(json_decode($query), $common_param));
    }
    if (strpos($current_path_alias, 'network')) {
      $parameters = array(
        'studies' => array(
          'terms' => array(
            $bucket->field => $bucket->value,
          )
        )
      );
    }
    if (strpos($current_path_alias, 'study')) {
      $parameters = array(
        'studies' => array(
          'terms' => array(
            'studyIds' => arg(2, $current_path_alias)
          )
        )
      );
    }
    $term_param = array_merge($parameters, $common_param);
    return MicaClient::add_parameter_dto_query_link($term_param);

  }

  /**
   * Parse a string header response and return an key/value array attributes
   * @param $raw_headers
   * @return array
   */
  private function parse_headers($raw_headers) {
    $headers = [];

    foreach (explode("\n", $raw_headers) as $i => $h) {
      $h = explode(':', $h, 2);

      if (isset($h[1])) {
        $headers[$h[0]] = trim($h[1]);
      }
    }

    return $headers;
  }

  /**
   * get property by given attribute
   * @param $attribute
   * @param $property
   * @return bool|mixed
   */
  private function parse_header($attribute, $property) {
    $attributes_array = explode(';', $attribute);
    foreach ($attributes_array as $property_string) {
      if (strstr($property_string, $property)) {
        return $property_value = str_replace('"', '', explode('=', $property_string)[1]);
      }
    }
    return FALSE;
  }

  /**
   * return the value of a given key header attribute  (filename, charset)
   * ToDo may be need to be extended to retrieve more attributes (User-Agent, ...)
   * @param $header
   * @param $property
   * @param null $attribute
   * @return bool|mixed|null
   */
  private function get_property_value_from_header_array($header, $property, $attribute = NULL) {
    if (!empty($attribute)) {
      return $this->parse_header($header[$attribute], $property);
    }
    else {
      foreach ($header as $attributes) {
        $find_property_value = $this->parse_header($attributes, $property);
        if (!empty($find_property_value)) {
          return $find_property_value;
        }
      }
    }
    return NULL;
  }

  /**
   * @param $file_resource
   * @return mixed
   */
  private function get_file_extension($file_resource) {
    $file_array = explode('.', $file_resource);
    $extension_file = count($file_array);

    return $file_array[$extension_file - 1];
  }

  /**
   * Deal with downloadable resources from server (Images, attachments)
   * @param:  $entity_type, $entity_id, $file_id
   * @return : an array containing :
   *            data : The raw file to download
   *            filename : The real file name of the file
   *            raw_header_array : the raw of header response
   *           or in case of error
   *            code : the error code
   *            message : the error message
   * */
  public function download_file($entity_type, $entity_id, $file_id) {
    $url = $this->micaUrl . "/" . $entity_type . "/" . $entity_id . "/file/" . $file_id . "/_download";
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => self::authorizationHeader(array(
            'Accept' => array(self::HEADER_BINARY),
          )
        ),
    ));

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      $file_name = $this->get_property_value_from_header_array($this->parse_headers($client->lastResponse->headers),
        'filename',
        'Content-Disposition'
      );

      $raw_data = array(
        'extension' => $this->get_file_extension($file_name),
        'data' => $data,
        'filename' => $file_name,
        'raw_header_array' => $this->parse_headers($client->lastResponse->headers)
      );
      return $raw_data;
    }
    catch (HttpClientException $e) {
      watchdog('MicaTaxonomyResource', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return $raw_data = array(
        'code' => $e->getCode(),
        'message' => $e->getMessage()
      );
    }

  }

}
