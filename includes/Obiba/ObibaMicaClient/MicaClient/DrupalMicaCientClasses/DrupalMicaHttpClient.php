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

namespace  Obiba\ObibaMicaClient\MicaClient\DrupalMicaClientClasses;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;

class DrupalMicaHttpClient implements MicaHttpClientInterface{

  function getMicaHttpClient($authentication = NULL, $formatter = NULL, $request_alter = FALSE, $delegate = NULL) {
    $http_client = MicaConfig\MicaDrupalConfig::GET_HTTP_CLIENT($authentication, $formatter, $request_alter, $delegate);
    return $http_client;
  }

  function getMicaHttpClientRequest($url, $values = array()) {
    $http_client_request = MicaConfig\MicaDrupalConfig::GET_HTTP_CLIENT_REQUEST($url, $values);
    return $http_client_request;
  }

  function getMicaHttpClientException() {
    // TODO: Implement getMicaHttpClientException() method.
  }

  function getMicaHttpClientStaticMethod($method) {
    // TODO: Implement getMicaHttpClientStaticMethod() method.
  }
}