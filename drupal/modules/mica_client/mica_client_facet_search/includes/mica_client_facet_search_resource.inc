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

  private function _search_resource($resource, $request_param = NULL, $parent_child, $type_parent_child, $spec_dto_params = NULL) {
    $this->setLastResponse(NULL);
    $request_param = !empty($request_param) ? '/' . $request_param : NULL;
    $url = $this->micaUrl . '/' . $resource . $request_param . '/_search/?' . 'size=' . parent::SIZE_RESPONSE;
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    if (empty($url_parm[1])) {
      $dto_param = $this->dto_filter_construct(NULL, NULL, $resource, $spec_dto_params);
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
      $dto_param = $this->dto_filter_construct($url_parm[1], array($parent_child => $type_parent_child), $resource, $spec_dto_params);
      if (empty(json_decode($dto_param)->filteredQuery->filter)) {
        $url = $this->micaUrl . '/' . $resource . $request_param . '/_search/?from=' . json_decode($dto_param)->from . '&size=' . parent::SIZE_RESPONSE;

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
      //  $dto_data_response = Protobuf::decode('\obiba\mica\QueryResultDto', $data);
      dpm(json_decode($data));

      return json_decode($data);

    } catch (HttpClientException $e) {

      return array();
    }
  }

  public function search_variables($request_param = NULL, $spec_dto_params = NULL) {
    $dto_data_response = $this->_search_resource('variables', $request_param, 'parent', 'Study', $spec_dto_params);
    $this->session_facets_builder($dto_data_response, 'variables', $request_param);

    // dpm($dto_data_response);
    $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
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
  }

  public function search_studies() {
    $dto_data_response = $this->_search_resource('studies', NULL, 'child', 'Variable');
    $this->session_facets_builder($dto_data_response, 'studies');

    // dpm($dto_data_response);
    $summaries_studies = !empty($dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries) ?
      $dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries : NULL;
    $dtoObj = '\obiba\mica\StudySummaryDto';
    $dtos = array();
    $summarier_data = !empty($summaries_studies) ? $summaries_studies : NULL;
    if ($summarier_data) {
      foreach ($summaries_studies as $study) {
        $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($study));
      }
    }
    $dtos ['totalHits'] = $dto_data_response->totalHits;

    return $dtos;
  }

}