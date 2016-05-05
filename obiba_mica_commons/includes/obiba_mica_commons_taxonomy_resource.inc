<?php

/**
 * @file
 * MicaStudyResource class
 */

/**
 * Class MicaStudyResource
 */
class MicaTaxonomyResource extends MicaClient {

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The Mica server url.
   */
  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    DrSlump\Protobuf::setDefaultCodec(new DrSlump\Protobuf\Codec\Binary());
  }

  /**
   * Get taxonomy summaries.
   *
   * @return object
   *   The taxonomy summaries wrapper.
   */
  public function getTaxonomySummaries() {
    $this->setLastResponse(NULL);
    $url_studies = $this->micaUrl . '/taxonomies/_summary';
    $request = new HttpClientRequest($url_studies, array(
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
      watchdog('MicaTaxonomyResource', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return array();
    }
  }

}
