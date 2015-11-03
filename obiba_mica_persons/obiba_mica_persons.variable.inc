<?php
/**
 * @file
 * Obiba Mica variable file
 */

/**
 * Implements hook_variable_info().
 */
function obiba_mica_persons_variable_info($options) {
  $variable['associated_people'] = array(
    'title' => t('Associated people'),
    'description' => t('The Associated people captions'),
    'type' => 'string',
    'default' => 'Associated people',
  );
  return $variable;
}
