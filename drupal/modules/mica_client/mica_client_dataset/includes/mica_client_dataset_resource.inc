<?php

/**
 * @file
 * MicaStudyResource class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'mica_client_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');

/**
 * Class MicaStudyResource
 */
class MicaDatasetResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
  }

  /**
   * Get the list of datasets.
   *
   * @param string $resource "datasets" or "harmonization-datasets" or "study-datasets"
   * @param null $study_id
   * @param null $query
   * @param int $from
   * @param $limit
   * @param null $sort field name to sort by
   * @param null $order "asc" or "desc"
   * @return array
   */
  public function get_datasets($resource = 'datasets', $study_id = NULL, $query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=5' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;
    $params .= empty($study_id) ? '' : '&study=' . $study_id;
    $url_datasets = $this->micaUrl . (empty($resource) ? '' : '/' . $resource) . '/_search?' . $params;
    $request = new HttpClientRequest($url_datasets, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return new DatasetJoinResponseWrapper(json_decode($data));
    } catch (HttpClientException $e) {

      drupal_set_message(t('Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage())), 'error');
      return array();
    }
  }

  /**
   * Get a dataset by its ID.
   *
   * @param string $resource "dataset" or "harmonization-dataset" or "study-dataset"
   * @param $dataset_id
   * @return array|Protobuf\Message|null
   */
  public function get_dataset($resource = 'dataset', $dataset_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/' . (empty($resource) ? 'dataset' : $resource) . '/' . rawurlencode($dataset_id);

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
      $dtoObj = '\obiba\mica\DatasetDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the list of variables of the dataset.
   *
   * @param $resource "dataset" or "harmonization-dataset" or "study-dataset"
   * @param $dataset_id
   * @param int $from
   * @param $limit
   * @param null $sort field name to sort by
   * @param null $order "asc" or "desc"
   * @return array|Protobuf\Message|mixed|null
   */
  public function get_variables($resource, $dataset_id, $from = 0, $limit = -1, $sort = NULL, $order = NULL, $query = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=-1' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;

    $url = $this->micaUrl . '/' . (empty($resource) ? 'dataset' : $resource) . '/' . rawurlencode($dataset_id) . '/variables?' . $params;
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
      if (!empty($detail)) {
        return json_decode($data);
      }
      $dtoObj = '\obiba\mica\DatasetVariablesDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the list variable harmonization status for a harmonization dataset.
   *
   * @param $resource "dataset" or "harmonization-dataset" or "study-dataset"
   * @param $dataset_id
   * @param int $from
   * @param $limit
   * @param null $sort field name to sort by
   * @param null $order "asc" or "desc"
   * @return array|Protobuf\Message|null
   */
  public function get_variables_harmonizations($resource, $dataset_id, $from = 0, $limit = -1, $sort = NULL, $order = NULL, $query = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=-1' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;
    $url = $this->micaUrl . '/' . (empty($resource) ? 'dataset' : $resource) . '/' . rawurlencode($dataset_id) . '/variables/harmonizations?' . $params;
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
      $dtoObj = '\obiba\mica\DatasetVariablesHarmonizationsDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the variable by its ID.
   *
   * @param $variable_id
   * @return array|Protobuf\Message|null
   */
  public function get_variable($variable_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/variable/' . rawurlencode($variable_id);
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
      $dtoObj = '\obiba\mica\DatasetVariableDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the facet (=summary from ES) of the variable.
   *
   * @param $variable_id
   * @return array|mixed
   */
  public function get_variable_facet($variable_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/variable/' . rawurlencode($variable_id) . '/facet';
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
      return json_decode($data);
    } catch (HttpClientException $e) {
      return array();
    }
  }

  /**
   * Get the harmonizations of a dataschema variable.
   *
   * @param $variable_id
   * @return array|Protobuf\Message|null
   */
  public function get_variable_harmonizations($variable_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/variable/' . rawurlencode($variable_id) . '/harmonizations';
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
      $dtoObj = '\obiba\mica\DatasetVariableHarmonizationDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

}