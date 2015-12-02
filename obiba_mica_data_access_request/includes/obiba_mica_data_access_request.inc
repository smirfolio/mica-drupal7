<?php

/**
 * @file
 * Data access request resources class
 */

$path_module_data_access = drupal_get_path('module', 'obiba_mica_data_access_request');

include_once $path_module_data_access . '/includes/obiba_mica_data_access_resources.inc';

/**
 * Class MicaDataAccessRequest
 */
class MicaDataAccessRequest extends MicaDataAccessRequestResources {
  const LIST_DATA_ACCESS = 'list-data-access';
  const NEW_DATA_ACCESS = 'new-data-access';
  const LIST_USERS_DATA_ACCESS = 'list-user-data-access';

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   * @param string $method
   *   THe method to query the server.
   */
  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url, $method);
  }

  /**
   * Get the form definition of data access request from mica server.
   *
   * @return string
   *   Json definition of the form (Angular schema-Form).
   */
  public function getFormDefinition() {
    $url_studies = $this->micaUrl . '/config/data-access-form';
    $request = new HttpClientRequest($url_studies, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));

    return $this->execute($request);
  }

  /**
   * Get a data access request from the server.
   *
   * @param string $id
   *   The data access request id.
   *
   * @return string
   *   Json form definition of the data access request (Angular schema-Form).
   */
  public function getRequest($id) {
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id;
    $request = new HttpClientRequest($url_requests, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));

    return $this->execute($request);
  }

  /**
   * GEt Pdf format of an data access request.
   *
   * @param string $id
   *   The data access request id.
   *
   * @return array
   *   The data server response.
   */
  public function downloadPdf($id) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id . '/_pdf';

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
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
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ), WATCHDOG_WARNING);
      return $e->getResponse();
    }

  }

  /**
   * Download data access request attachments.
   *
   * @param string $id_request
   *   The data access request id.
   * @param string $id_file
   *   The data access request id.
   *
   * @return array
   *   The data server response.
   */
  public function downloadAttachment($id_request, $id_file) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id_request . '/' . 'attachments/' . $id_file . '/_download';

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
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
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ), WATCHDOG_WARNING);
      return $e->getResponse();
    }

  }

  /**
   * Delete an data access request.
   *
   * @param string $id
   *   The data access request id.
   *
   * @return array
   *   The data server response.
   */
  public function deleteRequest($id) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id;

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));

    return $this->execute($request);
  }

  /**
   * Update data access request status.
   *
   * @param string $id
   *   The data access request id.
   * @param string $status
   *   The status to update to.
   *
   * @return array
   *   The data server response.
   */
  public function statusUpdateRequest($id, $status) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id . '/_status?to=' . $status;

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));

    return $this->execute($request);
  }

  public function getUserProfile($user_id){
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/user/' . $user_id . '/application/drupal';
    $request = new HttpClientRequest($url_requests, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      )
    ));

    return $this->execute($request);
  }

  public function getUsersList(){
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/users/application/drupal';
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
