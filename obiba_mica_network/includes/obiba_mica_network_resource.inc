<?php

/**
 * @file
 * MicaNetworkResource class
 */

/**
 * Class MicaNetworkResource
 */
class MicaNetworkResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  /**get_networks
   * Get the list of networks.
   *
   * @param null $study_id
   * @param null $query
   * @param int $from
   * @param $limit
   * @param null $sort field name to sort by
   * @param null $order "asc" or "desc"
   * @return array|mixed
   */
  public function getNetworks($study_id = NULL, $query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    global $language;
    $this->setLastResponse(NULL);
    $from = empty($from) ? '0' : $from;
    $limit = empty($limit) ? '5' : $limit;
    $order = empty($order) ? '' : ($order == 'desc' ? '-' : '');
    $sort_rql_bucket = empty($sort) ? "" : ",sort($order$sort)";
    $query = empty($query) ? NULL : ",match($query,(Mica_network.name,Mica_network.acronym,Mica_network.description))";
    $studies_query = empty($study_id)?'':",in(Mica_network.studyIds," . rawurlencode($study_id) . ")";
    if (!empty($query || $studies_query)) {
      $params = "network(limit($from,$limit)$query$studies_query$sort_rql_bucket)";
    }
    else {
      $params = "network(exists(Mica_network.id),limit($from,$limit)$sort_rql_bucket)";
    }
    $params .= ",locale($language->language)";
    $resource_query = '/networks/_rql?query=' . $params;

    $result_resource_query = obiba_mica_commons_get_cache($resource_query);
    if (empty($result_resource_query)) {
      $url_networks = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url_networks, array(
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
        $result_resource_query = new NetworkJoinResponseWrapper(json_decode($data));
        obiba_mica_commons_set_cache($resource_query, $result_resource_query);
        return $result_resource_query;
      }
      catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        return array();
      }
    }
    return $result_resource_query;
  }


  /**
   * Get the list of network details.
   *
   * @param null $networkIds
   * @return array|mixed
   */
  public function get_network_details($networkIds) {
    $this->setLastResponse(NULL);
    $resource_query = '/networks/_rql?query=' . RqlQueryBuilder::networks($networkIds);
    $result_resource_query = obiba_mica_commons_get_cache($resource_query);
    if (empty($result_resource_query)) {
      $url_networks = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url_networks, array(
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
        $response = json_decode($data);
        if (!empty($response->networkResultDto) && !empty($response->networkResultDto->{'obiba.mica.NetworkResultDto.result'})) {
          $result_resource_query = $response->networkResultDto->{'obiba.mica.NetworkResultDto.result'};
        }
        obiba_mica_commons_set_cache($resource_query, $result_resource_query);
        return $result_resource_query;
      }
      catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);

        return array();
      }
    }
    return $result_resource_query;
  }

  /**
   * Get a network by its ID.
   *
   * @param $network_id
   * @return array
   */
  public function get_network($network_id) {
    $resource_query = '/network/' . rawurlencode($network_id);
    $this->setLastResponse(NULL);
    $this->getCache($resource_query);
    $url = $this->micaUrl . $resource_query;
    if (!isset($this->result_resource_query)) {
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
        $this->result_resource_query = $data ? json_decode($data) : NULL;
        $this->updateModel($this->result_resource_query);
        obiba_mica_commons_set_cache($resource_query, $this->result_resource_query);
        return $this->result_resource_query;
      }
      catch (HttpClientException $e) {
        $this->result_resource_query = NULL;
        return array();
      }
    }

    return $this->result_resource_query;
  }


  private function updateModel($obj) {
    if (!empty($obj->content)) {
      $obj->model = json_decode($obj->content);
    } else {
      $obj->model = new stdClass();
    }
  }
}