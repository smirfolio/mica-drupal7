<?php
/**
 * @file
 * Mica networks file
 */

function obiba_mica_graphic_studies_query($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-geoChart-cache-' . $id_networks);
  if (empty($json_response)) {
    $network_resource = new NetworkStatistics($id_networks);
    $json_response = $network_resource->GeoStudiesQuery();
    cache_set('data-studies-nb-geoChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }
}
