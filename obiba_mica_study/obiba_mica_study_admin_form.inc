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

/**
* Study content form setting.
*
* @param array $form
*   The admin setting form.
*/
function obiba_mica_study_settings_admin_content(&$form) {
_obiba_mica_study_settings_admin_study_content($form);
_obiba_mica_study_settings_admin_harmonization_study_content($form);
}

function _obiba_mica_study_settings_admin_study_content(&$form){
  $localize = obiba_mica_commons_mica_server_localisation();
  $form['content_display_settings']['study_form'] = array(
    '#weight' => -2,
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
      'name' => t('Name'),
      'acronym' => t('Acronym'),
      'numberOfParticipants-participant-number' =>  $localize->getTranslation('study_taxonomy.vocabulary.numberOfParticipants-participant-number.title')
    ),
    '#description' => $info['description'],
  );

  $info = variable_get_info('study_list_default_order_sort');
  $form['content_display_settings']['study_form']['studies_list']['study_list_default_order_sort'] = array(
    '#type' => 'radios',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('study_list_default_order_sort'),
    '#options' => array(
      '' => t('Asc'),
      'desc' => t('Desc'),
    ),
    '#description' => $info['description'],
  );
}

function _obiba_mica_study_settings_admin_harmonization_study_content(&$form){
  $form['content_display_settings']['harmo_study_form'] = array(
    '#weight' => -1,
    '#type' => 'fieldset',
    '#title' => t('Harmonization Study Content'),
    '#collapsible' => FALSE,
  );

  $form['content_display_settings']['harmo_study_form']['study_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Harmonization Study details page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('harmo_study_title_acronym_display');
  $form['content_display_settings']['harmo_study_form']['study_details']['harmo_study_title_acronym_display'] = array(
    '#type' => 'radios',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_study_title_acronym_display'),
    '#options' => array(
      0 => t('Study Title - Acronym'),
      1 => t('Acronym - Study Title'),
      2 => t('Study Title only'),
      3 => t('Acronym only'),
    ),
    '#description' => $info['description'],
  );

  $info = variable_get_info('harmo_study_show_networks');
  $form['content_display_settings']['harmo_study_form']['study_details']['harmo_study_show_networks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_study_show_networks'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('harmo_study_show_datasets');
  $form['content_display_settings']['harmo_study_form']['study_details']['harmo_study_show_datasets'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_study_show_datasets'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('harmo_study_show_coverage_graphs');
  $form['content_display_settings']['harmo_study_form']['study_details']['harmo_study_show_coverage_graphs'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_study_show_coverage_graphs'),
    '#description' => $info['description'],
  );

  $form['content_display_settings']['harmo_study_form']['studies_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('HArmonization Studies list page'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('harmo_studies_list_show_study_sup_info');
  $form['content_display_settings']['harmo_study_form']['studies_list']['harmo_studies_list_show_study_sup_info'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_studies_list_show_study_sup_info'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('harmo_studies_list_show_trimmed_description_study');
  $form['content_display_settings']['harmo_study_form']['studies_list']['harmo_studies_list_show_trimmed_description_study'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('harmo_studies_list_show_trimmed_description_study'),
    '#description' => $info['description'],
  );
}
