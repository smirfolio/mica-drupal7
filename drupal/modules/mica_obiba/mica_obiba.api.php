<?php
/**
 * @file
 * Hooks provided by Mica client
 */

/**
 * Implementation of  hook_mica_override_templates_alter().
 * Alter default templates to display mica pages
 * @$themes_to_override an array of key/value key = name of the template to override and
 *                      the value = the file name of this template on the given module folder
 * all overridden templates must be in 'templates/' folder
 */
function hook_mica_override_templates_alter(&$themes_to_override) {
  $themes_to_override = array(
    'mica_obiba_study_detail' => 'mica_obiba_study-detail'
  );

}