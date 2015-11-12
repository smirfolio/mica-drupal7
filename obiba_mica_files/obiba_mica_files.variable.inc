<?php
/**
 * @file
 * Obiba Mica variable file
 */

/**
 * Implements hook_variable_info().
 */
function obiba_mica_files_variable_info($options) {
  $variable['files_documents_label'] = array(
    'title' => t('Documents'),
    'description' => t('The attached documents section title'),
    'type' => 'string',
    'default' => 'Documents',
  );
  return $variable;
}
