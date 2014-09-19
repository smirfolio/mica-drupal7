<?php

include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_get_datasets() {
  $node_view = node_view(node_load(variable_get('dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'datasets');
}

function mica_client_dataset_get_harmonization_datasets() {
  $node_view = node_view(node_load(variable_get('harmo_dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'harmonization-datasets');
}

function mica_client_dataset_get_study_datasets() {
  $node_view = node_view(node_load(variable_get('study_dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'study-datasets');
}

function _mica_client_dataset_get_datasets_page($node_view, $dataset_resource) {
  $resource = new MicaDatasetResource();
  $datasets = $resource->get_datasets($dataset_resource);
  // TODO implement search form and pagination

  pager_default_initialize($datasets->total, 5, $element = 0);
  $pager_output = theme('pager', array('quantity' => $datasets->total));

  return theme('mica_client_dataset-list', array(
    'node_page' => $node_view,
    'datasets' => $datasets,
    'pager_wrap' => $pager_output
  ));
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

function mica_client_dataset_type($dataset) {
  return !empty($dataset->{'obiba.mica.StudyDatasetDto.type'}) ? 'study-dataset' : 'harmonization-dataset';
}
