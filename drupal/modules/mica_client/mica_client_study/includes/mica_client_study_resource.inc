<?php

/**
 * @file
 * AgateClient class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'mica_client_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');

/**
 * Class MicaClient
 */
class MicaClient {

  const SET_COOKIE_HEADER = 'Set-Cookie';

  const OBIBA_COOKIE = 'obibaid';

  const MICA_COOKIE = 'micasid';

  const HEADER_BINARY = 'application/x-protobuf';

  const HEADER_JSON = 'application/json';

  private $micaUrl;

  private $lastResponse;

  public function __construct($mica_url) {
    $this->micaUrl = $mica_url . '/ws';
  }

  /**
   * Get the last response (if any).
   * @return mixed
   */
  public function getLastResponse() {
    return $this->lastResponse;
  }

  public function studies() {
    $this->lastResponse = NULL;
    $url = $this->micaUrl . '/studies';

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => array(
        'Accept' => array(HEADER_JSON),
        'Cookie' => array($this->authorizationHeader())
      )
    ));

    $client = $this->client();
    try {
      $body = $client->execute($request);
      $this->lastResponse = $client->lastResponse;

      $dtoObj = '\obiba\mica\StudySummaryDto';

      $dtos = array();
      if ($body) {
        foreach (json_decode($body) as $study) {
          $dtos [] = Protobuf::decode($dtoObj, json_encode($study));
        }
      }

      return $dtos;
    } catch (HttpClientException $e) {
      return array();
    }
  }



  private function authorizationHeader() {
    $cookie = null;

    if (isset($_COOKIE[OBIBA_COOKIE])) {
      $cookie = OBIBA_COOKIE . '=' . $_COOKIE[OBIBA_COOKIE];

      if (isset($_COOKIE[MICA_COOKIE])) {
        $cookie = $cookie . '; ' . MICA_COOKIE . '=' . $_COOKIE[MICA_COOKIE];
      }
    }

    return $cookie;
  }

  /**
   * @return HttpClient
   */
  private function client() {
    $client = new HttpClient($formatter = FALSE);

    if (!isset($client->options['curlopts'])) {
      $client->options['curlopts'] = array();
    }

    $client->options['curlopts'] += array(
      CURLOPT_SSLVERSION => 3,
      CURLOPT_SSL_VERIFYHOST => FALSE,
      CURLOPT_SSL_VERIFYPEER => FALSE
    );

    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());

    return $client;
  }
}