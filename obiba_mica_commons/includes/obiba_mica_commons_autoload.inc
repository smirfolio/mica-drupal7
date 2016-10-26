<?php



$path_module_study = drupal_get_path('module', 'obiba_mica');
include_once($path_module_study . '/includes/Obiba/ObibaMicaClient/MicaClient/DrupalMicaCientClasses/DrupalMicaClient.php');
include_once($path_module_study . '/includes/Obiba/ObibaMicaClient/MicaClient/DrupalMicaCientClasses/DrupalMicaClient.php');
use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClientClasses as DrupalMicaClientClasses;

class DrupalMicaClient extends DrupalMicaClientClasses\MicaClient{
  function __construct($mica_url, $micaCache) {
  return parent::__construct($mica_url, $micaCache);
  }
}