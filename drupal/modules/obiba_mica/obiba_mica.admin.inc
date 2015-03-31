<?php

/**
 * @file
 * Obiba Mica client module settings UI.
 */

$path_module_commons = drupal_get_path('module', 'obiba_mica_commons');
include_once($path_module_commons . '/includes/obiba_mica_commons_taxonomy_resource.inc');

/**
 * Provides settings pages.
 */
function obiba_mica_admin_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('OBiBa study server (Mica)'),
    '#collapsible' => FALSE,
  );

  _obiba_mica_settings_server_form($form);

  $form['statistics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Statistics settings'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('mica_statistics');
  $form['statistics']['mica_statistics'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_statistics'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_statistics_coverage');
  $form['statistics']['mica_statistics_coverage'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_statistics_coverage'),
    '#description' => $info['description'],
  );

  $form['image_cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache images settings'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('image_cache_time_out');
  $form['image_cache']['image_cache_time_out'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('image_cache_time_out'),
    '#description' => $info['description'],
  );

  $form['image_cache']['clear_cache'] = array(
    '#type' => 'submit',
    '#value' => 'Clear images Cache',
    '#submit' => array('obiba_mica_clear_images_cache'),
    '#limit_validation_errors' => array(),
  );

  $form['search_display_settings'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Search page display settings'),
    '#collapsible' => FALSE,
  );

  _obiba_mica_settings_networks_form($form);
  _obiba_mica_settings_studies_form($form);
  _obiba_mica_settings_datasets_form($form);
  _obiba_mica_settings_variables_form($form);

  $form['content_display_settings'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Content page display settings'),
    '#collapsible' => FALSE,
  );

  _obiba_mica_settings_study_form($form);
  _obiba_mica_settings_dataset_form($form);
  _obiba_mica_settings_variable_form($form);

  $form['taxonomies'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taxonomies'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('mica_taxonomy_figures');
  $form['taxonomies']['mica_taxonomy_figures'] = array(
    '#type' => 'textarea',
    '#title' => $info['title'],
    '#required' => FALSE,
    '#default_value' => variable_get_value('mica_taxonomy_figures'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_taxonomy_order');
  $value = variable_get_value('mica_taxonomy_order');
  $form['taxonomies']['mica_taxonomy_order'] = array(
    '#type' => 'textarea',
    '#title' => $info['title'],
    '#required' => FALSE,
    '#default_value' => empty($value) ? _obiba_mica_admin_get_taxonomy_summaries() : $value,
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $form['#submit'] = array('obiba_mica_default_password');
  return system_settings_form($form);
}

function _obiba_mica_settings_server_form(&$form) {
  $info = variable_get_info('mica_url');
  $form['server']['mica_url'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#required' => TRUE,
    '#default_value' => variable_get_value('mica_url'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_anonymous_name');
  $form['server']['mica_anonymous_name'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#required' => TRUE,
    '#default_value' => variable_get_value('mica_anonymous_name'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_anonymous_password');
  $form['server']['mica_anonymous_password'] = array(
    '#type' => 'password',
    '#title' => $info['title'],
    //  '#default_value' => variable_get_value('mica_anonymous_password'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_copyright_notice');
  $form['server']['mica_copyright_notice'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_copyright_notice'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_response_page_size');
  $form['server']['mica_response_page_size'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_response_page_size'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('mica_response_page_size');
  $form['server']['mica_response_page_size'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_response_page_size'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('mica_response_page_size_small');
  $form['server']['mica_response_page_size_small'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_response_page_size_small'),
    '#description' => $info['description'],
  );
}

function _obiba_mica_settings_networks_form(&$form) {
  $form['search_display_settings']['networks_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Networks Search'),
    '#collapsible' => FALSE,
  );

  // tab
  $info = variable_get_info('search_networks');
  $form['search_display_settings']['networks_form']['search_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_networks'),
    '#description' => $info['description'],
  );

  // columns
  $form['search_display_settings']['networks_form']['networks_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Network column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('networks_column_studies');
  $form['search_display_settings']['networks_form']['networks_column']['networks_column_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_studies'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_column_study_datasets');
  $form['search_display_settings']['networks_form']['networks_column']['networks_column_study_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_study_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_column_harmonization_datasets');
  $form['search_display_settings']['networks_form']['networks_column']['networks_column_harmonization_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_harmonization_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_column_variables');
  $form['search_display_settings']['networks_form']['networks_column']['networks_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_variables'),
    '#description' => $info['description'],
  );

  // labels
  $info = variable_get_info('networks_search_label');
  $form['search_display_settings']['networks_form']['networks_search_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_search_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_empty_label');
  $form['search_display_settings']['networks_form']['networks_empty_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_empty_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
}

function _obiba_mica_settings_studies_form(&$form) {
  $form['search_display_settings']['studies_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Studies Search'),
    '#collapsible' => FALSE,
  );

  // tab
  $info = variable_get_info('search_studies');
  $form['search_display_settings']['studies_form']['search_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_studies'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('studies_facet_search');
  $form['search_display_settings']['studies_form']['studies_facet_search'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_facet_search'),
    '#description' => $info['description'],
  );

  // columns
  $form['search_display_settings']['studies_form']['studies_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('studies_column_design');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_design'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_design'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_questionnaire');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_questionnaire'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_questionnaire'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_pm');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_pm'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_pm'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_bio');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_bio'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_bio'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_other');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_other'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_other'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_participants');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_participants'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_participants'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_networks');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_networks'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_study_datasets');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_study_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_study_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_harmonization_datasets');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_harmonization_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_harmonization_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_variables');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_variables'),
    '#description' => $info['description'],
  );

  // content details
  $info = variable_get_info('studies_column_variables');
  $form['search_display_settings']['studies_form']['studies_column']['studies_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_variables'),
    '#description' => $info['description'],
  );

  // labels
  $info = variable_get_info('studies_search_label');
  $form['search_display_settings']['studies_form']['studies_search_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_search_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_empty_label');
  $form['search_display_settings']['studies_form']['studies_empty_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_empty_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('search_studies_dce_autocomplete');
  $form['search_display_settings']['studies_form']['search_studies_dce_autocomplete'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_studies_dce_autocomplete'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('search_general_population_sources_autocomplete');
  $form['search_display_settings']['studies_form']['search_general_population_sources_autocomplete'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_general_population_sources_autocomplete'),
    '#description' => $info['description'],
  );
}

function _obiba_mica_settings_study_form(&$form)
{
  $form['content_display_settings']['study_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study Content'),
    '#collapsible' => FALSE,
  );

  $form['content_display_settings']['study_form']['study_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study details page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('study_title_acronym_display');
  $form['content_display_settings']['study_form']['study_details']['study_title_acronym_display'] = array(
    '#type' => 'radios',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_title_acronym_display'),
    '#options' => array(0 => t('Study Title - Acronym'), 1 => t('Acronym - Study Title'), 2 => t('Study Title only')),
    '#description' => $info['description'],
  );

  $info = variable_get_info('study_show_networks');
  $form['content_display_settings']['study_form']['study_details']['study_show_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_show_networks'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('study_show_datasets');
  $form['content_display_settings']['study_form']['study_details']['study_show_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_show_datasets'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('study_show_coverage_graphs');
  $form['content_display_settings']['study_form']['study_details']['study_show_coverage_graphs'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_show_coverage_graphs'),
    '#description' => $info['description'],
  );

  $form['content_display_settings']['study_form']['studies_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Studies list page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('studies_list_show_search_form');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_search_form'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_search_form'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('studies_list_show_search_button');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_search_button'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_search_button'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('studies_list_show_study_sup_info');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_study_sup_info'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_study_sup_info'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('studies_list_show_trimmed_description_study');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_trimmed_description_study'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_trimmed_description_study'),
    '#description' => $info['description'],
  );

}

function _obiba_mica_settings_dataset_form(&$form)
{

  $form['content_display_settings']['dataset_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dataset Content'),
    '#collapsible' => FALSE,
  );

  $form['content_display_settings']['dataset_form']['dataset_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study details page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('dataset_title_acronym_setup');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_title_acronym_setup'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_title_acronym_setup'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_show_studies');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_show_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_show_studies'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_description_overview_field');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_description_overview_field'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_description_overview_field'),
    '#description' => $info['description'],
  );

}

function _obiba_mica_settings_variable_form(&$form)
{
  $form['content_display_settings']['variable_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Variable Content'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('variable_show_studies');
  $form['content_display_settings']['variable_form']['variable_show_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variable_show_studies'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('dataset_detailed_var_stats');
  $form['content_display_settings']['variable_form']['dataset_detailed_var_stats'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_detailed_var_stats'),
    '#description' => $info['description'],
  );

}

function _obiba_mica_settings_datasets_form(&$form) {
  $form['search_display_settings']['datasets_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Datasets Search'),
    '#collapsible' => FALSE,
  );

  // tab
  $info = variable_get_info('search_datasets');
  $form['search_display_settings']['datasets_form']['search_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_datasets'),
    '#description' => $info['description'],
  );

  // columns
  $form['search_display_settings']['datasets_form']['datasets_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dataset column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('datasets_column_type');
  $form['search_display_settings']['datasets_form']['datasets_column']['datasets_column_type'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_column_type'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('datasets_column_networks');
  $form['search_display_settings']['datasets_form']['datasets_column']['datasets_column_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_column_networks'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('datasets_column_studies');
  $form['search_display_settings']['datasets_form']['datasets_column']['datasets_column_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_column_studies'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('datasets_column_variables');
  $form['search_display_settings']['datasets_form']['datasets_column']['datasets_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_column_variables'),
    '#description' => $info['description'],
  );

  // labels
  $info = variable_get_info('datasets_search_label');
  $form['search_display_settings']['datasets_form']['datasets_search_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_search_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('datasets_empty_label');
  $form['search_display_settings']['datasets_form']['datasets_empty_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('datasets_empty_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('search_datasets_autocomplete');
  $form['search_display_settings']['datasets_form']['search_datasets_autocomplete'] = array(
    '#type' => 'select',
    '#options' => array(
      ObibaDatasetConstants::FACET_TYPE_HIDE => t('Hide'),
      ObibaDatasetConstants::FACET_TYPE_AUTOCOMPLETE => t('Autocomplete'),
      ObibaDatasetConstants::FACET_TYPE_CHECKBOX => t('Checkbox')
    ),
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_datasets_autocomplete'),
    '#description' => $info['description'],
  );
}

function _obiba_mica_settings_variables_form(&$form) {
  $form['search_display_settings']['variables_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Variables Search'),
    '#collapsible' => FALSE,
  );

  // tab
  $info = variable_get_info('search_variables');
  $form['search_display_settings']['variables_form']['search_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_variables'),
    '#description' => $info['description'],
  );

  // columns
  $form['search_display_settings']['variables_form']['variables_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Variables column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('variables_column_study');
  $form['search_display_settings']['variables_form']['variables_column']['variables_column_study'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variables_column_study'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('variables_column_dataset');
  $form['search_display_settings']['variables_form']['variables_column']['variables_column_dataset'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variables_column_dataset'),
    '#description' => $info['description'],
  );

  // labels
  $info = variable_get_info('variable_coverage_label');
  $form['search_display_settings']['variables_form']['variable_coverage_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variable_coverage_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('variables_search_label');
  $form['search_display_settings']['variables_form']['variables_search_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variables_search_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('variables_empty_label');
  $form['search_display_settings']['variables_form']['variables_empty_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variables_empty_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
}

function obiba_mica_default_password($form, &$form_state) {
  if (empty($form_state['values']['mica_anonymous_password'])) {
    $form_state['values']['mica_anonymous_password'] = variable_get_value('mica_anonymous_password');
  }
}

function obiba_mica_clear_images_cache() {
  cache_clear_all('images-cache-', 'cache', TRUE);
  drupal_set_message(t('The images cache cleared'));
}

/**
 * Retrieves taxonomies
 * TODO this should become a dragtable action callback so clients can always refresh the list when desired
 * @return string
 */
function _obiba_mica_admin_get_taxonomy_summaries() {
  $service = new MicaTaxonomyResource();
  $taxonomies = $service->get_taxonomy_summaries();
  $list = array();

  if (!empty($taxonomies) && !empty($taxonomies->summaries)) {
    foreach ($taxonomies->summaries as $summary) {
      $list[] = $summary->name;
    }
  }

  return implode(',', $list);
}