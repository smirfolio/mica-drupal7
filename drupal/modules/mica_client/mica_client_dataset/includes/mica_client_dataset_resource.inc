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

  private function _normalize_parameters($request_param) {
    $requestArry = explode('&', $request_param);

    $formated_term = array();
    foreach ($requestArry as $term_association) {
      $term = explode('=', $term_association);
      if (!empty($term[1])) {
        $decoded_term = urldecode($term[0]);
        $formated_term[preg_replace('/\[[^\]]*\]/', '', $decoded_term)][] = $term[1];
      }
    }
    return $formated_term;
  }

  private function _dto_filter_construct($request_param) {
    $dto_guery = new \obiba\mica\QueryDto;
    $dto_guery_bool_filter = new \obiba\mica\BoolFilterQueryDto;
    foreach ($this->_normalize_parameters($request_param) as $field => $term_association) {
//dpm($url_param_array);
      if ($field != 'page') {
        $dto_guery_filter = new \obiba\mica\FilteredQueryDto;
        foreach ($term_association as $term) {

          $dto_guery_term = new \obiba\mica\TermsQueryDto;
          $dto_guery_term->setField(str_replace('-', '.', $field));
          $dto_guery_term->setValues(str_replace($field . '.', '', $term_association));

        }
        $dto_guery_bool_filter->addTerms($dto_guery_term);
        $dto_guery_filter->setFilter($dto_guery_bool_filter);
      }
      if ($field == 'page') {
        $dto_guery->setFrom($this->_pagination_parameters($term_association[0]));
      }
      $dto_guery->setSize(parent::SIZE_RESPONSE);
    }
    if (!empty($dto_guery_filter)) {
      $dto_guery->setFilteredQuery($dto_guery_filter);
    }

    $dto_guery->detailed = FALSE;
    dpm(json_encode($dto_guery));
    dpm($dto_guery);
    return json_encode($dto_guery);
  }

  private function _pagination_parameters($current_page = NULL) {
    $nb_pages = ceil($_SESSION['variables']['aggregations']['totalHits'] / parent::SIZE_RESPONSE);
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) // Si la valeur de $pageActuelle (le numéro de la page) est plus grande que $nombreDePages...
      {
        $pageActuelle = $nb_pages;
      }
    }
    else {
      $pageActuelle = 1; // La page actuelle est la n°1
    }
    $premiereEntree = ($pageActuelle) * parent::SIZE_RESPONSE; // On calcul la première entrée à lire
    return $premiereEntree;
  }

  private function _session_facets_builder($aggregations) {
    if (!empty($aggregations->totalHits)) {
      $_SESSION['variables']['aggregations'] = $aggregations->aggs;
      $_SESSION['variables']['aggregations']['totalHits'] = $aggregations->totalHits;
    }
  }

  public function variables_search($request_param) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/variables/' . $request_param . '/_search?size=' . parent::SIZE_RESPONSE;

    $url_parm = explode('?', $_SERVER['REQUEST_URI']);

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
      $dto_param = $this->_dto_filter_construct($url_parm[1]);
      if (empty(json_decode($dto_param)->filteredQuery)) {
        $url = $this->micaUrl . '/variables/' . $request_param . '/_search?from=' . json_decode($dto_param)->from . '&size=' . parent::SIZE_RESPONSE;
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
      $this->_session_facets_builder($dto_data_response);

      dpm($dto_data_response);

      $summaries_variables = $dto_data_response->{'obiba.mica.DatasetVariableResultDto.result'}->summaries;
      $dtoObj = '\obiba\mica\DatasetVariableResolverDto';
      $dtos = array();
      $summarier_data = !empty($summaries_variables) ? $summaries_variables : NULL;
      if ($summarier_data) {
        foreach ($summaries_variables as $variable) {
          $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($variable));
        }
      }
      $dtos ['totalHits'] = $dto_data_response->totalHits;
      return $dtos;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public function get_varaibles($resource, $dataset_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/' . $resource . '/' . $dataset_id . '/variables';
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

}