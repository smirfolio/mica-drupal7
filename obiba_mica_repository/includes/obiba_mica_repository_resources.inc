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

  private function httpRequestGetBuilder($resources, $header_accept = parent::HEADER_JSON) {

    $stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resources);
    if ($stored_data !== FALSE)
      return $stored_data;

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
      $response = !empty($data) ? json_decode($data) : NULL;
      if (!empty($response)) {
        $this->getLogo($response);
      }
      $this->drupalCache->MicaSetCache(__FUNCTION__ . $resources, $response);
      return $response;
    } catch (HttpClientException $e) {

      if ($e->getCode() == 403) {
        $error_level = WATCHDOG_WARNING;
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      } else {
        $error_level = WATCHDOG_ERROR;
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Error contacting Mica, please try again later.', 'error');
      }

      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), $error_level);

      $this->MicaClientAddHttpHeader('Status', $e->getCode());
      throw $e;

    } catch (Exception $e) {

      drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Error contacting Mica, please try again later.', 'error');
      watchdog('Mica Client', 'Unexpected error, exception @exception', array('@exception' => $e), WATCHDOG_ERROR);
      throw $e;
    }
  }

  private function getLogo($result_search){
    if(!empty($result_search->studyResultDto->{'obiba.mica.StudyResultDto.result'}->summaries)){
      foreach ($result_search->studyResultDto->{'obiba.mica.StudyResultDto.result'}->summaries as $key => $summary){
        if(!empty($summary->logo->id)){
          $result_search->studyResultDto->{'obiba.mica.StudyResultDto.result'}->summaries[$key]->logoUrl = obiba_mica_commons_safe_expose_server_url($summary->id, $summary->logo, 'study');
        }
      }
    }
    return $result_search;
}

  public function searchQuery($type, $query) {
    $resource = '/' . $type . '/_rql?query=' . $query;
    return $this->httpRequestGetBuilder($resource);
  }

  public function searchQueryAsCsv($type, $query) {
    $resource = $this->micaUrl . '/' . $type . '/_rql_csv?query=' . $query;
    return $this->downloadCsvExport($resource);
  }

  public function searchStudyQueryAsCsvReport($query) {
    $resource = $this->micaUrl . '/studies/_report?query=' . $query;
    return $this->downloadCsvExport($resource);
  }

  public function searchStudyQueryAsCsvReportByNetwork($networkId, $locale) {
    $resource = $this->micaUrl . '/studies/_report_by_network?networkId=' . $networkId.'&locale='.$locale;
    return $this->downloadCsvExport($resource);
  }

  public function downloadCsvExport($resource) {

    $request = new HttpClientRequest($resource, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_CSV),
        )
      ),
    ));
    $client = $this->client();
    try {
      $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return $client->lastResponse;
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);
      return array();
    }
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

  public function taxonomiesCoverageRql($query, $type, $aggregation_type) {

    $request_parameters = array(
      'query' => $query,
      'strict' => 'false'
    );
    $resources = $query . $type . $aggregation_type;
    $stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resources);
    if ($stored_data !== FALSE) {
      return $stored_data;
    }

    $url = "$this->micaUrl/variables/legacy/_coverage";
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

      $result_data = json_decode((!empty($data) ? $data : '{"charts":[]}'));
      $this->drupalCache->MicaSetCache(__FUNCTION__ . $resources, $result_data);
      return $result_data;

    } catch (HttpClientException $e) {
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to Mica fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);

      throw $e;
    } catch (Exception $e) {
      watchdog('Mica Client', 'Connection to Mica fail,  Error serve code : @exception',
        array(
          '@exception' => $e,
        ), WATCHDOG_ERROR);

      throw $e;
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
    if (is_array($entity_id)) {
      $entity_id = implode(',', $entity_id);
    }

    if (!empty($query)) {
      $query_search .= 'datasetId,' . $entity_id;
    }
    else {
      switch ($bucket->field) {
        case 'studyId' :
          $query_search .= 'studyId,' . $bucket->value;
          break;
        case 'dceId' :
          $query_search .= 'dceId,' . urlencode(urlencode($bucket->value));
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
