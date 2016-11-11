<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * TempFile resource class used to communicate with backend server
 */
namespace Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient;

use Obiba\ObibaMicaClient\MicaCache as MicaCache;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;

/**
 * Class MicaDataAccessRequest
 */
class DrupalMicaTempFileResource extends MicaClient {
  const FILES_WS_URL = '/files/temp';
  const FILE_WS_URL = '/files/temp/{id}';
  public $method;
  public $curlAuth;
  protected $request;
  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   * @param string $method
   *   THe method to query the server.
   */
  public function __construct($mica_url = NULL, $method = 'METHOD_POST') {
    parent::__construct($mica_url,
      new MicaCache\MicaDrupalClientCache(),
      new MicaConfig\MicaDrupalConfig(),
      new MicaWatchDog\MicaDrupalClientWatchDog());
    $this->method = $method;
    $this->request = $this->getResponseRequest();
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

    $headers = $this->request->HttpGetHeaders($result);

    if (!empty($headers) && !empty($headers['Location'])) {
      $this->request->drupalMicaClientAddHttpHeader('Location', $headers['Location'][0]);
    }

    $this->request->drupalMicaClientAddHttpHeader('Status', $http_code);

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
    return $this->sendGet(preg_replace('/\\{id\\}/', $id_file, self::FILE_WS_URL, 1),'HEADER_JSON');
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
    $this->setLastResponse(NULL);
    $url_requests = $this->micaUrl . preg_replace('/\\{id\\}/', $id_file, self::FILE_WS_URL, 1);

    $request = $this->getMicaHttpClientRequest($url_requests,
      array('method' => $this->getMicaHttpClientStaticMethod($this->method)));

    $this->micaClientAddHttpHeader('Status', $this->getLastResponseStatusCode());
    return array('Status' => $request->statusCode);
  }

  /**
   * Sets up cURL and return a $resource
   * @param $file
   * @return resource
   */
  private function initializeCurl(array $file) {
    $file_info = new \finfo(FILEINFO_MIME);
    $mime_file = $file_info->file($file['file']['tmp_name']);
    $cfile = new \CurlFile($file['file']['tmp_name'], $mime_file, $file['file']['name']);
    $data_file = array('file' => $cfile);
    $url = $this->micaUrl . '/ws'. self::FILES_WS_URL;
    $curl_handle = curl_init();
    $accept_header = $this->request->getRequestConst('HEADER_JSON');
    $requestAuth = $this->request->httpAuthorizationHeader(array());
    curl_setopt($curl_handle, CURLOPT_URL, $url);
    curl_setopt($curl_handle, CURLOPT_HEADER, TRUE);
    curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($curl_handle, CURLINFO_HEADER_OUT, TRUE);
    curl_setopt($curl_handle, CURLOPT_POST, 1);

    curl_setopt($curl_handle, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($curl_handle, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($curl_handle, CURLOPT_POSTFIELDS, $data_file);
    curl_setopt($curl_handle, CURLOPT_HTTPHEADER, array(
      'Accept' => $accept_header,
      'Content-Type' => 'multipart/form-data',
    ));

    if (!empty($requestAuth->headers['Cookie'])) {
      foreach ($requestAuth->headers['Cookie'] as $cookie) {
        curl_setopt($curl_handle, CURLOPT_COOKIE, $cookie);
      }
    }
$this->curlAuth = array(
  'CURLOPT_URL' => $url,
  'CURLOPT_POST' =>1,
  'CURLOPT_POSTFIELDS' => $data_file,
  'CURLOPT_HTTPHEADER' => array(
    'Accept' => $accept_header,
    'Content-Type' => 'multipart/form-data',
  ),
  'CURLOPT_COOKIE' => $cookie
);
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
          $this->drupalWatchDog->MicaWatchDog('Mica Client',
            'Connection to server fail,  Error serve code : @code, message: @message',
            array(
              '@code' => $http_code,
              '@message' => $message,
            ), $this->drupalWatchDog->MicaWatchDogSeverity('WARNING'));
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
    catch (\HttpClientException $e) {
      $this->drupalWatchDog->MicaWatchDog('Mica Client',
        'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ), $this->drupalWatchDog->MicaWatchDogSeverity('WARNING'));

      $this->micaClientAddHttpHeader('Status', $e->getCode());
      return empty($client->lastResponse->body) ? FALSE : json_decode($client->lastResponse->body);
    }

  }

}
