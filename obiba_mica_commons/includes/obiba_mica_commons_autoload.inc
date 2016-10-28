<?php






//$path_module_study = drupal_get_path('module', 'obiba_mica');
//include($path_module_study . '/includes/Obiba/ObibaMicaClient/MicaClient/DrupalMicaClientClasses/DrupalMicaClient.php');
//include($path_module_study . '/includes/Obiba/ObibaMicaClient/MicaClient/DrupalMicaClientClasses/DrupalMicaClientConfigResource.php');

use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClientClasses as MicaClientClasses;
use \Obiba\ObibaMicaClient\MicaCache as MicaCache;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;



if(class_exists('Obiba\ObibaMicaClient\MicaClient\DrupalMicaClientClasses\MicaClient')) {
  class DrupalMicaClient extends MicaClientClasses\MicaClient {
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
  class DrupalMicaClient {
  }
}

class DrupalMicaConfigResource   {
  public $micaClientConfigResource;
  function __construct($mica_url = NULL) {
    $this->micaClientConfigResource = new MicaClientClasses\MicaClientConfigResource($mica_url);
    return $this->micaClientConfigResource;
  }
}