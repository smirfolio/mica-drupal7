<?php
/**
 * @file
 * Obiba Mica variable file
 */

/**
 * Implements hook_variable_info().
 */
function obiba_mica_variable_info($options) {
  $variable['mica_url'] = array(
    'title' => t('Mica address'),
    'description' => t('URL of the Mica server. Example: https://mica.example.org:8445'),
    'type' => 'string',
    'default' => 'https://localhost:8445',
  );
  $variable['mica_anonymous_name'] = array(
    'title' => t('Anonymous user name'),
    'description' => t('The name under which an anonymous user is known by Mica.'),
    'type' => 'string',
    'default' => 'anonymous',
  );
  $variable['mica_anonymous_password'] = array(
    'title' => t('Anonymous user password'),
    'description' => t('The password used by the Drupal server when issuing requests to Mica.'),
    'type' => 'string',
    'default' => 'password',
  );
  $variable['mica_statistics'] = array(
    'title' => t('Show statistics'),
    'description' => t('If show statistics is selected, variable pages will include a statistics summary section, contingency tables and queries for entity counts features will be available.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['image_cache_time_out'] = array(
    'title' => t('The image cache timout'),
    'description' => t('The timeout in minute to expire Studies and networks image cache'),
    'type' => 'boolean',
    'default' => 1440,
  );

  $variable['search_networks'] = array(
    'title' => t('Show networks search'),
    'description' => t('If Show networks search is selected, the networks tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_studies'] = array(
    'title' => t('Show studies column'),
    'description' => t('Show studies column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_study_datasets'] = array(
    'title' => t('Show studies dataset column'),
    'description' => t('Show studies dataset column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_harmonization_datasets'] = array(
    'title' => t('Show harmonization dataset column'),
    'description' => t('Show harmonization dataset column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_variables'] = array(
    'title' => t('Show variables column'),
    'description' => t('Show variables column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['search_studies'] = array(
    'title' => t('Show studies search'),
    'description' => t('If Show Show studies search is selected, the studies tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['search_datasets'] = array(
    'title' => t('Show datasets search'),
    'description' => t('If Show Show datasets search is selected, the studies tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['search_variables'] = array(
    'title' => t('Show variables search'),
    'description' => t('If Show Show variables search is selected, the studies tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  return $variable;
}
