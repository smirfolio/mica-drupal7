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
 * MicaNetworkResource class
 */
use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient as DrupalMicaClient;

/**
 * Class MicaNetworkResource
 */
class DrupalMicaNetworkResource extends DrupalMicaClientResource {

  public function __construct(){
    parent::__construct();
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
    $from = empty($from) ? '0' : $from;
    $limit = empty($limit) ? '5' : $limit;
    $order = empty($order) ? '' : ($order == 'desc' ? '-' : '');
    $sort_rql_bucket = empty($sort) ? "" : ",sort($order$sort)";
    $query = empty($query) ? NULL : ",match($query,(Mica_network.name,Mica_network.acronym,Mica_network.description))";
    $studies_query = empty($study_id) ? '' : ",in(Mica_network.studyIds," . rawurlencode($study_id) . ")";
    if (!empty($query || $studies_query)) {
      $params = "network(limit($from,$limit)$query$studies_query$sort_rql_bucket)";
    }
    else {
      $params = "network(exists(Mica_network.id),limit($from,$limit)$sort_rql_bucket)";
    }
    $params .= ",locale($language->language)";
    $resource_query = '/networks/_rql?query=' . $params;

    $cache_stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cache_stored_data)) {
      return $cache_stored_data;
    }
    else {
      $response = $this->sendGet($resource_query, 'HEADER_JSON');
      if (!empty($response)) {
        $result_data = json_decode($response);
        $result_resource_query = new DrupalMicaClient\NetworkJoinResponseWrapper($result_data);
        $has_summary = $result_resource_query->hasSummaries();
        if (!empty($has_summary)) {
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $result_resource_query);
          return $result_resource_query;
        }
      }
    }
    return FALSE;
  }


  /**
   * Get the list of network details.
   *
   * @param null $networkIds
   * @return array|mixed
   */
  public function getNetworkDetails($networkIds) {
    $this->setLastResponse(NULL);
    $resource_query = '/networks/_rql?query=' . DrupalMicaClient\RqlQueryBuilder::networks($networkIds);
    $cache_stored_data = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cache_stored_data)) {
      return $cache_stored_data;
    }
    else {
      $response = $this->sendGet($resource_query, 'HEADER_JSON');
      $response_network = json_decode($response);
      if (!empty($response_network->networkResultDto) && !empty($response_network->networkResultDto->{'obiba.mica.NetworkResultDto.result'})) {
        $result_resource_query = $response_network->networkResultDto->{'obiba.mica.NetworkResultDto.result'};
      }
      if (!empty($result_resource_query)) {
        $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $result_resource_query);
        return $result_resource_query;
      }

    }
    return FALSE;
  }

  /**
   * Get a network by its ID.
   *
   * @param $network_id
   * @return array
   */
  public function getNetwork($network_id) {
    $resource_query = '/network/' . rawurlencode($network_id);

    $cached_network = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if (!empty($cached_network)) {
      return $cached_network;
    }
    else {
      $response = $this->sendGet($resource_query, 'HEADER_JSON');
      if (!empty($response)) {
        $network_response = json_decode($response);
        $this->updateModel($network_response);
        $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $network_response);
        return $network_response;
      }
    }
    return FALSE;
  }


  private function updateModel($obj) {
    if (!empty($obj->content)) {
      $obj->model = json_decode($obj->content);
    }
    else {
      $obj->model = new stdClass();
    }
  }
}