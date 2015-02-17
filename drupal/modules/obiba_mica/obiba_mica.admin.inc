<?php

/**
 * @file
 * Obiba Mica client module settings UI.
 */

/**
 * Provides settings pages.
 */
function obiba_mica_admin_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('OBiBa study server (Mica)'),
    '#collapsible' => FALSE,
  );

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
    '#type' => 'fieldset',
    '#title' => t('Search page display settings'),
    '#collapsible' => FALSE,
  );
  /********Networks Tabs ***********************/
  $info = variable_get_info('search_networks');
  $form['search_display_settings']['search_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_networks'),
    '#description' => $info['description'],
  );
  /*############***********Network columns**********############**********/
  $form['search_display_settings']['networks_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Network column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('networks_column_studies');
  $form['search_display_settings']['networks_column']['networks_column_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_studies'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_column_study_datasets');
  $form['search_display_settings']['networks_column']['networks_column_study_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_study_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('networks_column_harmonization_datasets');
  $form['search_display_settings']['networks_column']['networks_column_harmonization_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_harmonization_datasets'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('networks_column_variables');
  $form['search_display_settings']['networks_column']['networks_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_column_variables'),
    '#description' => $info['description'],
  );
  /***********End networks******************************/

  /*******************Studies Tabs**************************/
  $info = variable_get_info('search_studies');
  $form['search_display_settings']['search_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_studies'),
    '#description' => $info['description'],
  );
  /*############***********studies columns**********############**********/
  $form['search_display_settings']['studies_column'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study column display settings'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('studies_column_design');
  $form['search_display_settings']['studies_column']['studies_column_design'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_design'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_questionnaire');
  $form['search_display_settings']['studies_column']['studies_column_questionnaire'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_questionnaire'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_pm');
  $form['search_display_settings']['studies_column']['studies_column_pm'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_pm'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_bio');
  $form['search_display_settings']['studies_column']['studies_column_bio'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_bio'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_other');
  $form['search_display_settings']['studies_column']['studies_column_other'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_other'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_participants');
  $form['search_display_settings']['studies_column']['studies_column_participants'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_participants'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_networks');
  $form['search_display_settings']['studies_column']['studies_column_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_networks'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_study_datasets');
  $form['search_display_settings']['studies_column']['studies_column_study_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_study_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_harmonization_datasets');
  $form['search_display_settings']['studies_column']['studies_column_harmonization_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_harmonization_datasets'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('studies_column_variables');
  $form['search_display_settings']['studies_column']['studies_column_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_column_variables'),
    '#description' => $info['description'],
  );

  /*******************datasets Tabs**************************/
  $info = variable_get_info('search_datasets');
  $form['search_display_settings']['search_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_datasets'),
    '#description' => $info['description'],
  );
  /*******************variables Tabs**************************/
  $info = variable_get_info('search_variables');
  $form['search_display_settings']['search_variables'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('search_variables'),
    '#description' => $info['description'],
  );

  $form['#submit'] = array('my_default_password');
  return system_settings_form($form);
}

function my_default_password($form, &$form_state) {
  if (empty($form_state['values']['mica_anonymous_password'])) {
    $form_state['values']['mica_anonymous_password'] = variable_get_value('mica_anonymous_password');
  }
}

function obiba_mica_clear_images_cache() {
  cache_clear_all('images-cache-', 'cache', TRUE);
  drupal_set_message(t('The images cache cleared'));
}