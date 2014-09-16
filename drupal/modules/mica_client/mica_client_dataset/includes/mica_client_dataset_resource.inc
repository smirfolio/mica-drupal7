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

  public function get_datasets($resource = 'datasets', $study_id = NULL, $query = NULL) {
    $this->setLastResponse(NULL);
    $params = !empty($study_id) ? '&study=' . $study_id : '';
    if (!empty($query)) {
      $params .= '&query=' . $query;
    }
    $url_datasets = $this->micaUrl . '/' . $resource . '?limit=-1' . $params;
    //dpm($url_study_datasets);
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

  public function variables_search($spec_dto_params = NULL, $size = NULL) {
    $this->setLastResponse(NULL);
    $size_param = is_null($size) ? parent::SIZE_RESPONSE : $size;
    $url = $this->micaUrl . '/variables/_search?size=' . $size_param;
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    if (empty($url_parm[1])) {
      $dto_param = $this->dto_filter_construct(NULL, NULL, 'variable', $spec_dto_params, $size_param);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/variables/_search?from=' . json_decode($dto_param)->from . '&size=' . $size_param;

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
      $dto_param = $this->dto_filter_construct($url_parm[1], array('parent' => 'Study'), 'variable', $spec_dto_params, $size_param);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/variables/_search?from=' . json_decode($dto_param)->from . '&size=' . $size_param;

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
      $this->session_facets_builder($dto_data_response, 'variable');

      //dpm($dto_data_response);
      $variable_summaries = array();
      if ($dto_data_response->totalHits > 0 && $size_param > 0) {
        $variable_summaries = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
      }
      $dtoObj = '\obiba\mica\DatasetVariableResolverDto';
      $response = array();
      if (!empty($variable_summaries)) {
        foreach ($variable_summaries as $variable) {
          $response ['data'][] = Protobuf::decode($dtoObj, json_encode($variable));
        }
      }
      $response['totalHits'] = $dto_data_response->totalHits;
      if (!empty($dto_data_response->aggs)) {
        $response['aggs'] = $dto_data_response->aggs;
      }
      return $response;
    } catch (HttpClientException $e) {
      return array('totalHits' => 0);
    }
  }

  public function get_dataset($resource_dataset = 'dataset', $dataset_id) {
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