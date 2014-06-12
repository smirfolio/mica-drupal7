<?php

/**
 * @file
 * Obiba Auth module settings UI.
 */

/**
 * Provides settings pages.
 */
function obiba_auth_admin_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('OBiBa authentication server (Agate)'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['agate_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Agate address'),
    '#default_value' => variable_get('agate_url', ''),
    '#maxlength' => 255,
    '#description' => t('URL of the Agate server. Note that cross-domain is not supported. Example: https://agate.example.org:8444'),
  );

  $form['server']['agate_application_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Application name'),
    '#default_value' => variable_get('agate_application_name', 'drupal'),
    '#maxlength' => 255,
    '#description' => t('The name under which the Drupal server is known by Agate.'),
  );

  $form['server']['agate_application_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Application key'),
    '#default_value' => variable_get('agate_application_key', 'changeit'),
    '#maxlength' => 255,
    '#description' => t('The key used by the Drupal server when issuing requests to Agate.'),
  );

  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('User accounts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['account']['obiba_user_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create Drupal accounts'),
    '#default_value' => variable_get('obiba_user_register', 1),
    '#description' => t('Whether a Drupal account is automatically created the first time a OBiBa user logs into the site. If disabled, you will need to pre-register Drupal accounts for authorized users.'),
  );

  // Taken from Drupal's User module.
  $roles = array_map('check_plain', user_roles(TRUE));
  $checkbox_authenticated = array(
    '#type' => 'checkbox',
    '#title' => $roles[DRUPAL_AUTHENTICATED_RID],
    '#default_value' => TRUE,
    '#disabled' => TRUE,
  );
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  $form['account']['obiba_auto_assigned_role'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#description' => t('The selected roles will be automatically assigned to each OBiBa user on login. Use this to automatically give OBiBa users additional privileges or to identify OBiBa users to other modules.'),
    '#default_value' => variable_get('obiba_auto_assigned_role', array()),
    '#options' => $roles,
    '#access' => user_access('administer permissions'),
    DRUPAL_AUTHENTICATED_RID => $checkbox_authenticated,
  );

  if (module_exists('persistent_login')) {
    $form['account']['obiba_allow_rememberme'] = array(
      '#type' => 'checkbox',
      '#title' => t('Users can stay logged in between sessions'),
      '#default_value' => variable_get('obiba_allow_rememberme', 0),
      '#description' => t('If Persistent Login is enabled, users can choose to stay logged in between browser sessions'),
    );
  }


  return system_settings_form($form);
}
