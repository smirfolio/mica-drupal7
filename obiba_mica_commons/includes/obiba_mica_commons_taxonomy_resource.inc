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
 * MicaStudyResource class
 */

use \Obiba\ObibaMicaClient\MicaCache as MicaCache;
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
    parent::__construct($mica_url, new MicaCache\MicaDrupalClientCache());
  }

  /**
   * Get taxonomy summaries.
   *
   * @return object
   *   The taxonomy summaries wrapper.
   */
  public function getTaxonomySummaries($resource) {
    $this->setLastResponse(NULL);
    $url_studies = $this->micaUrl . '/taxonomies/'.$resource;
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
