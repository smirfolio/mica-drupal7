<?php


/**
 * Implements hook_drush_command().
 */
function mica_client_drush_command() {
  $items['highcharts-download'] = array(
    'callback' => 'mica_client_drush_download',
    'aliases' => 'dhi',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'description' => dt('Downloads the required highcharts library from highcharts.com.'),
    'arguments' => array(
      'path' => dt('Optional. The path to the download folder. If omitted, Drush will use the default location (<code>sites/all/libraries/highcharts</code>).'),
    ),
  );
  return $items;
}

/**
 * Downloads
 */
function mica_client_drush_download() {
  $args = func_get_args();
  if ($args[0]) {
    $path = $args[0];
  }
  else {
    // $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/sites/all/libraries';
    $path = drush_get_context('DRUSH_DRUPAL_ROOT');
  }
  // Create the path if it does not exist.
  if (!is_dir($path . '/sites/all/libraries')) {
    drush_op('mkdir', $path . '/sites/all/libraries');
  }
  if (!is_dir($path . '/sites/all/libraries/highcharts')) {
    drush_op('mkdir', $path . '/sites/all/libraries/highcharts');
  }
  if (!is_dir($path . '/sites/all/libraries/highcharts/js')) {

    drush_op('mkdir', $path . '/sites/all/libraries/highcharts/js');
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }
  else {
    drush_log('No dir @path', array('@path' => $path), 'notice');
  }
  $path = $path . '/sites/all/libraries/highcharts/js';
  chdir($path);

  $svn_cmd = 'wget   http://code.highcharts.com/highcharts.js';
  if (drush_shell_exec($svn_cmd)) {
    drush_log(dt('Highcharts.js  was downloaded to !path.', array('!path' => ' ' . $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download Highcharts.js to !path.', array('!path' => ' ' . $path)) . '<br/>' . dt('Attempted command: !wget.', array('!wget' => '<code>' . $svn_cmd . '</code>')), 'error');
  }

  $svn_cmd = 'wget   http://code.highcharts.com/highcharts-more.js';
  if (drush_shell_exec($svn_cmd)) {
    drush_log(dt('Highcharts-more.js  was downloaded to !path.', array('!path' => ' ' . $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download Highcharts-more.js to !path.', array('!path' => ' ' . $path)) . '<br/>' . dt('Attempted command: !wget.', array('!wget' => '<code>' . $svn_cmd . '</code>')), 'error');
  }

}

