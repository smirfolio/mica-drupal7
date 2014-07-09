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
class MicaStudyResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  public function studies() {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/studies';

    $request = new HttpClientRequest($url, array(
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
      dpm(json_decode($data));
      $dtoObj = '\obiba\mica\StudySummaryDto';
      $dtos = array();
      if ($data) {
        foreach (json_decode($data) as $study) {
          $dtos [] = Protobuf::decode($dtoObj, json_encode($study));
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
          $dto_guery_term->setField($field);
          $dto_guery_term->setValues(str_replace($field . '.', '', $term_association));

        }
        $dto_guery_bool_filter->addTerms($dto_guery_term);
        $dto_guery_filter->setFilter($dto_guery_bool_filter);
      }
      if ($field == 'page') {
        dpm($term_association[0]);
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
    $nb_pages = ceil($_SESSION['aggregations']['totalHits'] / parent::SIZE_RESPONSE);
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
    $premiereEntree = ($pageActuelle - 1) * parent::SIZE_RESPONSE; // On calcul la première entrée à lire
    return $premiereEntree;
  }

  private function _session_facets_builder($aggregations) {
    $current_session_aggregations = $_SESSION['aggregations'];
    if (!empty($aggregations->totalHits)) {
      $_SESSION['aggregations'] = $aggregations->aggs;
      $_SESSION['aggregations']['totalHits'] = $aggregations->totalHits;
    }
  }

  public
  function studies_search($request_param) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/studies/_search';

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

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      dpm(json_decode($data));
      $dto_data_response = json_decode($data);
      $this->_session_facets_builder($dto_data_response);

      $dtoObj = '\obiba\mica\StudySummaryDto';
      $dtos = array();
      $ummarier_data = !empty($dto_data_response->summaries) ? $dto_data_response->summaries : NULL;
      if ($ummarier_data) {
        foreach ($dto_data_response->summaries as $study) {
          $dtos ['data'][] = Protobuf::decode($dtoObj, json_encode($study));
        }
      }
      $dtos ['totalHits'] = $dto_data_response->totalHits;
      return $dtos;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public
  function study($study_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/study/' . $study_id;

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
      $dtoObj = '\obiba\mica\StudyDto';
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

}