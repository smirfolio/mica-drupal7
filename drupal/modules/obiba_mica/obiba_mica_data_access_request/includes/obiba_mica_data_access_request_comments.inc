<?php

/**
 * @file
 * MicaDataAccessRequestComments class
 */

$path_module_data_access = drupal_get_path('module', 'obiba_mica_data_access_request');

include_once($path_module_data_access . '/includes/obiba_mica_data_access_resources.inc');

/**
 * Class MicaDataAccessRequestComments
 */
class MicaDataAccessRequestComments extends MicaDataAccessRequestResources {

  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url, $method);
  }

  public function get_comments($id, $resource) {
    dpm('MicaDataAccessRequestComments::get_comments()');
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . sprintf('/%s/%s/comments', $resource, $id);
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