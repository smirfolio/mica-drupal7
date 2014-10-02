<?php

include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_get_datasets_list() {
  $node_view = node_view(node_load(variable_get('dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'datasets');
}

function mica_client_dataset_get_harmonization_datasets_list() {
  $node_view = node_view(node_load(variable_get('harmo_dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'harmonization-datasets');
}

function mica_client_dataset_get_study_datasets_list() {
  $node_view = node_view(node_load(variable_get('study_dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'study-datasets');
}

function _mica_client_dataset_get_datasets_page($node_view, $dataset_resource) {
  $context['captions'] = array('default' => 'Dataset', 'plural' => 'Datasets');
  $context['url'] = 'refresh_list_datasets_' . $dataset_resource;
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $query = NULL;
  $sort = NULL;
  $sort_by = NULL;

  if (!empty($_GET['search-query'])) {
    $query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $sort_by = $_GET['search-sort-order'];
  }

  $datasets = mica_client_dataset_get_datasets($query, $sort, $sort_by, $dataset_resource);

  pager_default_initialize($datasets->total, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $list_datasets = theme('mica_client_dataset-list-page-block', array(
    'list_dataset' => $datasets,
  ));
  return theme('mica_client_dataset-list', array(
    "form_search" => drupal_get_form('mica_client_dataset_create_form'),
    'node_page' => $node_view,
    "total_items" => $datasets->total,
    'list_datasets' => $list_datasets,
    'pager_wrap' => $pager_output
  ));
}

function mica_client_dataset_get_datasets($query, $sort, $sort_by, $dataset_resource) {
  $from = 0;
  $resource = new MicaDatasetResource();
  if (!empty($_GET['page'])) {
    $from = $resource->pagination_list_search_parameters($_GET['page'], 'list-datasets', 5);
  }

  $datasets = $resource->get_datasets($dataset_resource, NULL, $query, $from, NULL, $sort, $sort_by);
  $_SESSION['list-datasets']['aggregations']['totalHits'] = $datasets->total;
  return $datasets;
}

function mica_client_dataset_create_form() {
  $context =
    array(
      'options' => //
        array()
    );

  return mica_client_commons_create_search_form($context);
}

function mica_client_dataset_retrieve_datasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = mica_client_dataset_get_datasets($query, $sort, $sort_order, 'datasets');
//  dpm($list_datasets);
  pager_default_initialize($list_datasets->total, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $list_datasets_rendered = theme('mica_client_dataset-list-page-block', array(
    'list_dataset' => $list_datasets,
    "pager_wrap" => $pager_output
  ));
  $data['list_studies'] = $list_datasets_rendered;
  $data['total'] = $list_datasets->total;
  drupal_json_output($data);
}

function mica_client_dataset_retrieve_harmonizationDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = mica_client_dataset_get_datasets($query, $sort, $sort_order, 'harmonization-datasets');
  dpm($list_datasets);
  pager_default_initialize($list_datasets->total, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $list_datasets_rendered = theme('mica_client_dataset-list-page-block', array(
    'list_dataset' => $list_datasets,
    "pager_wrap" => $pager_output
  ));
  $data['list_studies'] = $list_datasets_rendered;
  $data['total'] = $list_datasets->total;
  drupal_json_output($data);
}

function mica_client_dataset_retrieve_studyDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = mica_client_dataset_get_datasets($query, $sort, $sort_order, 'study-dataset');
  pager_default_initialize($list_datasets->total, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $list_datasets_rendered = theme('mica_client_dataset-list-page-block', array(
    'list_dataset' => $list_datasets,
    "pager_wrap" => $pager_output
  ));
  $data['list_studies'] = $list_datasets_rendered;
  $data['total'] = $list_datasets->total;
  drupal_json_output($data);
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
