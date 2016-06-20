<?php
/**
 * @file
 * Obiba Mica Graphics variable file
 */

$path_module_commons = drupal_get_path('module', 'obiba_mica_graphic');
include_once($path_module_commons . '/obiba_mica_graphic.admin.inc');

/**
 * Implements hook_variable_info().
 */
function obiba_mica_graphic_variable_info($options) {

  $variable['graphic_label'] = array(
    'title' => t('Statistics graphic Label'),
    'description' => t('The Statistics graphic section title'),
    'type' => 'string',
    'default' => 'Catalogue Statistics graphic',
  );

  $variable['graphics_blocks'] = array(
    'title' => t('Statistics graphic bocks'),
    'description' => t('Enable the Statistics graphic in some blocks'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['graphics_blocks_networks'] = array(
    'title' => t('Concerned Networks Statistics'),
    'description' => t('Please select the Concerned networks'),
    'type' => 'options',
    'default' => '',
  );

  $variable['graphics_blocks_aggregations'] = array(
    'title' => t('Aggregations statistics'),
    'description' => t('Please select the Aggregations statistics to show, and fill free to add a custom css'),
    'type' => 'string',
    'default' => array(
      NetworkStatistics::GEO_NBR_STAT => array(
        'value' => 'populations-selectionCriteria-countriesIso',
        'value_name' => 'col-md-6',
        'weight' => '-10',
        'enable' => 1,
      ),
      NetworkStatistics::METHODS_DESIGNS => array(
        'value' => 'methods-designs',
        'value_name' => 'col-md-6',
        'weight' => '-9',
        'enable' => 1,
      ),
      NetworkStatistics::NUMBER_PARTICIPANTS => array(
        'value' => 'numberOfParticipants-participant-range',
        'value_name' => 'col-md-6',
        'weight' => '-8',
        'enable' => 1,
      ),
      NetworkStatistics::BIO_SAMPLES => array(
        'value' => 'populations-dataCollectionEvents-bioSamples',
        'value_name' => 'col-md-6',
        'weight' => '-7',
        'enable' => 1,
      ),
    ),
  );

  $variable['graphics_content'] = array(
    'title' => t('Statistics graphic in networks page '),
    'description' => t('Enable the Statistics graphic in networks page'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['pie_slice_text_style_color'] = array(
    'title' => t('Pie slice text color'),
    'description' => t('Pleas enter the hex colors code'),
    'type' => 'string',
    'default' => '',
  );

  $variable['mica_graphic_colors'] = array(
    'title' => t('Used colors on the graphics'),
    'description' => t('Pleas select your desired colors'),
    'type' => 'string',
    'default' => array(
      'color1' => array(
        'value' => 'color1',
        'value_name' => '#e5edfb',
        'weight' => '-10',
        'enable' => 1,
      ),
      'color2' => array(
        'value' => 'color2',
        'value_name' => '#cfddf5',
        'weight' => '-9',
        'enable' => 1,
      ),
      'color3' => array(
        'value' => 'color3',
        'value_name' => '#b8cbed',
        'weight' => '-8',
        'enable' => 1,
      ),
      'color4' => array(
        'value' => 'color4',
        'value_name' => '#a0b8e2',
        'weight' => '-7',
        'enable' => 1,
      ),
      'color5' => array(
        'value' => 'color5',
        'value_name' => '#88a4d4',
        'weight' => '-6',
        'enable' => 1,
      ),
      'color6' => array(
        'value' => 'color6',
        'value_name' => '#000000',
        'weight' => '-5',
        'enable' => 0,
      ),
      'color7' => array(
        'value' => 'color7',
        'value_name' => '#000000',
        'weight' => '-4',
        'enable' => 0,
      ),
      'color8' => array(
        'value' => 'color8',
        'value_name' => '#000000',
        'weight' => '-3',
        'enable' => 0,
      ),
      'color9' => array(
        'value' => 'color9',
        'value_name' => '#000000',
        'weight' => '-2',
        'enable' => 0,
      ),
      'color10' => array(
        'value' => 'color10',
        'value_name' => '#000000',
        'weight' => '-1',
        'enable' => 0,
      ),
    ),
  );

  return $variable;
}
