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
 * Data access request resources class
 */

$path_module_data_access = drupal_get_path('module', 'obiba_mica_data_access_request');

include_once $path_module_data_access . '/includes/obiba_mica_data_access_resources.inc';

/**
 * Class MicaDataAccessRequests
 */
class MicaDataAccessRequests extends DrupalMicaDataAccessRequestResources {

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   * @param string $method
   *   THe method to query the server.
   */
  public function __construct() {
    parent::__construct();
  }

  /**
   * Get data access requests list.
   *
   * @return array
   *   The data server response.
   */
  public function getRequests() {
    return json_decode($this->sendGet('/data-access-requests', 'HEADER_JSON'));
  }

  public function downloadCsvExport($resource) {

    return $this->downloadFileGet($resource, array('HEADER_CSV'));
//
//    $request = new HttpClientRequest($url_data_access_request_csv_export, array(
//      'method' => HttpClientRequest::METHOD_GET,
//      'headers' => $this->authorizationHeader(array(
//          'Accept' => array(parent::HEADER_CSV),
//        )
//      ),
//    ));
//    $client = $this->client();
//    try {
//      $client->execute($request);
//      $this->setLastResponse($client->lastResponse);
//      return $client->lastResponse;
//    }
//    catch (HttpClientException $e) {
//      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
//        array(
//          '@code' => $e->getCode(),
//          '@message' => $e->getMessage()
//        ), WATCHDOG_WARNING);
//      return array();
//    }
  }
}
