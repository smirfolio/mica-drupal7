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
class MicaSearchResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
  }

  private function _search_resource($resource, $request_param = NULL, $parent_child, $type_parent_child, $spec_dto_params = NULL, $size = NULL) {
    $this->setLastResponse(NULL);
    $request_param = !empty($request_param) ? '/' . $request_param : NULL;
    $url = $this->micaUrl . '/' . $resource . $request_param . '/_search?' . 'size=' . (is_null($size) ? $this::SIZE_RESPONSE : $size);
    //dpm($url);
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    if (empty($url_parm[1])) {
      $dto_param = $this->dto_filter_construct(NULL, NULL, $resource, $spec_dto_params, $size);

      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
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
      $dto_param = $this->dto_filter_construct($url_parm[1], array($parent_child => $type_parent_child), $resource, $spec_dto_params, $size);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/' . $resource . $request_param . '/_search?from=' . json_decode($dto_param)->from . '&size=' . (is_null($size) ? $this::SIZE_RESPONSE : $size);

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
          'data' => $dto_param
        ));
      }
    }
    $client = $this->client();
    try {
      //dpm($request);
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      //dpm(json_decode($data));

      return json_decode($data);

    } catch (HttpClientException $e) {

      return array();
    }
  }

  public function search_variables($request_param = NULL, $spec_dto_params = NULL, $size = NULL) {
    $data_response = $this->_search_resource('variables', $request_param, 'parent', 'Study', $spec_dto_params, $size);
    $dto_data_response = $data_response->variableResultDto;
    $this->session_facets_builder($dto_data_response, 'variables', $request_param);
    // dpm($dto_data_response);
    $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
    $dtoObj = '\obiba\mica\DatasetVariableResolverDto';
    $dtos = array();
    $summaries_data = !empty($summaries_variables) ? $summaries_variables : NULL;
    if ($summaries_data) {
      foreach ($summaries_variables as $variable) {
        $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($variable));
      }
    }
    $dtos['totalHits'] = $dto_data_response->totalHits;
    $dtos['totalCount'] = $dto_data_response->totalCount;
    return $dtos;
  }

  public function search_studies() {
    $data_response = $this->_search_resource('studies', NULL, 'child', 'Variable', NULL);
    $dto_data_response = $data_response->studyResultDto;
    $this->session_facets_builder($dto_data_response, 'studies');
    $summaries_studies = !empty($dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries) ?
      $dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries : NULL;
    $dtoObj = '\obiba\mica\StudySummaryDto';
    $dtos = array();
    $summaries_data = !empty($summaries_studies) ? $summaries_studies : NULL;
    if ($summaries_data) {
      foreach ($summaries_studies as $study) {
        $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($study));
      }
    }
    if (!empty($dto_data_response)) {
      $dtos ['totalHits'] = $dto_data_response->totalHits;
      $dtos ['totalCount'] = $dto_data_response->totalCount;
    }
    else {
      $dtos ['totalHits'] = 0;
    }

    return $dtos;
  }


  public function search_networks() {
    $dto_data_response = $this->_search_resource('networks', NULL, 'child', 'Study', NULL);
    //$this->session_facets_builder($dto_data_response, 'studies');
    // dpm($dto_data_response);
    dpm($dto_data_response);
//    $summaries_networks = !empty($dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries) ?
//      $dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries : NULL;
//    $dtoObj = '\obiba\mica\NetworkDto';
//    $dtos = array();
//    $summaries_data = !empty($summaries_networks) ? $summaries_networks : NULL;
//    if ($summaries_data) {
//      foreach ($summaries_networks as $network) {
//        $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($network));
//      }
//    }
//    if (!empty($dto_data_response)) {
//      $dtos ['totalHits'] = $dto_data_response->totalHits;
//      $dtos ['totalCount'] = $dto_data_response->totalCount;
//    }
//    else {
//      $dtos ['totalHits'] = 0;
//    }
//
//    return $dtos;
  }

}