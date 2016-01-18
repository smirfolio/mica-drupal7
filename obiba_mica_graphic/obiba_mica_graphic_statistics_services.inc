<?php
/**
 * @file
 * Obiba Mica Graphics file
 */

function obiba_mica_graphic_statistics_query($type_entities = 'studies', $id_entities) {
  if (!empty(file_get_contents('php://input')) && !empty($id_entities)) {
    $cached_json_response = cache_get('data-studies-statistics-cache-' . $type_entities .'-' . $id_entities);
    if (!empty($cached_json_response)) {
      $json_response = $cached_json_response->data;
    }
    else {
      $network_resource = new NetworkStatistics($id_entities);
      $json_response = $network_resource->statisticsQuery($type_entities, file_get_contents('php://input'));
      cache_set('data-studies-statistics-cache-' . $type_entities .'-' . $id_entities, $json_response, 'cache', time() + (60 * 60));
    }
    drupal_json_output(json_decode($json_response));
  }
}
