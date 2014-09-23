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

  private function  _search_resource() {
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);

    parse_str($url_parm[1], $parts);
    $dto_param = $this->dto_filter_construct($parts['type'], $parts['query'], 0);
    $url = $this->micaUrl . '/' . $parts['type'] . '/_search';
    if (!empty($parts['query']) && empty($parts['page'])) {
      $dto_param = $this->dto_filter_construct($parts['query']);
    }
    if (!empty($parts['page']) && empty($parts['query'])) {
      $from = $this->pagination_list_search_parameters($_GET['page'], 'list-studies', $this::SIZE_RESPONSE);
      $dto_param = $this->dto_filter_construct(NULL, $from);
    }
    if (!empty($parts['page']) && !empty($parts['query'])) {
      $from = $this->pagination_list_search_parameters($_GET['page'], 'list-studies', $this::SIZE_RESPONSE);
      $dto_param = $this->dto_filter_construct($parts['query'], $from);
    }

    if (empty($parts['page']) && empty($parts['query'])) {
      $dto_param = $dto_param = $this->dto_filter_construct();
    }
    dpm($dto_param);
    dpm($url);
    $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_POST,
        'headers' => $this->authorizationHeader(array(
              'Accept' => array(parent::HEADER_JSON),
              'Content-Type' => array(parent::HEADER_JSON)
            )
          ),
        'data' => $dto_param,
      ));

//    else {
//      $url_param = $url . '?size=20';
//      if (!empty($_GET['page'])) {
//        $from = $this->pagination_list_search_parameters($_GET['page'], 'list-studies', $this::SIZE_RESPONSE);
//      }
//      if (!empty($from)) {
//        $url_param .= '&from=' . $from;
//      }
//      dpm($url_param);
//      $request = new HttpClientRequest($url_param, array(
//        'method' => HttpClientRequest::METHOD_GET,
//        'headers' => $this->authorizationHeader(array(
//              'Accept' => array(parent::HEADER_JSON),
//            )
//          ),
//      ));
//    }

    $client = $this->client();
    try {
      //dpm($request);
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      // dpm(json_decode($data));
      return json_decode($data);

    } catch (HttpClientException $e) {
      return array();
    }

  }


  private function _search_resource_($resource, $request_param = NULL, $parent_child, $type_parent_child, $spec_dto_params = NULL, $size = NULL) {
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

  public function get_stats_entities_count($dto, $dto_data_response) {
    return array(
      'data' => $dto['data'],
      'study_totalHits' => $dto_data_response->studyResultDto->totalHits,
      'study_totalCount' => $dto_data_response->studyResultDto->totalCount,
      'variable_totalHits' => $dto_data_response->variableResultDto->totalHits,
      'variable_totalCount' => $dto_data_response->variableResultDto->totalCount,
      'network_totalHits' => !empty($dto_data_response->networkResultDto->totalHits) ?
          $dto_data_response->networkResultDto->totalHits : 0,
      'network_totalCount' => !empty($dto_data_response->networkResultDto->totalCount) ?
          $dto_data_response->networkResultDto->totalCount : 0
    );
  }

  public function search_variables($request_param = NULL, $spec_dto_params = NULL, $size = NULL) {
    $data_response = $this->_search_resource('variables', $request_param, 'parent', 'Study', $spec_dto_params, $size);
    $dto_data_response = $data_response->variableResultDto;
    /*ad to session aggregation from other dto entities*/
    $this->session_facets_builder($data_response, $request_param);
    $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
    $dtoObj = '\obiba\mica\DatasetVariableResolverDto';
    $dtos = array();
    $summaries_data = !empty($summaries_variables) ? $summaries_variables : NULL;
    if ($summaries_data) {
      foreach ($summaries_variables as $variable) {
        $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($variable));
      }
    }
    $dtos = $this->get_stats_entities_count($dtos, $data_response);
    return $dtos;
  }

  public function search_studies($request_param = NULL, $spec_dto_params = NULL, $size = NULL) {
    $data_response = $this->_search_resource('studies', $request_param, 'child', 'Variable', NULL);

    $dto_data_response = $data_response->studyResultDto;
    $this->session_facets_builder($data_response, $request_param);
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
      $dtos = $this->get_stats_entities_count($dtos, $data_response);

    }
    else {
      $dtos ['study-totalHits'] = 0;
    }

    return $dtos;
  }


  public function search_networks($request_param = NULL, $spec_dto_params = NULL, $size = NULL) {
    $data_response = $this->_search_resource('networks', $request_param, 'child', 'Study', NULL);
    //$this->session_facets_builder($dto_data_response, 'networks');


    if (!empty($data_response->networkResultDto)) {
      $dto_data_response = $data_response->networkResultDto;
      /*ad to session aggregation from other dto entities*/
      $this->session_facets_builder($data_response, $request_param);
      $summaries_networks = $dto_data_response->{'obiba.mica.NetworkResultDto.result'}->networks;
      $dtoObj = '\obiba\mica\NetworkDto';
      $dtos = array();
      $summaries_data = !empty($summaries_networks) ? $summaries_networks : NULL;
      if ($summaries_data) {
        foreach ($summaries_networks as $networks) {
          $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($networks));
        }
      }
      $dtos = $this->get_stats_entities_count($dtos, $data_response);
      return $dtos;
    }

  }

}