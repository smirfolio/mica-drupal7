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
class MicaDataAccessRequests extends MicaDataAccessRequestResources {

  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url, $method);
  }

//
  public function get_requests() {
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-requests';

    $request = new HttpClientRequest($url_requests, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));

    return $this->execute($request);
  }

}