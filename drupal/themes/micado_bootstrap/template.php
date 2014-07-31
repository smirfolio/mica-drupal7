<?php

/**
 * @file
 * template.php
 */

/*
 * Hook to override default theme pages
 *  copy '<modules>/mica_client_study/templates/'   files in current theme 'templates/' path
 * you can modify default display of listed page by rearrange block field
 *don't forget to clear the theme registry.
 *
 */
function micado_bootstrap_theme($existing, $type, $theme, $path) {
  $theme_array = array();

  $destination_path = file_exists($path . '/templates/mica_client_study-list.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_study_list'] = array(
      'template' => 'mica_client_study-list',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_study_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_study_search'] = array(
      'template' => 'mica_client_study_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_study_detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_study_detail'] = array(
      'template' => 'mica_client_study_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_population_detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_population_detail'] = array(
      'template' => 'mica_population_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_dce_detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_dce_detail'] = array(
      'template' => 'mica_dce_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_study_attachments.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_study_attachments'] = array(
      'template' => 'mica_client_study_attachments',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_study_block_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_study_block_search'] = array(
      'template' => 'mica_client_study_block_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_datasets-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_datasets-detail'] = array(
      'template' => 'mica_client_datasets-detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_client_datasets-tables.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_client_datasets-tables'] = array(
      'template' => 'mica_client_datasets-tables',
      'path' => $path . '/templates'
    );
  }

  return $theme_array;

}
