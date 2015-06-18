<?php

/**
 * @file
 * MicaStudyResource class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'obiba_mica_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');


/**
 * Class MicaStudyResource
 */
class MicaDataAccessRequestResources extends MicaClient {

  protected $method;

  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url);
    $this->method = $method;
  }

  public function data_access_save($data, $id_data_access = NULL, $resource) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $url_data_access = $this->micaUrl . $resource . ($id_data_access ? '/' . $id_data_access : '');
    $request = new HttpClientRequest($url_data_access, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
            'Content-Type' => array(parent::HEADER_JSON),

          )
        ),
      'data' => $data,
    ));

    return $this->execute($request);
  }

  protected function execute($request) {
    $client = $this->client();
    try {
      $response = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return json_decode($response);
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
//      drupal_set_message(t('An error occurred and processing did not complete Mica Server error: @message',
//        array('@message' => $e->getMessage())), 'error');
      drupal_add_http_header('Status', $e->getCode());
      return empty($client->lastResponse->body) ? FALSE : $client->lastResponse->body;
    }

  }

}