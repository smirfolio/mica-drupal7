<?php

/**
 * @file
 * Mica networks file
 */
class ObibaSearchResources extends MicaSearchResource {
  const MICA_REPOSITORY = 'mica/repository';
  var $last_reponse;

  function __construct() {
    parent::__construct();
  }

  private function httpRequestGetBuilder($resources, $header_accept = parent::HEADER_JSON) {
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
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return json_decode($data);
    }
    catch (HttpClientException $e) {
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);
      dpm($e->getMessage());
      return array();
    }
  }

  private function queryLocalBuilder($query) {

  }

  public function searchQuery($type, $query) {
    $this->queryLocalBuilder($query);
    return $this->httpRequestGetBuilder('/' . $type . '/_rql?query=' . $query);
  }

  public function taxonomiesSearch($query) {
    return $this->httpRequestGetBuilder('/taxonomies/_search?query=' . $query);
  }

  public function taxonomiesFilter($entity) {
    return $this->httpRequestGetBuilder('/taxonomies/_filter?target=' . $entity);
  }

  public function taxonomyFilter($name, $entity) {
    return $this->httpRequestGetBuilder('/taxonomy/' . $name . '/_filter?target=' . $entity);
  }

  public function variablesCoverage($query) {
    return $this->httpRequestGetBuilder('/variables/_coverage?query=' . $query);
  }

  public function variablesCoverageDownload($query, $header_accept) {
    return $this->httpRequestGetBuilder('/variables/_coverage_download?query=' . $query, $header_accept);
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
//    dpm($bucket);
//    dpm($taxonomy_name);
//    dpm($vocabulary_name);
//    dpm($entity_id);
    $query_search='';
    if (!empty($taxonomy_name)) {
      if (!empty($vocabulary_name)) {
        $query_search = 'variable(and(exists(' . $taxonomy_name . '.' . $vocabulary_name . '),in(Mica_variable.';
      }
    }
    if (!empty($query)) {
      $query_search .= 'datasetId,'. $entity_id;
    }
    else {
      switch ($bucket->field) {
        case 'studyIds' :
          $query_search .= 'studyIds,'. $bucket->value;
          break;
        case 'dceIds' :
          $query_search .= 'dceIds,' . urlencode(urlencode($bucket->value));
      }
    }
    $query_search .= ')))&display=list&type=variables';
    return $query_search;
  }
}
