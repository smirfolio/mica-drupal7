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

use \Obiba\ObibaMicaClient\MicaCache as MicaCache;

/**
 * @file
 * Mica networks file
 */
class ObibaSearchResources extends DrupalMicaClientResource {
  const MICA_REPOSITORY = 'mica/repository';

  function __construct() {
    parent::__construct(NULL);
  }

  private function httpRequestGetBuilder($resources, $header_accept = 'HEADER_JSON', $ajax = FALSE) {
    $stored_data = NULL;
    $stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resources);
    if (!empty($stored_data)) {
      return $stored_data;
    }
    else {
      $response = $this->sendGet($resources, $header_accept, $ajax, array('headers'=> array('Content-Type' => array($header_accept))));
      $array_response = json_decode($response);
      if (!empty($array_response)) {
        $this->drupalCache->MicaSetCache(__FUNCTION__ . $resources, $array_response);
        return $array_response;
      }
    }
    return FALSE;
  }

  public function searchQuery($type, $query, $ajax = FALSE) {
    $resource = '/' . $type . '/_rql?query=' . $query;
    return $this->httpRequestGetBuilder($resource, 'HEADER_JSON', $ajax);
  }

  public function searchQueryAsCsv($type, $query) {
    $resource = '/' . $type . '/_rql_csv?query=' . $query;
    return $this->downloadFileGet($resource, array('HEADER_CSV'));
  }

  public function taxonomiesSearch($query, $target, $locale) {
    $resource = '/taxonomies/_search?query=' . rawurlencode($query)
      . (!empty($target) ? '&target=' . $target : '')
      . (!empty($locale) ? '&locale=' . $locale : '');
    return $this->httpRequestGetBuilder($resource);
  }

  public function taxonomiesFilter($target) {
    $resource = '/taxonomies/_filter?target=' . $target;
    return $this->httpRequestGetBuilder($resource);
  }

  public function taxonomyFilter($name, $target) {
    $resource = '/taxonomy/' . $name . '/_filter?target=' . $target;
    return $this->httpRequestGetBuilder($resource);
  }

  public function variablesCoverage($query) {
    $resource = '/variables/_coverage?query=' . $query;
    return $this->httpRequestGetBuilder($resource);
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
    $request_parameters = array(
      'parameters' => array(
        'query' => $query,
        'strict' => $strict ? 'true' : 'false'
      )
    );
    $resources = $query . $type . $aggregation_type;
    $stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resources);
    if (!empty($stored_data)) {
      return $stored_data;
    }
    else {
      $resource_query = sprintf("/%s/legacy/_%s", $type, $aggregation_type);
      $response = $this->sendGet($resource_query, 'HEADER_JSON', TRUE, $request_parameters);
      if (!empty($response)) {
        $result_data = json_decode($response);
        $this->drupalCache->MicaSetCache(__FUNCTION__ . $resources, $result_data);
        return $result_data;
      }
    }
    return array();
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
    if (is_array($entity_id)) {
      $entity_id = implode(',', $entity_id);
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

  /**
   * The query builder for charts.
   *
   * @param string $query
   *   The query for the charts.
   * @param object $bucket
   *   The bucket.
   * @param string $taxonomy_name
   *   The taxonomy name.
   * @param string $vocabulary_name
   *   The vocabulary name.
   * @param array $terms
   *   The terms.
   *
   * @return string
   *   A json query.
   */
  public static function chartQueryBuilders($query = NULL, $bucket = NULL, $taxonomy_name = NULL, $vocabulary_name = NULL, array $terms = NULL, $entity_id = NULL) {
    return ObibaSearchResources::repositoryRqlBuilder($query, $bucket, $taxonomy_name, $vocabulary_name, $entity_id);
  }
}
