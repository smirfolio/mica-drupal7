<?php

/**
 * @file
 * MicaNetworkResource class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'obiba_mica_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');
include_once($path_module_protos . '/protos/MicaSearch.php');

/**
 * Class MicaNetworkResource
 */
class MicaNetworkResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
    Protobuf::setDefaultCodec(new Protobuf\Codec\Binary);
  }

  /**
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
    $url_networks = $this->micaUrl . '/networks/_search?' . $params;

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
      return new NetworkJoinResponseWrapper(json_decode($data));
    }
    catch (HttpClientException $e) {
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return array();
    }
  }

  /**
   * Get a network by its ID.
   *
   * @param $network_id
   * @return array|Protobuf\Message|null
   */
  public function get_network($network_id) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/network/' . rawurlencode($network_id);

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
      Protobuf::setDefaultCodec(new Protobuf\Codec\Binary);
      return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    }
    catch (HttpClientException $e) {
      return array();
    }
  }

}