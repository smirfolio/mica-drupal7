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

  $destination_path = file_exists($path . '/templates/block--mica_client_dataset.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['block__mica_client_dataset'] = array(
      'variables' => array('block' => array()),
      'template' => 'block--mica_client_dataset',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/block--mica_client_facet_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['block__mica_client_facet_search.tpl.php'] = array(
      'variables' => array('block' => array()),
      'template' => 'block--mica_client_facet_search',
      'path' => $path . '/templates'
    );
  }

  return $theme_array;

}

/**
 * Implements hook_bootstrap_based_theme().
 */
function micado_bootstrap_bootstrap_based_theme() {
  return array('micado_bootstrap' => TRUE);
}

/**
 * Implements hook_preprocess_html().
 */
function micado_bootstrap_preprocess_html(&$variables) {
  drupal_add_css('https://fonts.googleapis.com/css?family=Open+Sans:400italic,400,300,700,700italic', array('type' => 'external'));
}

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function micado_bootstrap_preprocess_page(&$variables) {
  drupal_add_js('misc/jquery.cookie.js', 'file');
  // Add information about the number of sidebars.
  if (!empty($variables['page']['facets']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['facets']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-9"';
  }
  // Add information about the number of sidebars.
  elseif (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-9"';
  }

  else {
    $variables['content_column_class'] = ' class="col-sm-12"';
  }
}

