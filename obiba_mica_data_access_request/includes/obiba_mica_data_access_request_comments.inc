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

  const resource_path = '%s/%s/comments';

  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url, $method);
  }

  public function save_comment($comment, $id, $resource) {
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . sprintf(self::resource_path, $resource, $id);
    $request = new HttpClientRequest($url_requests, array(
      'method' => HttpClientRequest::METHOD_POST,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
          'Content-Type' => array(parent::HEADER_TEXT)
        )
      ),
      'data' => $comment
    ));

    return $this->execute($request);
  }

  public function get_comments($id, $resource) {
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . sprintf(self::resource_path, $resource, $id);
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