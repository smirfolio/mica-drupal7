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
 * TempFile resource class used to communicate with backend server
 */

/**
 * Class MicaConfigResource
 */
class MicaConfigResource extends MicaClient {
  const CONFIG_WS_URL = '/config/_public';
  const ALL_CONFIG_WS_URL = '/config';

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   */
  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  /**
   * Get public configuration.
   *
   * @return object
   *   The Mica server public configuration.
   */
  public function getConfig() {
    return $this->config();
  }

  /**
   * Get roles memberships .
   *
   * @param $configs
   *   The config to query.
   *
   * @return object
   *   The specific configurations.
   */
  public function getSpecificConfigs($configs = array()) {
    $specific_configs = array();
    $all_config = $this->config(self::ALL_CONFIG_WS_URL);
    if (!empty($configs)) {
      foreach($configs as $config){
        $specific_configs[$config]=$all_config->{$config};
      }
      return $specific_configs;
    }
    return FALSE;
  }

  /**
   * Get public configuration.
   *
   * @param $config_resource
   *   The config resource url.
   *
   * @return object
   *   The Mica server public configuration.
   */
  private function config($config_resource = self::CONFIG_WS_URL) {
    $this->setLastResponse(NULL);
    $this->drupalCache->MicaGetCache($config_resource);
    if (!isset($this->result_resource_query)) {
      $url = $this->micaUrl . $config_resource;

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
        $config_client = json_decode($data);
        if (!empty($config_client)) {
          $this->result_resource_query = $config_client;
          $this->drupalCache->MicaSetCache($config_resource, $config_client);
        }
      } catch (HttpClientException $e) {
        watchdog('MicaConfigResource', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        return array();
      }
    }
    return $this->result_resource_query;
  }

  /**
   * Get translations.
   *
   * @param string $locale
   *   The locale to get translations for.
   * @return object
   *   The Mica server translations resource.
   */
  public function getTranslations($locale) {
    $this->setLastResponse(NULL);
    $url = $this->micaUrl . '/config/i18n/' . $locale . '.json';
    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_GET,
      'headers' => array(
        'Accept' => array(parent::HEADER_JSON),
      ),
    ));
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return $data;
    } catch (HttpClientException $e) {
      watchdog('MicaConfigResource', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        ), WATCHDOG_WARNING);
      return array();
    }
  }

  /**
   * Get whether the published documents are accessible by anonymous user.
   *
   * @return bool
   */
  public function isOpenAccess() {
    $config = $this->getConfig();
    if (empty($config)) {
      return TRUE;
    }
    else {
      return $config->openAccess;
    }
  }

  /**
   * Get public URL from the server configuration.
   *
   * @return null
   */
  public function getPublicURL() {
    $config = $this->getConfig();
    if (empty($config) || empty($config->publicUrl)) {
      return NULL;
    }
    else {
      return $config->publicUrl;
    }
  }
}
