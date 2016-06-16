<?php

/**
 * @file
 * Research project resource class
 */

/**
 * Class MicaResearchProjectResource
 */
class MicaResearchProjectResource extends MicaClient {

  /**
   * MicaResearchProjectResource constructor.
   *
   * @param null|string $mica_url
   * @param string $method
   */
  public function __construct($mica_url, $method = 'METHOD_POST') {
    parent::__construct($mica_url);
  }

  /**
   * @param null $query
   * @param int $from
   * @param int $limit
   * @param null $sort
   * @param null $order
   * @return array|mixed
   */
  public function getProjects($query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=5' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;
    $resource_query = '/projects?' . $params;

    $this->getCache($resource_query);
    if (!isset($this->result_resource_query)) {
      $url_projects = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url_projects, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON)
          )
        )
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $this->result_resource_query = json_decode($data);
      } catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        $this->result_resource_query = NULL;
        return array();
      }
    }
    return $this->result_resource_query;
  }

  /**
   * @param $project_id
   * @return array|null
   */
  public function getProject($project_id) {
    $resource_query = '/project/' . rawurlencode($project_id);
    $this->setLastResponse(NULL);
    $this->getCache($resource_query);
    $url = $this->micaUrl . $resource_query;
    if (!isset($this->result_resource_query)) {
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON)
          )
        ),
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $this->result_resource_query = json_decode($data);
        obiba_mica_commons_set_cache($resource_query, $this->result_resource_query);
        return $this->result_resource_query;
      } catch (HttpClientException $e) {
        $this->result_resource_query = NULL;
      }
      return array();
      
    }    
    return $this->result_resource_query;
  }

  public function getFormDefinition() {
    $url = $this->micaUrl . '/config/project-form';
    $this->setLastResponse(NULL);
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
        )
      ),
    ));
    $client = $this->client();
    try {
      $response = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return json_decode($response);
    } catch (HttpClientException $e) {
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