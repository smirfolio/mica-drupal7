<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Obiba Mica client module settings UI.
 */

/**
 * Provides settings pages form.
 *
 * @return array
 *   The setting form on a array drupal markup.
 */
function obiba_mica_content_pages_admin_settings() {
  $form['content_display_settings'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Content page display settings'),
    '#collapsible' => FALSE,
  );
  obiba_mica_settings_network_content($form);
  obiba_mica_settings_study_content($form);
  if (module_exists('obiba_mica_data_access_request')) {
    obiba_mica_settings_data_access_content($form);
  }

  $form['translation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Translations'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('mica_disabled_path_translation');
  $form['translation']['mica_disabled_path_translation'] = array(
    '#type' => 'textarea',
    '#title' => $info['title'],
    '#required' => FALSE,
    '#default_value' => variable_get_value('mica_disabled_path_translation'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  return system_settings_form($form);
}

/**
 * Data access content form setting.
 *
 * @param array $form
 *   The admin setting form.
 */
function obiba_mica_settings_data_access_content(&$form) {
  $form['content_display_settings']['access_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data Access Content'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('access_home_page_title');
  $form['content_display_settings']['access_form']['access_home_page_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_home_page_title'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_requests_page_title');
  $form['content_display_settings']['access_form']['my_requests']['access_requests_page_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_requests_page_title'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('access_request_my_page_title');
  $form['content_display_settings']['access_form']['my_requests']['access_request_my_page_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_request_my_page_title'),
    "#maxlength" => 255,
    "#description" => $info['description']
  );

  $info = variable_get_info('access_request_page_title');
  $form['content_display_settings']['access_form']['my_requests']['access_request_page_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_request_page_title'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_documents_section_title');
  $form['content_display_settings']['access_form']['my_requests']['access_documents_section_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_documents_section_title'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  $info = variable_get_info('access_documents_section_help_text');
  $form['content_display_settings']['access_form']['my_requests']['access_documents_section_help_text'] = array(
    '#type' => 'textarea',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_documents_section_help_text'),
    '#description' => $info['description'],
  );
  $info = variable_get_info('user_list_page_title');
  $form['content_display_settings']['access_form']['user_list_page_title'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('user_list_page_title'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_my_requests_button');
  $form['content_display_settings']['access_form']['access_my_requests_button'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_my_requests_button'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_download_button');
  $form['content_display_settings']['access_form']['access_download_button'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_download_button'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_new_request_button');
  $form['content_display_settings']['access_form']['access_new_request_button'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_new_request_button'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_new_request_button_info');
  $form['content_display_settings']['access_form']['access_new_request_button_info'] = array(
    '#type' => 'textarea',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_new_request_button_info'),
    '#maxlength' => 255,
    '#description' => $info['description']
  );
  $info = variable_get_info('access_signup_button');
  $form['content_display_settings']['access_form']['access_signup_button'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_signup_button'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_signin_button');
  $form['content_display_settings']['access_form']['access_signin_button'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_signin_button'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $info = variable_get_info('access_comments_enabled');
  $form['content_display_settings']['access_form']['access_comments_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('access_comments_enabled'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
}

/**
 * Network content form setting.
 *
 * @param array $form
 *   The admin setting form.
 */
function obiba_mica_settings_network_content(&$form) {
  $form['content_display_settings']['network_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Network Content'),
    '#collapsible' => FALSE,
  );

  $form['content_display_settings']['network_form']['network_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Network details page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('networks_section_label');
  $form['content_display_settings']['network_form']['network_details']['networks_section_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('networks_section_label'),
    '#description' => $info['description'],
  );

}

/**
 * Study content form setting.
 *
 * @param array $form
 *   The admin setting form.
 */
function obiba_mica_settings_study_content(&$form) {
  $form['content_display_settings']['study_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Study Content'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('study_target_number_participant_label');
  $form['content_display_settings']['study_form']['study_target_number_participant_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => $info['default'],
    '#description' => $info['description']
  );

  $info = variable_get_info('study_target_number_participant_with_sample_label');
  $form['content_display_settings']['study_form']['study_target_number_participant_with_sample_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => $info['default'],
    '#description' => $info['description']
  );

  $info = variable_get_info('study_supplementary_information_about_target_number_participant');
  $form['content_display_settings']['study_form']['study_supplementary_information_about_target_number_participant'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => $info['default'],
    '#description' => $info['description']
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
    '#options' => array(
      0 => t('Study Title - Acronym'),
      1 => t('Acronym - Study Title'),
      2 => t('Study Title only'),
      3 => t('Acronym only'),
    ),
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

  $info = variable_get_info('studies_list_show_studies_count_caption');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_studies_count_caption'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_studies_count_caption'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('studies_list_show_search_form');
  $form['content_display_settings']['study_form']['studies_list']['studies_list_show_search_form'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('studies_list_show_search_form'),
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


  $info = variable_get_info('study_list_name_acronym_sort');
  $form['content_display_settings']['study_form']['studies_list']['study_list_name_acronym_sort'] = array(
    '#type' => 'radios',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_list_name_acronym_sort'),
    '#options' => array(
      0 => t('None'),
      1 => t('Name'),
      2 => t('Acronym'),
    ),
    '#description' => $info['description'],
  );

}
