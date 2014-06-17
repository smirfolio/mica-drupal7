<?php

/**
 * @file
 * Obiba Mica client module settings UI.
 */

/**
 * Provides settings pages.
 */
function mica_client_admin_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('OBiBa study server (Mica)'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['mica_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Mica address'),
    '#required' => TRUE,
    '#default_value' => variable_get('mica_url', 'https://localhost:8445'),
    '#maxlength' => 255,
    '#description' => t('URL of the Mica server. Example: https://mica.example.org:8445'),
  );

  return system_settings_form($form);
}
