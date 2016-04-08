<?php

/**
 * @file
 * TempFile resource class used to communicate with backend server
 */

/**
 * Class MicaConfigResource
 */
class MicaConfigResource extends MicaClient {
  const CONFIG_WS_URL = '/config/_public';

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   */
  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  /**
   * Get public configuration.
   *
   * @return object
   *   The Mica server public configuration.
   */
  public function getConfig() {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . CONFIG_WS_URL;
    $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
                'Accept' => array(parent::HEADER_JSON),
            )
        ),
    ));
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);

      return json_decode($data);
    }
    catch (HttpClientException $e) {
      watchdog('MicaConfigResource', 'Connection to server fail,  Error serve code : @code, message: @message',
          array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return array();
    }
  }

  /**
   * Get whether the published documents are accessible by anonymous user.
   *
   * @return bool
   */
  public function isOpenAccess() {
    $config = $this->getConfig();
    if(empty($config)) {
      return TRUE;
    }
    else {
      return $config->openAccess;
    }
  }

}
