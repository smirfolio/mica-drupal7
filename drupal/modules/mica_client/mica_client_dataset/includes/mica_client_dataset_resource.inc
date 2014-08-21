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

  public function get_datasetes($resource, $study_id = NULL) {
    $this->setLastResponse(NULL);
    $study_resouce = !empty($study_id) ? '&study=' . $study_id : '';
    $url_study_datasets = $this->micaUrl . '/' . $resource . '/?limit=-1' . $study_resouce;
    //dpm($url_study_datasets);
    $request = new HttpClientRequest($url_study_datasets, array(
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
      $dtos = array();
      // dpm(json_decode($data));

      if (!empty(json_decode($data)->datasets)) {
        foreach (json_decode($data)->datasets as $dataset) {
          $dtoObj = '\obiba\mica\DatasetDto';
          $dtos [] = Protobuf::decode($dtoObj, json_encode($dataset));
        }
      }

      return $dtos;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public function variables_search($request_param, $spec_dto_params = NULL, $size = NULL) {
    $this->setLastResponse(NULL);
    $limit_param = is_null($size) ? parent::SIZE_RESPONSE : $size;
    $url = $this->micaUrl . '/variables/' . $request_param . '/_search?limit=' . $limit_param;
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    if (empty($url_parm[1])) {
      $dto_param = $this->dto_filter_construct(NULL, NULL, 'variable', $spec_dto_params);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/variables/' . $request_param . '/_search?from=' . json_decode($dto_param)->from . '&limit=' . $limit_param;

        $request = new HttpClientRequest($url, array(
          'method' => HttpClientRequest::METHOD_GET,
          'headers' => $this->authorizationHeader(array(
                'Accept' => array(parent::HEADER_JSON),
              )
            ),
        ));
      }
      else {
        $request = new HttpClientRequest($url, array(
          'method' => HttpClientRequest::METHOD_POST,
          'headers' => $this->authorizationHeader(array(
                'Accept' => array(parent::HEADER_JSON),
                'Content-Type' => array(parent::HEADER_JSON)
              )
            ),
          'data' => $dto_param,
        ));
      }
    }
    else {
      $dto_param = $this->dto_filter_construct($url_parm[1], array('parent' => 'Study'), 'variable', $spec_dto_params);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/variables/' . $request_param . '/_search?from=' . json_decode($dto_param)->from . '&limit=' . $limit_param;

        $request = new HttpClientRequest($url, array(
          'method' => HttpClientRequest::METHOD_GET,
          'headers' => $this->authorizationHeader(array(
                'Accept' => array(parent::HEADER_JSON),
              )
            ),
        ));
      }
      else {
        $request = new HttpClientRequest($url, array(
          'method' => HttpClientRequest::METHOD_POST,
          'headers' => $this->authorizationHeader(array(
                'Accept' => array(parent::HEADER_JSON),
                'Content-Type' => array(parent::HEADER_JSON)
              )
            ),
          'data' => $dto_param,
        ));
      }
    }
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      $dto_data_response = json_decode($data);
      $this->session_facets_builder($dto_data_response, 'variable', $request_param);

      //dpm($dto_data_response);
      $summaries_variables = array();
      if ($dto_data_response->totalHits > 0) {
        $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
      }
      $dtoObj = '\obiba\mica\DatasetVariableResolverDto';
      $dtos = array();
      $summarier_data = !empty($summaries_variables) ? $summaries_variables : NULL;
      if ($summarier_data) {
        foreach ($summaries_variables as $variable) {
          $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($variable));
        }
      }
      $dtos['totalHits'] = $dto_data_response->totalHits;
      return $dtos;
    } catch (HttpClientException $e) {
      return array('totalHits' => 0);
    }
  }

  public function get_dataset_varaibles($resource, $dataset_id, $size = NULL) {
    $this->setLastResponse(NULL);
    $limit_param = is_null($size) ? parent::SIZE_RESPONSE : $size;
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    $url = $this->micaUrl . '/' . $resource . '/' . $dataset_id . '/variables?limit=' . $size_param;

    if (empty($url_parm[1])) {
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
              'Accept' => array(parent::HEADER_JSON),
            )
          ),
      ));
    }
    else {
      $dto_param = $this->dto_filter_construct($url_parm[1], NULL, 'variable');
      $url = $this->micaUrl . '/' . $resource . '/' . $dataset_id . '/variables?from=' . json_decode($dto_param)->from . '&limit=' . $size_param;
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
              'Accept' => array(parent::HEADER_JSON),
            )
          ),
      ));
    }

    $client = $this->client();
    try {
      $data = $client->execute($request);
      // return $data;
      $this->setLastResponse($client->lastResponse);
      $dtoObj = '\obiba\mica\DatasetVariablesDto';

      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public function get_dataset($resource_dataset, $dataset_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/' . $resource_dataset . '/' . $dataset_id;

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

  public function get_variable($resource_dataset, $dataset_id, $detail = NULL) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/' . $resource_dataset . '/' . $dataset_id . '/' . $detail;
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
      $dtoObj = '\obiba\mica\DatasetVariableDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

}