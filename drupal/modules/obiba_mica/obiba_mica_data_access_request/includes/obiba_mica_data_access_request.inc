<?php

/**
 * @file
 * MicaStudyResource class
 */

$path_module_data_access = drupal_get_path('module', 'obiba_mica_data_access_request');

include_once($path_module_data_access . '/includes/obiba_mica_data_access_resources.inc');

/**
 * Class MicaStudyResource
 */
class MicaDataAccessRequest extends MicaDataAccessRequestResources {

  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url, $method);
  }

  public function get_form_definition() {
    $url_studies = $this->micaUrl . '/config/data-access-form';
    $request = new HttpClientRequest($url_studies, array(
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
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return $e->getResponse();
    }
  }

  public function get_request($id) {
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id;
    $request = new HttpClientRequest($url_requests, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));

    return $this->execute($request);
  }

  public function download_pdf($id) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id . '/_pdf';

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));
    $client = $this->client();
    try {
      $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      $headers = $this->getLastResponseHeaders();
      $responses['response'] = $this->getLastResponse();
      $responses['headers'] = $headers;
      return $responses;
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return $e->getResponse();
    }

  }

  public function delete_request($id) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id;

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));

    return $this->execute($request);
  }

}