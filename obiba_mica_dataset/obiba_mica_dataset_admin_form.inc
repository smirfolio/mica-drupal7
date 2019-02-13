<?php

/**
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

function obiba_mica_dataset_admin_settings(&$form){
  _obiba_mica_dataset_settings_dataset_content($form);
  _obiba_mica_dataset_settings_variable_content($form);
}

/**
 * Variable content form setting.
 *
 * @param array $form
 *   The admin setting form.
 */
function _obiba_mica_dataset_settings_dataset_content(&$form) {
  $bootstrap_theme_path = base_path() . drupal_get_path('theme', 'obiba_bootstrap');
  $form['content_display_settings']['dataset_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dataset Content'),
    '#collapsible' => FALSE,
  );
  $form['content_display_settings']['dataset_form']['dataset_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dataset details page'),
    '#collapsible' => FALSE,
  );
  $info = variable_get_info('dataset_detailed_crosstab');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_detailed_crosstab'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_detailed_crosstab'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('dataset_title_acronym_setup');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_title_acronym_setup'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_title_acronym_setup'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_show_harmonization_studies');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_show_harmonization_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_show_harmonization_studies'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_show_collected_studies');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_show_collected_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_show_collected_studies'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_description_overview_field');
  $form['content_display_settings']['dataset_form']['dataset_details']['dataset_description_overview_field'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_description_overview_field'),
    '#description' => $info['description'],
  );

  $form['content_display_settings']['dataset_form']['harmonization_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Harmonization status display'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('dataset_harmonization_impossible_icon');
  $form['content_display_settings']['dataset_form']['harmonization_status']['dataset_harmonization_impossible_icon'] = array(
    '#type' => 'radios',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_harmonization_impossible_icon'),
    '#options' => array(
      ObibaDatasetConstants::IMPOSSIBLE_HARMO_ICON => '<img src="' . $bootstrap_theme_path . '/glyphicon-remove.png" > Remove',
      ObibaDatasetConstants::INCOMPLETE_HARMO_ICON => '<img src="' . $bootstrap_theme_path . '/glyphicon-minus.png" > Minus',
    ),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_harmonization_impossible_label');
  $form['content_display_settings']['dataset_form']['harmonization_status']['dataset_harmonization_impossible_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#maxlength' => 255,
    '#default_value' => variable_get_value('dataset_harmonization_impossible_label'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_harmonization_complete_description');
  $form['content_display_settings']['dataset_form']['harmonization_status']['dataset_harmonization_complete_description'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#maxlength' => 255,
    '#default_value' => variable_get_value('dataset_harmonization_complete_description'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_harmonization_impossible_description');
  $form['content_display_settings']['dataset_form']['harmonization_status']['dataset_harmonization_impossible_description'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#maxlength' => 255,
    '#default_value' => variable_get_value('dataset_harmonization_impossible_description'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_harmonization_undetermined_description');
  $form['content_display_settings']['dataset_form']['harmonization_status']['dataset_harmonization_undetermined_description'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#maxlength' => 255,
    '#default_value' => variable_get_value('dataset_harmonization_undetermined_description'),
    '#description' => $info['description'],
  );
}

/**
 * Variable content form setting.
 *
 * @param array $form
 *   The admin setting form.
 */
function _obiba_mica_dataset_settings_variable_content(&$form) {
  $form['content_display_settings']['variable_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Variable Content'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('mica_all_variables_dataschema');
  $form['content_display_settings']['variable_form']['mica_all_variables_dataschema'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_all_variables_dataschema'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('mica_statistics');
  $form['content_display_settings']['variable_form']['mica_statistics'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('mica_statistics'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('variable_show_studies');
  $form['content_display_settings']['variable_form']['variable_show_studies'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variable_show_studies'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('variable_show_networks');
  $form['content_display_settings']['variable_form']['variable_show_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variable_show_networks'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('dataset_detailed_var_stats');
  $form['content_display_settings']['variable_form']['dataset_detailed_var_stats'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('dataset_detailed_var_stats'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('variable_algorithm');
  $form['content_display_settings']['variable_form']['variable_algorithm'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('variable_algorithm'),
    '#description' => $info['description'],
  );
}

