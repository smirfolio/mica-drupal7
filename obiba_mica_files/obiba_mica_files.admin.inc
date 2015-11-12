<?php
/**
 * @file
 * Obiba Mica files module admin settings
 */

/**
 * Provides settings pages.
 */
function obiba_mica_files_admin_settings() {

  $form['files'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Files module display settings'),
    '#collapsible' => FALSE,
  );

  $form['files']['files_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Files module display'),
    '#collapsible' => FALSE,
  );

  $form['files']['files_display']['labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Files module labels'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('files_documents_label');
  $form['files']['files_display']['labels']['files_documents_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('files_documents_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  return system_settings_form($form);

}
