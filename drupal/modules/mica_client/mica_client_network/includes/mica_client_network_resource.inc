<?php

/**
 * @file
 * MicaNetworkResource class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'mica_client_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');

/**
 * Class MicaNetworkResource
 */
class MicaNetworkResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Binary);
  }

  public function get_networks($study_id = NULL) {
    $this->setLastResponse(NULL);
    $study_param = !empty($study_id) ? '&study=' . $study_id : '';
    $url_networks = $this->micaUrl . '/networks?limit=-1' . $study_param;

    $request = new HttpClientRequest($url_networks, array(
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
      return json_decode($data);
    } catch (HttpClientException $e) {
      return array();
    }
  }

  public function get_network($network_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/network/' . $network_id;

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_BINARY),
          )
        ),
    ));

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      $dtoObj = '\obiba\mica\NetworkDto';
      Protobuf::setDefaultCodec(new Protobuf\Codec\Binary);
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    } catch (HttpClientException $e) {
      return array();
    }
  }

}