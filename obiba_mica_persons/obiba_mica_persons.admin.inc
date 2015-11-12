<?php
/**
 * @file
 * Obiba Mica Persons module variable file
 */

/**
 * Provides settings pages.
 */
function obiba_mica_persons_admin_settings() {
  $form['persons'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Persons display settings'),
    '#collapsible' => FALSE,
  );

  $form['persons']['persons_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Persons display'),
    '#collapsible' => FALSE,
  );

  $form['persons']['persons_display']['labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Persons labels'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('associated_people');
  $form['persons']['persons_display']['labels']['associated_people'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('associated_people'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  return system_settings_form($form);
}
