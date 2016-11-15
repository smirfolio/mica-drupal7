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
    $parameters = compact('resource', 'study_id', 'query', 'from', 'limit', 'sort', 'order', 'network_id');
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    $obiba->buildResourceQuery('getDatasets', $parameters);
    $Dtasets = $obiba->getCollections('getDatasets');
    return $Dtasets;
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
  public function getDataset($dataset_id, $resource = 'dataset', $token_key = NULL)) {
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    $resource_param = array(
      'id' => $dataset_id,
      'resource' => $resource
    );
    return $obiba->buildResourceQuery('getDataset', $resource_param)
      ->getDocument('getDataset');
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
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    $parameters = compact('resource', 'dataset_id', 'from', 'limit', 'sort', 'query', 'order');
    $obiba->buildResourceQuery('getVariables', $parameters);
    return $obiba->getCollections('getVariables');
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
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    return $obiba->buildResourceQuery('getVariable', $variable_id)
      ->getDocument('getVariable');
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
