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


namespace Obiba\ObibaMicaClient\MicaHttpClient;


class  DrupalMicaHttpClient extends AbstractMicaHttpClient {

  function __construct($micaUrl = NULL) {
    parent::__construct($micaUrl);
    return $this;
  }

  public function drupalMicaClientAddHttpHeader($header){
   return  $this->drupalMicaHttpClient->micaClientAddHttpHeader($header);
  }

  public function drupalMicaClientGetLastResponse(){
    return $this->httpGetLastResponse();
  }
}