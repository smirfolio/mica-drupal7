<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Mica networks file
 */
class ObibaSearchResources extends MicaClient {
  const MICA_REPOSITORY = 'mica/repository';

  function __construct() {
    parent::__construct();
    $this->result_resource_query = NULL;
  }

  private function httpRequestGetBuilder($resources, $header_accept = parent::HEADER_JSON) {
    if (!isset($this->result_resource_query)) {
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
        $array_response = json_decode($data);
        $this->result_resource_query = $array_response;
        obiba_mica_commons_set_cache($resources, $array_response);
        return $this->result_resource_query;
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
        $this->result_resource_query = NULL;
        return array();
      }
    }
    return $this->result_resource_query;
  }

  public function searchQuery($type, $query) {
    $resource = '/' . $type . '/_rql?query=' . $query;
    return $this->getCache($resource)->httpRequestGetBuilder($resource);
  }

  public function taxonomiesSearch($query, $target, $locale) {
    $resource = '/taxonomies/_search?query=' . rawurlencode($query)
      . (!empty($target) ? '&target=' . $target : '')
      . (!empty($locale) ? '&locale=' . $locale : '');
    return $this->getCache($resource)->httpRequestGetBuilder($resource);
  }

  public function taxonomiesFilter($target) {
    $resource = '/taxonomies/_filter?target=' . $target;
    return $this->getCache($resource)->httpRequestGetBuilder($resource);
  }

  public function taxonomyFilter($name, $target) {
    $resource = '/taxonomy/' . $name . '/_filter?target=' . $target;
    return $this->getCache($resource)->httpRequestGetBuilder($resource);
  }

  public function variablesCoverage($query) {
    $resource = '/variables/_coverage?query=' . $query;
    return $this->getCache($resource)->httpRequestGetBuilder($resource);
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

  public function taxonomiesCoverageRql($query, $type, $aggregation_type, $strict) {
    if (!empty($_SESSION['errorsQuery'])) {
      unset($_SESSION['errorsQuery']);
    }

    $request_parameters = array(
      'query' => $query,
      'strict' => $strict ? 'true' : 'false'
    );

    $url = sprintf("%s/%s/legacy/_%s", $this->micaUrl, $type, $aggregation_type);
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON)
        )
      ),
      'parameters' => $request_parameters,
    ));

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return empty($data) ? array() : json_decode($data);
    } catch (HttpClientException $e) {
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return array();
    }
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
