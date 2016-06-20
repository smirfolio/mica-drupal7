<?php

/**
 * @file
 * TempFile resource class used to communicate with backend server
 */

/**
 * Class MicaDataAccessRequest
 */
class MicaTempFileResource extends MicaClient {
  const FILES_WS_URL = '/files/temp';
  const FILE_WS_URL = '/files/temp/{id}';

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   * @param string $method
   *   THe method to query the server.
   */
  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url);
    $this->method = $method;
  }

  /**
   * Upload file to mica server.
   *
   * @param array $file
   *   The http $_FILE Variable to send to server.
   *
   * @return array
   *   The data server response.
   */
  public function uploadFile(array $file) {
    $curl_handle = $this->initializeCurl($file);
    $result = curl_exec($curl_handle);
    $http_code = curl_getinfo($curl_handle, CURLINFO_HTTP_CODE);
    $errors = $this->getErrors($http_code, $result);

    if (!empty($errors)) {
      return $errors;
    }

    if (preg_match('/(?<=files\/temp\/).*/', $result, $group)) {
      $match = $group[0];
    }

    curl_close($curl_handle);

    $headers = $this->getHeaders($result);

    if (!empty($headers) && !empty($headers['Location'])) {
      drupal_add_http_header('Location', $headers['Location'][0]);
    }

    drupal_add_http_header('Status', $http_code);

    return array('code' => $http_code, 'message' => trim($match));
  }

  /**
   * Resource to get temp file resource.
   *
   * @param string $id_file
   *   The file id.
   *
   * @return array
   *   The data server response.
   */
  public function getFile($id_file) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . preg_replace('/\\{id\\}/', $id_file, self::FILE_WS_URL, 1);
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
   * Resource to get temp file resource.
   *
   * @param string $id_file
   *   The file id.
   *
   * @return array
   *   The data server response.
   */
  public function deleteFile($id_file) {
    $constant_method = constant('HttpClientRequest::' . $this->method);
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . preg_replace('/\\{id\\}/', $id_file, self::FILE_WS_URL, 1);
    $request = new HttpClientRequest($url_requests, array('method' => $constant_method));

    drupal_add_http_header('Status', $this->getLastResponseStatusCode());
    return array('Status' => $request->statusCode);
  }

  /**
   * Sets up cURL and return a $resource
   * @param $file
   * @return resource
   */
  private function initializeCurl(array $file) {
    $file_info = new finfo(FILEINFO_MIME);
    $mime_file = $file_info->file($file['file']['tmp_name']);
    $cfile = new CurlFile($file['file']['tmp_name'], $mime_file, $file['file']['name']);
    $data_file = array('file' => $cfile);
    $url = $this->micaUrl . self::FILES_WS_URL;
    $curl_handle = curl_init();
    $header = $this->authorizationHeader(array());
    curl_setopt($curl_handle, CURLOPT_URL, $url);
    curl_setopt($curl_handle, CURLOPT_HEADER, TRUE);
    curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($curl_handle, CURLINFO_HEADER_OUT, TRUE);
    curl_setopt($curl_handle, CURLOPT_POST, 1);

    curl_setopt($curl_handle, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($curl_handle, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($curl_handle, CURLOPT_POSTFIELDS, $data_file);
    curl_setopt($curl_handle, CURLOPT_HTTPHEADER, array(
      'Accept' => $this::HEADER_JSON,
      'Content-Type' => 'multipart/form-data',
    ));

    if (!empty($header['Cookie'])) {
      foreach ($header['Cookie'] as $cookie) {
        curl_setopt($curl_handle, CURLOPT_COOKIE, $cookie);
      }
    }

    return $curl_handle;
  }

  /**
   * Verifies the status code and if any errors are found, returns the error data
   *
   * @param $http_code
   * @param $result
   * @return array|null
   */
  private function getErrors($http_code, $result) {
    if ($http_code != 201 && preg_match_all('/(?<=HTTP\/1\.1).*/', $result, $error_meesage)) {
      foreach ($error_meesage[0] as $message) {
        if (!preg_match('/(?<= 100 ).*/', $message, $code)) {
          watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
            array(
              '@code' => $http_code,
              '@message' => $message,
            ), WATCHDOG_WARNING);
          return array('code' => $http_code, 'message' => $message);
        }
      }
    }

    return NULL;
  }

  private function execute($request) {
    $client = $this->client();
    try {
      $response = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return json_decode($response);
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ), WATCHDOG_WARNING);

      drupal_add_http_header('Status', $e->getCode());
      return empty($client->lastResponse->body) ? FALSE : json_decode($client->lastResponse->body);
    }

  }

}
