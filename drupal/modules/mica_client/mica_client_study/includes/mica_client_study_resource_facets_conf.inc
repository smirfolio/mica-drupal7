<?php


function mica_client_study_resource_return_facets() {
  $path_module = drupal_get_path('module', 'mica_client_study');
  $facets = drupal_parse_info_file($path_module . '/mica_client_study.info')['facets'];
  return $facets;
}