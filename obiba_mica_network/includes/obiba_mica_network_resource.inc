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
class DrupalMicaNetworkResource  {

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
  public function getNetworks($study_id = NULL, $query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    $parameters = compact('study_id', 'query', 'from', 'limit', 'sort', 'order');
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    return $obiba->buildResourceQuery('getNetworks', $parameters)
     ->getCollections('getNetworks');
  }


  /**
   * Get the list of network details.
   *
   * @param null $networkIds
   * @return array|mixed
   */
  public function getNetworkDetails($networkIds) {
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    return  $obiba->buildResourceQuery('getNetworkDetails', $networkIds)
      ->getCollections('getNetworkDetails');
  }

  /**
   * Get a network by its ID.
   *
   * @param $network_id
   * @return array
   */
  public function getNetwork($network_id, $token_key = NULL) {
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    return  $obiba->buildResourceQuery('getNetwork', $network_id, $token_key = NULL)
      ->getDocument('getNetwork');
  }
}