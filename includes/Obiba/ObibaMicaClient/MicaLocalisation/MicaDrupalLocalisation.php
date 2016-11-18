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


namespace Obiba\ObibaMicaClient\MicaLocalisation;

use Flow\JSONPath\JSONPath as JSONPath;
use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient\MicaClientConfigResource as MicaDrupalConfigResources;

class MicaDrupalLocalization implements MicaLocalizationInterface {

  public $langJson;
  private $jsonTranslation;
  private $jsonParser;

  function __construct() {
    $configResources = new MicaDrupalConfigResources();
    $this->jsonTranslation = $configResources->getTranslations();
    $this->jsonParser = new JSONPath(json_decode($this->jsonTranslation));
    return $this;
  }

  function getTranslation($vocabulary) {
    $sanitizedKey = $this->sanitizeStringKey($vocabulary);
    try {
      $local = $this->jsonParser->find($sanitizedKey);
      if(!empty($local[0])) {
        return $local[0];
      }
    } catch (\Exception $e) {
    }
    return $vocabulary;
  }


  private function sanitizeStringKey($vocabulary) {
    $sanitizedString = '$';
    $paths = explode('.', $vocabulary);
    foreach ($paths as $keyPath => $path) {
      if ($keyPath == 0) {
        $sanitizedString .= ".";
      }
      if (strstr($path, '-')) {
        $sanitizedString .= "\"$path\".";
      }
      else {
        $sanitizedString .= $path . '.';
      }
    }
    return rtrim($sanitizedString, ".");
  }

}