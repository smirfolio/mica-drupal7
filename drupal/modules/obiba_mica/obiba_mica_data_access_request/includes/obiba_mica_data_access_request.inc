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

  public function download_attachment($id_request, $id_file) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id_request . '/' . 'attachments/' . $id_file . '/_download';

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

  public function status_update_request($id, $status) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/data-access-request/' . $id . '/_status?to=' . $status;

    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));

    return $this->execute($request);
  }

  public function get_file($id_file, $resource = 'files/temp') {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . '/' . $resource . '/' . $id_file;
    $request = new HttpClientRequest($url_requests, array(
      'method' => $constant_method,
      'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
    ));

    return $this->execute($request);
  }

  public function upload_file($file) {
    $header = $this->authorizationHeader(array());

    $file_info = new finfo(FILEINFO_MIME);
    $mime_file = $file_info->file($file['file']['tmp_name']);
    $cfile = new CurlFile($file['file']['tmp_name'], $mime_file, $file['file']['name']);
    $data_file = array('file' => $cfile);
    $url = $this->micaUrl . '/files/temp';
    $resource = curl_init();
    curl_setopt($resource, CURLOPT_URL, $url);
    curl_setopt($resource, CURLOPT_HEADER, TRUE);
    curl_setopt($resource, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($resource, CURLINFO_HEADER_OUT, TRUE);
    curl_setopt($resource, CURLOPT_POST, 1);

    curl_setopt($resource, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($resource, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($resource, CURLOPT_POSTFIELDS, $data_file);
    curl_setopt($resource, CURLOPT_HTTPHEADER, array(
      'Accept' => $this::HEADER_JSON,
      'Content-Type' => 'multipart/form-data'
    ));
    foreach ($header['Cookie'] as $cookie) {
      curl_setopt($resource, CURLOPT_COOKIE, $cookie);
    }

    $result = curl_exec($resource);
    $http_code = curl_getinfo($resource, CURLINFO_HTTP_CODE);

//Deal with the server errors
    if ($http_code != 201) {
      if (preg_match_all('/(?<=HTTP\/1\.1).*/', $result, $error_meesage)) {
        foreach ($error_meesage[0] as $message) {
          if (!preg_match('/(?<= 100 ).*/', $message, $code)) {
            watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
              array('@code' => $http_code, '@message' => $message), WATCHDOG_WARNING);
            return array('code' => $http_code, 'message' => $message);
          }
        }
      }
    }
    if (preg_match('/(?<=files\/temp\/).*/', $result, $group)) {
      $match = $group[0];
    }
    curl_close($resource);
    return array('code' => $http_code, 'message' => trim($match));
  }

}