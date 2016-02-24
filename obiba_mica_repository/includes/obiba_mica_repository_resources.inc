<?php

/**
 * @file
 * Mica networks file
 */
class ObibaSearchResources extends MicaSearchResource {
  const MICA_REPOSITORY = 'repository';
  var $last_reponse;

  function __construct() {
    parent::__construct();
  }

  private function httpRequestGetBuilder($resources, $header_accept = parent::HEADER_JSON) {
    $url = $this->micaUrl . $resources;

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array($header_accept),
          'Content-Type' => array($header_accept)
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
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);
      dpm($e->getMessage());
      return array();
    }
  }

  private function queryLocalBuilder($query) {

  }

  public function searchQuery($type, $query) {
    $this->queryLocalBuilder($query);
    return $this->httpRequestGetBuilder('/' . $type . '/_rql?query=' . $query);
  }

  public function taxonomiesSearch($query) {
    return $this->httpRequestGetBuilder('/taxonomies/_search?query=' . $query);
  }

  public function taxonomiesFilter($entity) {
    return $this->httpRequestGetBuilder('/taxonomies/_filter?target=' . $entity);
  }

  public function variablesCoverage($query) {
    return $this->httpRequestGetBuilder('/variables/_coverage?query=' . $query);
  }

  public function variablesCoverageDownload($query, $header_accept) {
    return $this->httpRequestGetBuilder('/variables/_coverage_download?query=' . $query, $header_accept);
  }

}
