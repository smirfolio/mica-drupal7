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
 * MicaStudyResource class
 */

use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient as DrupalMicaClient;
/**
 * Class MicaStudyResource
 */
class DrupalMicaDatasetResource extends DrupalMicaClientResource {

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   */
  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  /**
   * Get the list of datasets.
   *
   * @param string $resource
   *   The resource to query.
   * @param int $study_id
   *   The study id.
   * @param string $query
   *   The query in http request.
   * @param int $from
   *   The from item.
   * @param int $limit
   *   The size response server.
   * @param string $sort
   *   Field name to sort by.
   * @param string $order
   *   the sort "asc" or "desc".
   *
   * @return array
   *   Server response.
   */
  public function getDatasets($resource = NULL, $study_id = NULL, $query = NULL, $from = 0, $limit = 50, $sort = NULL, $order = NULL, $network_id = NULL) {
    global $language;
    $this->setLastResponse(NULL);
    $from = empty($from) ? '0' : $from;
    $limit = empty($limit) ? '5' : $limit;
    $order = empty($order) ? '' : ($order == 'desc' ? '-' : '');
    $sort_rql_bucket = empty($sort) ? ",sort(name)" : ",sort($order$sort)";
    $query = empty($query) ? '' : ",match($query,(Mica_dataset.name,Mica_dataset.acronym,Mica_dataset.description))";
    $resource_params = empty($resource) ? '' : ",in(Mica_dataset.className,$resource)";
    $network_params = empty($network_id) ? '' : ",in(Mica_dataset.networkId,$network_id)";
    $studies_param = empty($study_id) ? '' : ",study(in(Mica_study.id,(" . rawurlencode($study_id) . ")))";

    if (!empty($query) || !empty($resource_params) || !empty($studies_param)) {
      $params = "dataset(limit($from,$limit)$resource_params$network_params$query$sort_rql_bucket)$studies_param";
    }
    else {
      $params = "dataset(exists(Mica_dataset.id),limit($from,$limit)$sort_rql_bucket)";
    }

    $params .= ",locale($language->language)";
    $resource_query = '/datasets/_rql?query=' . $params;
    $cached_datasets = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cached_datasets)) {
      return $cached_datasets;
    }
    else {
      $url_datasets = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url_datasets, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $datasets = json_decode($data);
        if ($datasets->datasetResultDto->totalCount !== 0) {
          $datasets_result = new DrupalMicaClient\DatasetJoinResponseWrapper($datasets);
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $datasets_result);
          return $datasets_result;
        }
      } catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        return array();
      }
    }
  }

  /**
   * Get a dataset by its ID.
   *
   * @param string $dataset_id
   *   The dataset id.
   * @param string $resource
   *   The resource to query.
   *
   * @return array
   *   The server response.
   */
  public function getDataset($dataset_id, $resource = 'dataset', $token_key = NULL) {
    $resource_query = (empty($resource) ? 'dataset' : $resource) . '/' . $dataset_id;
    if(!empty($token_key)){
      $resource_query = 'draft/' . (empty($resource) ? 'dataset' : $resource) . '/' . $dataset_id . '?key=' . $token_key;
    }
    $this->setLastResponse(NULL);
    $cached_dataset = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    $url = $this->micaUrl . '/' . $resource_query;
    if (!empty($cached_dataset)) {
      return $cached_dataset;
    }
    else {
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));

      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $result_dataset = $data ? json_decode($data) : NULL;
        if (!empty($result_dataset)) {
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $result_dataset);
          return $result_dataset;
        }

      } catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        $message_parameters['message'] = 'Connection to server fail,  Error serve code : @code, message: @message';
        $message_parameters['placeholders'] = array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        );
        $message_parameters['severity'] = 'error';
        if ($e->getCode() == 500 || $e->getCode() == 503 || $e->getCode() == 0) {
          DrupalMicaClientResource::DrupalMicaErrorHandler(TRUE, $message_parameters);
          throw $e;
        }
        if (obiba_mica_commons_is_ajax()) {
          DrupalMicaClientResource::DrupalMicaErrorHandler(NULL, $message_parameters);
        }
        else {
          drupal_set_message(t($message_parameters['message'], $message_parameters['placeholders']), $message_parameters['severity']);
        }
      }
    }
  }

  /**
   * Get the list of variables of the dataset.
   *
   * @param string $resource
   *   The resource to query.
   * @param string $dataset_id
   *   The dataset id.
   * @param int $from
   *   The from item.
   * @param int $limit
   *   The size response server.
   * @param string $sort
   *   Field name to sort by.
   * @param string $order
   *   the sort "asc" or "desc".
   * @param string $query
   *   The query in http request.
   *
   * @return array
   *   The server response.
   */
  public function getVariables($resource, $dataset_id, $from = 0, $limit = -1, $sort = NULL, $order = NULL, $query = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=-1' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . urlencode($query);
    $resource_query = (empty($resource) ? 'dataset' : $resource) .
      '/' . rawurlencode($dataset_id) .
      '/variables' . (empty($query) ? ''
        : '/_search') . '?' . $params;
    $url = $this->micaUrl . '/' . $resource_query;
    $cached_variables_dataset = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cached_variables_dataset)) {
      return $cached_variables_dataset;
    }
    else {
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        if (!empty($data)) {
          $variables_result = json_decode($data);
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $variables_result);
          return $variables_result;
        }
      } catch (HttpClientException $e) {
        return array();
      }
    }
  }

  /**
   * Query the cross variables.
   *
   * @param string $resource
   *   The resource to query.
   * @param string $dataset_id
   *   The dataset id.
   * @param string $variable1
   *   The variable 1 id.
   * @param string $variable2
   *   The variable 2 id.
   *
   * @return stdClass
   *   The server response.
   */
  public function crossVariables($resource, $dataset_id, $variable1, $variable2) {
    $this->setLastResponse(NULL);
    $params = empty($variable2) ? '' : 'by=' . $variable2;
    $cross_variables_resource = (empty($resource) ? 'dataset' : $resource)
      . '/' . rawurlencode($dataset_id) .
      '/variable/' . (empty($variable1) ? '' : $variable1) . '/contingency?' . $params;
    $cached_variables_cross_table = $this->drupalCache->MicaGetCache(__FUNCTION__ . $cross_variables_resource);
    if (!empty($cached_variables_cross_table)) {
      return $cached_variables_cross_table;
    }
    else {
      $url = $this->micaUrl . '/' . $cross_variables_resource;
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        if (!empty($data)) {
          $result_data = json_decode($data);
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $cross_variables_resource, $result_data);
          return $result_data;
        }

      } catch (HttpClientException $e) {
        return new stdClass();
      }
    }
  }

  /**
   * Download the cross variables.
   *
   * @param string $resource
   *   The resource to query.
   * @param string $dataset_id
   *   The dataset id.
   * @param string $variable1
   *   The variable 1 id.
   * @param string $variable2
   *   The variable 2 id.
   * @param string $doc_type
   *   The type download file.
   *
   * @return array
   *   The server response.
   */
  public function downloadCrossVariables($resource, $dataset_id, $variable1, $variable2, $doc_type) {
    $this->setLastResponse(NULL);
    $params = empty($variable2) ? '' : 'by=' . $variable2;
    $url = $this->micaUrl . '/' . (empty($resource) ? 'dataset' : $resource) . '/' . rawurlencode($dataset_id)
      . '/variable/' . (empty($variable1) ? '' : $variable1) . '/contingency/_export?' . $params;

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(
        $doc_type === 'csv' ? array('Accept' => array(parent::HEADER_CSV)) : array('Accept' => array(parent::HEADER_EXCEL_SHEET))
      ),
    ));
    $client = $this->client();
    try {
      $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return $client->lastResponse;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the list variable harmonization status for a harmonization dataset.
   *
   * @param string $resource
   *   The resource to query.
   * @param string $dataset_id
   *   The dataset id.
   * @param int $from
   *   The from item.
   * @param int $limit
   *   The size response server.
   * @param string $sort
   *   Field name to sort by.
   * @param string $order
   *   the sort "asc" or "desc".
   * @param string $query
   *   The query in http request.
   *
   * @return array
   *   The server response.
   */
  public function getVariablesHarmonizations($resource, $dataset_id, $from = 0, $limit = -1, $sort = NULL, $order = NULL, $query = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=-1' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;

    $query_resources = (empty($resource) ? 'dataset' : $resource)
      . '/' . rawurlencode($dataset_id) .
      '/variables/harmonizations?' . $params;
    $Cached_variables_harmonized = $this->drupalCache->MicaGetCache(__FUNCTION__ . $query_resources);
    if (!empty($Cached_variables_harmonized)) {
      return $Cached_variables_harmonized;
    }
    else {
      $url = $this->micaUrl . '/' . $query_resources;
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        if (!empty($data)) {
          $variable_result = json_decode($data);
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $query_resources, $variable_result);
          return $variable_result;
        }
      } catch (HttpClientException $e) {
        if (obiba_mica_commons_is_ajax()) {
          $message_parameters['message'] = 'Connection to server fail,  Error serve code : @code, message: @message';
          $message_parameters['placeholders'] = array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          );
          $message_parameters['severity'] = 'error';
          DrupalMicaClientResource::DrupalMicaErrorHandler(NULL, $message_parameters);
        }
        else{
          return array();
        }
      }
    }
  }

  /**
   * Download the variables harmonizations.
   *
   * @param string $dataset_id
   *   The dataset id.
   * @param string $locale
   *   The local of variable.
   *
   * @return array
   *   The server response.
   */
  public function downloadVariablesHarmonizations($dataset_id, $locale) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/harmonization-dataset/' . rawurlencode($dataset_id) . '/variables/harmonizations/_export';
    if (!empty($locale)) {
      $url .= '?locale=' . $locale;
    }

    $request = new HttpClientRequest($url, array(
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
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the variable by its ID.
   *
   * @param string $variable_id
   *   The variable id.
   *
   * @return array
   *   The server response.
   */
  public function getVariable($variable_id) {
    global $language;
    $resource_query = sprintf("/variable/%s?locale=%s", rawurlencode($variable_id), $language->language);
    $this->setLastResponse(NULL);
    $cached_variable = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cached_variable)) {
      return $cached_variable;
    }
    else {
      $url = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $result_variable = $data ? json_decode($data) : NULL;
        if (!empty($result_variable)) {
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $result_variable);
          return $result_variable;
        }
      } catch (HttpClientException $e) {
        return array();
      }
    }
    return array();
  }

  /**
   * Get the aggregation (=summary from ES) of the variable.
   *
   * @param string $variable_id
   *   The variable id.
   *
   * @return array
   *   The server response.
   */
  public function getVariableAggregation($variable_id) {
    $this->setLastResponse(NULL);
    $variable_aggregation_resource = '/variable/' . rawurlencode($variable_id) . '/aggregation';
    $variable_aggregations = $this->drupalCache->MicaGetCache(__FUNCTION__ . $variable_aggregation_resource);
    if (!empty($variable_aggregations)) {
      return $variable_aggregations;
    }
    else {
      $url = $this->micaUrl . $variable_aggregation_resource;
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        if (!empty($data)) {
          $variable_aggregation_response = json_decode($data);
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $variable_aggregation_resource, $variable_aggregation_response);
          return $variable_aggregation_response;
        }
      } catch (HttpClientException $e) {
        return array();
      }
    }
  }

  /**
   * Get the harmonizations of a dataschema variable.
   *
   * @param string $variable_id
   *   The variable id.
   *
   * @return array
   *   The server response.
   */
  public function getVariableHarmonizations($variable_id) {
    $this->setLastResponse(NULL);
    $resource_request = '/variable/' . rawurlencode($variable_id) . '/harmonizations';
    $cached_variable_harmonization = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_request);
    if (!empty($cached_variable_harmonization)) {
      return $cached_variable_harmonization;
    }
    $url = $this->micaUrl . $resource_request;
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      if (!empty($data)) {
        $response_data = $data ? json_decode($data) : NULL;
        $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_request, $response_data);
        return $response_data;
      }
    } catch (HttpClientException $e) {
      return array();
    }
  }

}
