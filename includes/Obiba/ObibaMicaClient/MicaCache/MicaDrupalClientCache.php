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

class MicaDrupalClientCache implements MicaCacheInterface {
  public $MicaClient;

  function __construct($object) {
    $this->MicaClient = $object;
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
    $cached_result = obiba_mica_commons_get_cache($resource_query);
    if (!empty($cached_result)) {
      $this->MicaClient->result_resource_query = $cached_result;
    }
    return $this;
  }

  public function MicaSetCache($resource_query, $value) {
    obiba_mica_commons_set_cache($resource_query, $value);
  }

  public function IsEmptyStoredData($resources, $stored_data) {
    $entity_resource = explode('/', $resources);
    switch ($entity_resource[1]) {
      case 'taxonomy':
        if (!isset($stored_data)) {
          return TRUE;
        }
        break;
      case 'taxonomies' :
        if (!isset($stored_data)) {
          return TRUE;
        }
        break;

      case 'variables' :
        $coverage_resource = explode('?', $entity_resource[2]);
        if ($coverage_resource[0] !== '_coverage') {
          if (!isset($stored_data->variableResultDto->totalHits)) {
            return TRUE;
          }
        }
        else{
          return TRUE;
        }
        break;
      case 'datasets' :
        if (!isset($stored_data->datasetResultDto->totalHits)) {
          return TRUE;
        }
        break;
      case 'studies' :
        if (!isset($stored_data->studyResultDto->totalHits)) {
          return TRUE;
        }
        break;
      case 'networks' :
        if (!isset($stored_data->networkResultDto->totalHits)) {
          return TRUE;
        }
        break;
      default :
        if (!isset($stored_data)) {
          return FALSE;
        }

    }
    return FALSE;
  }
}
