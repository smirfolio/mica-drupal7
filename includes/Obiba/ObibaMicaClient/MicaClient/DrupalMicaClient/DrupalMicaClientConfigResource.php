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

namespace Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient;

use Obiba\ObibaMicaClient\MicaCache as MicaCache;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;
use Obiba\ObibaMicaClient\MicaHttpClient as MicaHttpClient;

/**
 * Class MicaConfigResource
 */
class MicaClientConfigResource extends MicaClient {
  const CONFIG_WS_URL = '/config/_public';
  const ALL_CONFIG_WS_URL = '/config';

  /**
   * Instance initialisation.
   *
   * @param string $mica_url
   *   The mica server url.
   */
  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url,
      new MicaCache\MicaDrupalClientCache(),
      new MicaConfig\MicaDrupalConfig(),
      new MicaWatchDog\MicaDrupalClientWatchDog()
    );
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
      foreach ($configs as $config) {
        $specific_configs[$config] = $all_config->{$config};
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
    $cached_config = $this->drupalCache->MicaGetCache($config_resource);
    if (!empty($cached_config)) {
      return $cached_config;
    }
    else {
      $request = new MicaHttpClient\DrupalMicaHttpClient();
        $request->httpGet($config_resource)
        ->httpSetAcceptHeaders(array($request::HEADER_JSON))
        ->httpAuthorizationHeader();
      $response = $request->send();
      if (!empty($response)) {
        $this->drupalCache->MicaSetCache($config_resource, $response);
        return $response;
      }
    }
    return array();
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
    $lang_resource = '/config/i18n/' . $locale . '.json';

    $cached_lang = $this->drupalCache->MicaGetCache($lang_resource);
    if (!empty($cached_lang)) {
      return $cached_lang;
    }
    else {
      $request = new MicaHttpClient\DrupalMicaHttpClient();
      $request->httpGet($lang_resource)
        ->httpSetAcceptHeaders(array($request::HEADER_JSON))
        ->httpAuthorizationHeader();
      $response = $request->send();
      if (!empty($response)) {
        $this->drupalCache->MicaSetCache($lang_resource, $response);
        return $response;
      }
    }
    return array();
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
