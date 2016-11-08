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
 * MicaClient class
 */

namespace Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient;

use Obiba\ObibaMicaClient\MicaCache as MicaCache;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;
use Obiba\ObibaMicaClient\MicaHttpClient as MicaHttpClient;

/**
 * Class DrupalMicaClient
 */
class MicaClient {

  private $lastResponse;
  private static $responsePageSizeSmall = 10;
  private static $responsePageSize = 20;


  /**
   * Instance initialisation.
   *
   * Mica client from a given url or from the one retrieved from 'mica_url'
   * variable.
   *
   * @param string $micaUrl
   * @param MicaCache\MicaCacheInterface $micaCache
   * @param MicaConfig\MicaConfigInterface $micaConfig
   * @param MicaWatchDog\MicaWatchDogInterface $micaWatchDog
   *   IF given,  the Mica server url, the  default value is a a setting
   *   parameter
   *
   */
  public function __construct($micaUrl = NULL,
                              MicaCache\MicaCacheInterface $micaCache,
                              MicaConfig\MicaConfigInterface $micaConfig,
                              MicaWatchDog\MicaWatchDogInterface $micaWatchDog) {
    $this->drupalCache = $micaCache;
    $this->drupalConfig = $micaConfig;
    $this->drupalWatchDog = $micaWatchDog;
    $this->micaUrl = (isset($micaUrl) ? $micaUrl : $this->drupalConfig->MicaGetConfig('mica_url')) . '/ws';
    self::$responsePageSize = $this->drupalConfig->MicaGetConfig('mica_response_page_size');
    self::$responsePageSizeSmall = $this->drupalConfig->MicaGetConfig('mica_response_page_size_small');

  }

  /**
   * Make sure we are not using previous session state.
   */
  public static function clear() {
    unset($_SESSION[MicaHttpClient\DrupalMicaHttpClient::MICA_COOKIE]);
  }

  /**
   * Send a logout request to Mica and clean drupal client cookies.
   */
  public function logout() {
    $request = new MicaHttpClient\DrupalMicaHttpClient($this->micaUrl);
    $request->httpGet('/auth/session/_current')
      ->httpSetAcceptHeaders($request::HEADER_JSON)
      ->httpAuthorizationHeader();
    $response = $request->send();

    if (!empty($response)) {
      unset($_SESSION[$request::MICA_COOKIE]);
    }
    else {
      unset($_SESSION[$request::MICA_COOKIE]);
    }
  }

  /**
   * GEt the setting of the samll page size response (for pagination).
   *
   * @return int
   *   The page size.
   */
  public
  static function getResponsePageSizeSmall() {
    return self::$responsePageSizeSmall;
  }

  /**
   * GEt the setting of the page size response (for pagination).
   *
   * @return int
   *   The page size.
   */
  public
  static function getResponsePageSize() {
    $size = empty($_GET['size']) ? self::$responsePageSize : $_GET['size'];
    return $size;
  }

  /**
   * The search list pagination parameters.
   *
   * @param int $current_page
   *   The current page number
   * @param string $type
   *   The entity type.
   * @param int $size
   *   The size server response.
   *
   * @return float|int
   *   The next page offset.
   */
  public function paginationListSearchParameters($current_page = 0, $type = NULL, $size = NULL) {
    return self::nextPageOffset(
      empty($current_page) ? 0 : $current_page,
      empty($size) ? MicaClient::getResponsePageSize() : $size,
      @$_SESSION[strtolower($type)]['aggregations']['total_hits']
    );
  }

  /**
   * Calculate the next offset page.
   *
   * @param int $current_page
   *   The current page number.
   * @param int $size
   *   The size server response.
   * @param int $total
   *   The total in server.
   *
   * @return int
   *   The next page offset.
   */
  public static function nextPageOffset($current_page = 0, $size = NULL, $total = NULL) {
    $nb_pages = ceil($total / $size);
    $from = 0;
    if (!empty($current_page)) {
      $actual_page = intval($current_page);
      if ($actual_page > $nb_pages) {
        $actual_page = $nb_pages;
      }
      $from = ($actual_page) * $size;
    }

    return $from;
  }

  /**
   * Get the file extension from file resource.
   *
   * @param string $file_resource
   *   The file name.
   *
   * @return string
   *   The file extension.
   */
  protected function getFileExtension($file_resource) {
    $file_array = explode('.', $file_resource);
    $extension_file = count($file_array);

    return $file_array[$extension_file - 1];
  }

  /**
   * Deal with downloadable resources from server (Images, attachments).
   *
   * @param string $entity_type
   *   Study, dce, network ...
   * @param string $entity_id
   *   The id of the entity.
   * @param string $file_id
   *   The id of the stored file on the server.
   *
   * @return array
   *   containing :
   *    data : The raw file to download
   *    filename : The real file name of the file
   *    raw_header_array : the raw of header response
   *    or in case of error
   *    code : the error code
   *    message : the error message
   */
  public function downloadFile($entity_type, $entity_id, $file_id) {
    $url = $this->micaUrl . "/" . $entity_type . "/" . $entity_id . "/file/" . $file_id . "/_download";
    $request = $this->getMicaHttpClientRequest($url, array(
      'method' => $this->getMicaHttpClientStaticMethod('METHOD_GET'),
      'headers' => self::authorizationHeader(array(
          'Accept' => array(self::HEADER_BINARY),
        )
      ),
    ));

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      $file_name = $this->getPropertyValueFromHeaderArray($this->parseHeaders($client->lastResponse->headers),
        'filename',
        'Content-Disposition'
      );

      $raw_data = array(
        'extension' => $this->getFileExtension($file_name),
        'data' => $data,
        'filename' => $file_name,
        'raw_header_array' => $this->parseHeaders($client->lastResponse->headers),
      );
      return $raw_data;
    } catch (\HttpClientException $e) {
      $this->drupalWatchDog->MicaWatchDog(
        'MicaClient',
        'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ),
        $this->drupalWatchDog->MicaWatchDogSeverity('WARNING'));
      return $raw_data = array(
        'code' => $e->getCode(),
        'message' => $e->getMessage(),
      );
    }

  }
}
