<?php


function mica_client_dataset_resource_return_facets() {
  $path_module = drupal_get_path('module', 'mica_client_dataset');
  $facets = drupal_parse_info_file($path_module . '/mica_client_dataset.info')['facets'];
  return $facets;
}