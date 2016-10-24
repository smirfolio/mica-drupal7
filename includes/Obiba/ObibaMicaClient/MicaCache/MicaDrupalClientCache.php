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

namespace Obiba\ObibaMicaClient\MicaCache;

use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;

class MicaDrupalClientCache implements MicaCacheInterface {
  function __construct() {
  }

  /**
   * query the cache.
   *
   * @param string $resource_query
   *   Study, dce, network ...
   *
   * @return $this
   */
  public function MicaGetCache($resource_query) {
    $cached_result = $this->clientGetCache($resource_query);
    if (!empty($cached_result)) {
      return $cached_result;
    }
    return FALSE;
  }

  public function MicaSetCache($resource_query, $value) {
    $this->clientSetCache($resource_query, $value);
  }

  public function clientGetCache($key) {
    $client_get_cache = MicaConfig\MicaDrupalConfig::CLIENT_GET_CACHE;
    return $client_get_cache($key);
  }

  public function clientSetCache($key, $value) {
    $client_set_cache = MicaConfig\MicaDrupalConfig::CLIENT_SET_CACHE;
    $client_set_cache($key, $value);
  }

  public function IsNotEmptyStoredData($resources, $stored_data) {
    $entity_resource = explode('/', $resources);
    switch ($entity_resource[1]) {
      case 'taxonomy':
        if (!empty($stored_data)) {
          return TRUE;
        }
        break;
      case 'taxonomies' :
        if (!empty($stored_data)) {
          return TRUE;
        }
        break;
      case 'variables' :
        $coverage_resource = explode('?', $entity_resource[2]);
        if ($coverage_resource[0] !== '_coverage') {
          if (!empty($stored_data->variableResultDto->totalHits)) {
            return TRUE;
          }
        }
        else {
          if (!empty($stored_data->taxonomyHeaders) ||
            !empty($stored_data->vocabularyHeaders) ||
            !empty($stored_data->termHeaders) ||
            !empty($stored_data->rows)
          ) {
            return TRUE;
          }
        }
        break;
      case 'datasets' :
        if (!empty($stored_data->datasetResultDto->totalHits)) {
          return TRUE;
        }
        break;
      case 'studies' :
        if (!empty($stored_data->studyResultDto->totalHits)) {
          return TRUE;
        }
        break;
      case 'networks' :
        if (!empty($stored_data->networkResultDto->totalHits)) {
          return TRUE;
        }
        break;
      case 'network' :
        $stored_data;
        if (!empty($stored_data->networkSummaries)) {
          return TRUE;
        }
        break;
      default :
        return FALSE;
    }
  }

}
