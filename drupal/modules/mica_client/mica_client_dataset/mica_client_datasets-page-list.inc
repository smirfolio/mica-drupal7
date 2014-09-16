<?php

include_once('includes/mica_client_dataset_resource.inc');
function mica_client_dataset_get_datastes() {
  $node_rendred = node_view(node_load(variable_get('dataset_page')));
  $node_rendred['#node']->title = '';
  return $node_rendred;
}

function mica_client_dataset_get_harmonization_datasets() {
  $dataset_resource = new MicaDatasetResource();
  $node_rendred = node_view(node_load(variable_get('harmo_dataset_page')));
  $harmo_datasets_dto = $dataset_resource->get_datasets('harmonization-datasets');
  $node_rendred['#node']->title = '';
  $datasets_table = _mica_client_dataset_get_datasets_table($harmo_datasets_dto, 'harmonization-dataset');
  $node_rendred['body']['#items'][1]['value'] = $datasets_table;
  $node_rendred['body']['#items'][1]['safe_value'] = $datasets_table;
  $node_rendred['body'][1]['#markup'] = $datasets_table;
  return $node_rendred;
}

function mica_client_dataset_get_study_datasets() {
  $output = array();
  $dataset_resource = new MicaDatasetResource();
  $node_rendred = node_view(node_load(variable_get('study_dataset_page')));
  $study_datasets_dto = $dataset_resource->get_datasets('study-datasets');
  $node_rendred['#node']->title = '';
  $datasets_table = _mica_client_dataset_get_datasets_table($study_datasets_dto, 'study-dataset');
  $node_rendred['body']['#items'][1]['value'] = $datasets_table;
  $node_rendred['body']['#items'][1]['safe_value'] = $datasets_table;
  $node_rendred['body'][1]['#markup'] = $datasets_table;

  return $node_rendred;
}

function _mica_client_dataset_get_datasets_table($datasets, $type) {
  $dataset_rows = array();
  foreach ($datasets as $key_dataset => $dataset_dto) {
    $dce_description = NULL;
    //
    if (!empty($dataset_dto->description)) {
      $dataset_description = theme('box', truncate_utf8(mica_client_commons_get_localized_field($dataset_dto, 'description'), 50, TRUE, TRUE));
    }
    $dataset_name = mica_client_commons_get_localized_field($dataset_dto, 'name');

    $dataset_rows[$key_dataset] = array(
      'data' => array(
        'label' => l($dataset_name, 'mica/' . $type . '/' . $dataset_dto->id . '/' . mica_client_commons_to_slug($dataset_name)),
        'desc' => !empty($dataset_description) ? $dataset_description : '-'
      )
    );
  }

  $dataset = theme(
    'table',
    array(
      'header' => array(t('Name'), t('Description')),
      'rows' => $dataset_rows,
      'empty' => t('No dataset found'),
      'sticky' => FALSE,
      'attributes' => array('id' => 'variables_overview')
    )
  );
  return $dataset;
}
