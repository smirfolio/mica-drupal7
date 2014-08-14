<?php


function mica_client_dataset_resource_return_facets($dto_type = NULL) {
  switch ($dto_type) {
    case 'mica_client_dataset':
      $path_module = drupal_get_path('module', 'mica_client_dataset');
      $facets = drupal_parse_info_file($path_module . '/mica_client_dataset.info')['facets'];
      return $facets;
    case 'mica_client_study' :
      $path_module = drupal_get_path('module', 'mica_client_study');
      $facets = drupal_parse_info_file($path_module . '/mica_client_study.info')['facets'];
      return $facets;
    default :
      $path_module = drupal_get_path('module', 'mica_client_dataset');
      $facets = drupal_parse_info_file($path_module . '/mica_client_dataset.info')['facets'];
      return $facets;
  }

}