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

/**
 * Class MicaStudyResource
 */
class MicaStudyResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  public function studies() {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/studies/_search';

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
      dpm(json_decode($data));
      $_SESSION['aggregations'] = json_decode($data)->aggs;
      $dtoObj = '\obiba\mica\StudySummaryDto';
      $dtos = array();
      if ($data) {
        foreach (json_decode($data)->summaries as $study) {
          $dtos [] = Protobuf::decode($dtoObj, json_encode($study));
        }
      }

      return $dtos;
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public function study($study_id) {
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