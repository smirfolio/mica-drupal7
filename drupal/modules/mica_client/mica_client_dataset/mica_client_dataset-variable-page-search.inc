<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_variable_page_search($request) {

  drupal_set_title('Varibales Search');

  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/mica_studies.css', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/mica-client-study-search.js', 'file');
  drupal_add_js(array('mica_client_study' => array('queries' => 'test_param')), 'setting');

  $rows = array();
  $variable_resource = new MicaDatasetResource();
  $variables = $variable_resource->variables_search($request);

  foreach ($variables['data'] as $variable) {
    $name = $variable->name;
    $rows[] = array(
      l($name, 'mica/variable/' . mica_client_commons_to_slug($name) . '/' . $variable->id),
      !empty($variable->variableLabel) ? mica_client_commons_get_localized_field($variable, 'variableLabel') : '-',
      !empty($variable->datasetName) ? mica_client_commons_get_localized_field($variable, 'datasetName') : '-',
    );
  }
//dpm($studies['totalHits']);
  $headers = array(
    t('Variables'),
    t('Label'),
    t('Dataset')
  );
  $per_page = $variable_resource::SIZE_RESPONSE;
  pager_default_initialize($variables['totalHits'], $per_page);

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows, // empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
    )
  ) . theme('pager', array('quantity' => 10));

}