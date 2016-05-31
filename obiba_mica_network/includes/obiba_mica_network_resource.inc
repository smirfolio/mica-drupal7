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
    DrSlump\Protobuf::setDefaultCodec(new DrSlump\Protobuf\Codec\Binary);
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
  public function get_networks($study_id = NULL, $query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    $this->setLastResponse(NULL);
    $params = empty($from) ? 'from=0' : 'from=' . $from;
    $params .= empty($limit) ? '&limit=5' : '&limit=' . $limit;
    $params .= empty($sort) ? '' : '&sort=' . $sort;
    $params .= empty($order) ? '' : '&order=' . $order;
    $params .= empty($query) ? '' : '&query=' . $query;
    $params .= empty($study_id) ? '' : '&study=' . rawurlencode($study_id);
    $resource_query = '/networks/_search?' . $params;
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
   * @return array|Protobuf\Message|null
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
            'Accept' => array(parent::HEADER_BINARY),
          )
        ),
      ));

      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $dtoObj = '\obiba\mica\NetworkDto';
        DrSlump\Protobuf::setDefaultCodec(new DrSlump\Protobuf\Codec\Binary);
        $this->result_resource_query = $data ? DrSlump\Protobuf::decode($dtoObj, $data) : NULL;
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

}