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
 * Class MicaSearchResource
 */
class MicaSearchResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
  }

  public function taxonomies_coverage() {
    return $this->_aggregation_resource('coverage');
  }

  private function _search_resource() {
    return $this->_aggregation_resource('search');
  }

  private function  _aggregation_resource($aggregation_type = 'search') {
    $url_parm = explode('?', $_SERVER['REQUEST_URI']);
    $type = 'variables';
    $url = $this->micaUrl . '/' . $type . '/_' . $aggregation_type;
    if (!empty($url_parm[1])) {
      parse_str($url_parm[1], $parts);
      if (!empty($parts['type'])) {
        $type = $parts['type'];
      }

      $url = $this->micaUrl . '/' . $type . '/_' . $aggregation_type;
      if (!empty($parts['query']) && empty($parts['page'])) {
        $dto_param = $this->dto_filter_construct($type, $parts['query'], 0);
      }
      if (!empty($parts['page']) && empty($parts['query'])) {
        $from = $this->pagination_list_search_parameters($_GET['page'], $type, $this::SIZE_RESPONSE);
        $dto_param = $this->dto_filter_construct($type, NULL, $from);
      }
      if (!empty($parts['page']) && !empty($parts['query'])) {
        $from = $this->pagination_list_search_parameters($_GET['page'], $type, $this::SIZE_RESPONSE);
        $dto_param = $this->dto_filter_construct($type, $parts['query'], $from);
      }
      if (empty($parts['page']) && empty($parts['query'])) {
        $dto_param = $dto_param = $this->dto_filter_construct($type, NULL, 0);
      }
    }
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_POST,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
            'Content-Type' => array(parent::HEADER_JSON)
          )
        ),
      'data' => !empty($dto_param) ? $dto_param : $this->dto_filter_construct($type, NULL, 0),
    ));

    $client = $this->client();
    try {
//      dpm($request);
//      dpm($url);
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
//       dpm(json_decode($data));
      return json_decode($data);

    } catch (HttpClientException $e) {
      return array();
    }

  }

  public function get_stats_entities_count($dto, $dto_data_response) { //dpm($dto_data_response);
    return array(
      'data' => $dto['data'],
      'study_totalHits' => $dto_data_response->studyResultDto->totalHits,
      'study_totalCount' => $dto_data_response->studyResultDto->totalCount,
      'variable_totalHits' => $dto_data_response->variableResultDto->totalHits,
      'variable_totalCount' => $dto_data_response->variableResultDto->totalCount,
      'network_totalHits' => !empty($dto_data_response->networkResultDto->totalHits) ?
          $dto_data_response->networkResultDto->totalHits : 0,
      'network_totalCount' => !empty($dto_data_response->networkResultDto->totalCount) ?
          $dto_data_response->networkResultDto->totalCount : 0,
      'dataset_totalHits' => !empty($dto_data_response->datasetResultDto->totalHits) ?
          $dto_data_response->datasetResultDto->totalHits : 0,
      'dataset_totalCount' => !empty($dto_data_response->datasetResultDto->totalCount) ?
          $dto_data_response->datasetResultDto->totalCount : 0
    );
  }

  public function search_variables() {
    $data_response = $this->_search_resource();
    if (!empty($data_response->variableResultDto)) {
      $dto_data_response = $data_response->variableResultDto;
      /*ad to session aggregation from other dto entities*/
      $this->session_facets_builder($data_response);
      $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
      $dtos ['data'] = $summaries_variables;
      $dtos = $this->get_stats_entities_count($dtos, $data_response);
      return $dtos;
    }
    return NULL;
  }

  public function search_studies() {
    $data_response = $this->_search_resource();
    if (!empty($data_response->studyResultDto)) {
      $dto_data_response = $data_response->studyResultDto;
      $this->session_facets_builder($data_response);
      $summaries_studies = !empty($dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries) ?
        $dto_data_response->{'obiba.mica.StudyResultDto.result'}->summaries : NULL;
      $dtos = array();
      $dtos ['data'] = $summaries_studies;
      if (!empty($dto_data_response)) {
        $dtos = $this->get_stats_entities_count($dtos, $data_response);
      }
      else {
        $dtos ['study-totalHits'] = 0;
      }
      return $dtos;
    }
    else {
      return NULL;
    }
  }

  public function search_networks() {
    $data_response = $this->_search_resource();
    if (!empty($data_response->networkResultDto)) {
      $dto_data_response = $data_response->networkResultDto;
      /*ad to session aggregation from other dto entities*/
      $this->session_facets_builder($data_response);
      $summaries_networks = !empty($dto_data_response->{'obiba.mica.NetworkResultDto.result'}->networks) ?
        $dto_data_response->{'obiba.mica.NetworkResultDto.result'}->networks : NULL;
      $dtos ['data'] = $summaries_networks;
      $dtos = $this->get_stats_entities_count($dtos, $data_response);
      return $dtos;
    }
    else {
      return NULL;
    }
  }

  public function search_datasets() {
    $data_response = $this->_search_resource();
    if (!empty($data_response->datasetResultDto)) {
      $dto_data_response = $data_response->datasetResultDto;
      /*ad to session aggregation from other dto entities*/
      $this->session_facets_builder($data_response);
      $summaries_datasets = !empty($dto_data_response->{'obiba.mica.DatasetResultDto.result'}->datasets) ?
        $dto_data_response->{'obiba.mica.DatasetResultDto.result'}->datasets : NULL;
      $dtos ['data'] = $summaries_datasets;
      $dtos = $this->get_stats_entities_count($dtos, $data_response);
      return $dtos;
    }
    else {
      return NULL;
    }
  }


}