<?php

use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient as DrupalMicaClient;
use \Obiba\ObibaMicaClient\MicaCache as MicaCache;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;



if(class_exists('Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient\MicaClient')) {
  class DrupalMicaClientResource extends DrupalMicaClient\MicaClient {
    protected $micaClient;

    function __construct($mica_url) {
      parent::__construct($mica_url,
        new MicaCache\MicaDrupalClientCache(),
        new MicaConfig\MicaDrupalConfig(),
        new MicaWatchDog\MicaDrupalClientWatchDog());
    }
  }
}
else{
  class DrupalMicaClientResource {
  }
}

class DrupalMicaConfigResource   {
  public $micaClientConfigResource;
  function __construct($mica_url = NULL) {
    $this->micaClientConfigResource = new DrupalMicaClient\MicaClientConfigResource($mica_url);
    return $this->micaClientConfigResource;
  }
}