<?php

/**
 * @file
 * Mica networks file
 */
class ObibaSearchResources extends MicaSearchResource {
  const MICA_REPOSITORY = 'mica/repository';
  var $last_reponse;
  private $result_resource_query;
  private $resource_query;

  function __construct($resource_query = NULL) {
    parent::__construct();
    $this->result_resource_query = NULL;
    $this->resource_query = $resource_query;
  }

  private function httpRequestGetBuilder($header_accept = parent::HEADER_JSON) {
    $resources = $this->resource_query;
    $url = $this->micaUrl . $resources;

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array($header_accept),
          'Content-Type' => array($header_accept)
        )
      )
    ));
    $client = $this->client();
    try {
      if (!isset($this->result_resource_query)) {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $array_response = json_decode($data);
        $this->result_resource_query = $array_response;
        obiba_mica_commons_set_cache($resources, $array_response);
      }
      return $this->result_resource_query;
    } catch (HttpClientException $e) {
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);
      $this->result_resource_query = NULL;
      return array();
    }
  }

  public function getCache() {
    $cached_result = obiba_mica_commons_get_cache($this->resource_query);
    if (!empty($cached_result)) {
      $this->result_resource_query = $cached_result->data;
    }
    return $this;
  }

  public function searchQuery() {
    return $this->httpRequestGetBuilder();
  }

  public function taxonomiesSearch() {
    return $this->httpRequestGetBuilder();
  }

  public function taxonomiesFilter() {
    return $this->httpRequestGetBuilder();
  }

  public function taxonomyFilter() {
    return $this->httpRequestGetBuilder();
  }

  public function variablesCoverage() {
    return $this->httpRequestGetBuilder();
  }

  public function variablesCoverageDownload($query, $header_accept) {
    $this->resource_query = '/variables/_coverage_download?query=' . $query;
    return $this->httpRequestGetBuilder($header_accept);
  }

  static function repositoryAnchor($url, $text, array $attributes, array $query_params) {
    $options = array();

    // Drupal may require css classes to be inside an array!
    if (!empty($attributes) && !empty($attributes['class'])) {
      $attributes['class'] = self::formatClassAsArray($attributes['class']);
    }

    if (!empty($attributes)) {
      $options['attributes'] = $attributes;
    }
    if (!empty($query_params)) {
      if (empty($query_params['query'])) {
        unset($query_params['query']);
      }
      $options['fragment'] = '/search?' . http_build_query($query_params);
    }
    return l($text, $url, $options);
  }

  /**
   * Format class as array.
   *
   * @param string $class
   *   A class to add.
   *
   * @return array
   *   A formatted class array.
   */
  public static function formatClassAsArray($class) {
    return is_array($class) ? $class : explode(' ', $class);
  }

  static function repositoryRqlBuilder($query = NULL, $bucket = NULL, $taxonomy_name = NULL, $vocabulary_name = NULL, $entity_id = NULL) {
    $query_search = '';
    if (!empty($taxonomy_name)) {
      if (!empty($vocabulary_name)) {
        $query_search = 'variable(and(exists(' . $taxonomy_name . '.' . $vocabulary_name . '),in(Mica_variable.';
      }
    }
    if (!empty($query)) {
      $query_search .= 'datasetId,' . $entity_id;
    }
    else {
      switch ($bucket->field) {
        case 'studyIds' :
          $query_search .= 'studyIds,' . $bucket->value;
          break;
        case 'dceIds' :
          $query_search .= 'dceIds,' . urlencode(urlencode($bucket->value));
      }
    }
    $query_search .= ')))&display=list&type=variables';
    return $query_search;
  }
}
