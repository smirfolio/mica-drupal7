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

namespace Obiba\ObibaMicaClient\MicaConfigurations;

class MicaDrupalConfig implements MicaConfigInterface {
const CLIENT_GET_CACHE = "obiba_mica_commons_get_cache";
const CLIENT_SET_CACHE = "obiba_mica_commons_set_cache";

  function __construct() {
  }

  public function MicaGetConfig($key) {
    return variable_get_value($key);
  }

  public function MicaSetConfig($key, $value) {
    // TODO: Implement MicaSetConfig() method.
  }
}