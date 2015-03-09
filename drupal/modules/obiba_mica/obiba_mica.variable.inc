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
    'title' => t('The image cache timeout'),
    'description' => t('The timeout in minute to expire Studies and networks image cache'),
    'type' => 'boolean',
    'default' => 1440,
  );

  _obiba_mica_variable_info_networks($variable);
  _obiba_mica_variable_info_studies($variable);
  _obiba_mica_variable_info_datasets($variable);
  _obiba_mica_variable_info_variables($variable);

  $variable['mica_taxonomy_figures'] = array(
    'title' => t('Taxonomy in figures'),
    'description' => t('List of taxonomy names (ordered, case sensitive, comma separated) that will be displayed in Variable Classification figures. If none is specified, all taxonomies (alphabetically ordered) will be displayed.'),
    'type' => 'string',
    'default' => '',
  );

  $variable['mica_taxonomy_order'] = array(
    'title' => t('Taxonomy Order'),
    'description' => t('List of taxonomy names (case sensitive, comma separated, without blank spaces) determining their order of appearance in the search and classification UI.'),
    'type' => 'string',
    'default' => '',
  );

  return $variable;
}

function _obiba_mica_variable_info_networks(&$variable) {
  $variable['search_networks'] = array(
    'title' => t('Show networks search'),
    'description' => t('If selected, the networks tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_studies'] = array(
    'title' => t('Show studies'),
    'description' => t('Show studies column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_study_datasets'] = array(
    'title' => t('Show studies dataset'),
    'description' => t('Show studies dataset column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_harmonization_datasets'] = array(
    'title' => t('Show harmonization dataset'),
    'description' => t('Show harmonization dataset column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_column_variables'] = array(
    'title' => t('Show variables'),
    'description' => t('Show variables column in the networks table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['networks_search_label'] = array(
    'title' => t('Networks search label'),
    'description' => t('Text to be displayed in links to network search.'),
    'type' => 'string',
    'default' => 'Search Networks',
  );
  $variable['networks_empty_label'] = array(
    'title' => t('No network label'),
    'description' => t('Text to be displayed when no network is found.'),
    'type' => 'string',
    'default' => 'No network found',
  );
}

function _obiba_mica_variable_info_studies(&$variable) {
  $variable['search_studies'] = array(
    'title' => t('Show studies search'),
    'description' => t('If selected, the studies tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_design'] = array(
    'title' => t('Show design'),
    'description' => t('Show design column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_questionnaire'] = array(
    'title' => t('Show questionnaires'),
    'description' => t('Show questionnaires column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_pm'] = array(
    'title' => t('Show physical measures'),
    'description' => t('Show physical measures column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_bio'] = array(
    'title' => t('Show biological samples'),
    'description' => t('Show biological samples column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_other'] = array(
    'title' => t('Show other data sources'),
    'description' => t('Show other data sources column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_participants'] = array(
    'title' => t('Show participants'),
    'description' => t('Show participants column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_networks'] = array(
    'title' => t('Show networks'),
    'description' => t('Show networks column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_study_datasets'] = array(
    'title' => t('Show study datasets'),
    'description' => t('Show study datasets column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_harmonization_datasets'] = array(
    'title' => t('Show harmonization datasets'),
    'description' => t('Show harmonization dataset column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_column_variables'] = array(
    'title' => t('Show variables'),
    'description' => t('Show variables column in the studies table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_search_label'] = array(
    'title' => t('Studies search label'),
    'description' => t('Text to be displayed in links to study search.'),
    'type' => 'string',
    'default' => 'Search Studies',
  );
  $variable['studies_empty_label'] = array(
    'title' => t('No study label'),
    'description' => t('Text to be displayed when no study is found.'),
    'type' => 'string',
    'default' => 'No study found',
  );
  $variable['search_studies_dce_autocomplete'] = array(
    'title' => t('Show Data Collection Event auto-complete search filter'),
    'description' => t('If selected, the auto-complete search filter will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
}

function _obiba_mica_variable_info_datasets(&$variable) {
  $variable['search_datasets'] = array(
    'title' => t('Show datasets search'),
    'description' => t('If selected, the datasets tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['datasets_column_type'] = array(
    'title' => t('Show type dataset'),
    'description' => t('Show type dataset column in the datasets table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['datasets_column_networks'] = array(
    'title' => t('Show networks'),
    'description' => t('Show networks column in the datasets table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['datasets_column_studies'] = array(
    'title' => t('Show studies'),
    'description' => t('Show studies column in the datasets table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['datasets_column_variables'] = array(
    'title' => t('Show variables'),
    'description' => t('Show variables column in the datasets table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['datasets_search_label'] = array(
    'title' => t('Datasets search label'),
    'description' => t('Text to be displayed in links to dataset search.'),
    'type' => 'string',
    'default' => 'Search Datasets',
  );
  $variable['datasets_empty_label'] = array(
    'title' => t('No dataset label'),
    'description' => t('Text to be displayed when no dataset is found.'),
    'type' => 'string',
    'default' => 'No dataset found',
  );
  $variable['search_datasets_autocomplete'] = array(
    'title' => t('Show dataset auto-complete search filter'),
    'description' => t('If selected, the auto-complete search filter will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
}

function _obiba_mica_variable_info_variables(&$variable) {
  $variable['search_variables'] = array(
    'title' => t('Show variables search'),
    'description' => t('If selected, the variables tab will be displayed in the search page.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['variables_column_study'] = array(
    'title' => t('Show study'),
    'description' => t('Show study column in the variables table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['variables_column_dataset'] = array(
    'title' => t('Show dataset'),
    'description' => t('Show dataset column in the variables table.'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['variable_coverage_label'] = array(
    'title' => t('Variable classification label'),
    'description' => t('Text to be displayed in links to variable classification.'),
    'type' => 'string',
    'default' => 'Variable Classification',
  );
  $variable['variables_search_label'] = array(
    'title' => t('Variables search label'),
    'description' => t('Text to be displayed in links to variable search.'),
    'type' => 'string',
    'default' => 'Search Variables',
  );
  $variable['variables_empty_label'] = array(
    'title' => t('No variable label'),
    'description' => t('Text to be displayed when no variable is found.'),
    'type' => 'string',
    'default' => 'No variable found',
  );
}