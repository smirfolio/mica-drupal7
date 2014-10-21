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
  return _mica_client_dataset_get_datasets_page($node_view, 'harmonization_datasets');
}

function mica_client_dataset_get_study_datasets_list() {
  $node_view = node_view(node_load(variable_get('study_dataset_page')));
  $node_view['#node']->title = '';
  return _mica_client_dataset_get_datasets_page($node_view, 'study_datasets');
}

function _mica_client_dataset_get_datasets_page($node_view, $dataset_resource) {
  $context['url'] = '/drupal/mica/refresh_list_datasets_' . $dataset_resource;
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $query = NULL;
  $sort = NULL;
  $sort_by = NULL;
  $list_datasets = '';
  if (!empty($_GET['search-query'])) {
    $query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $sort_by = $_GET['search-sort-order'];
  }

  $resource_dataset = mica_client_dataset_correct_resource_server($dataset_resource);
  $response = mica_client_dataset_get_datasets($query, $sort, $sort_by, $resource_dataset);
  $totalHits = empty($response) ? 0 : $response->getTotalHits();
  pager_default_initialize($totalHits, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $summaries = empty($response) ? array() : $response->getSummaries();
  if (!empty($summaries)) {
    foreach ($summaries as $dataset) {
      $list_datasets .= theme('mica_client_dataset-list-page-block', array(
        'dataset' => $dataset
      ));
    }
  }
  else {
    $list_datasets = t('No dataset found');
  }
  return theme('mica_client_dataset-list', array(
    "form_search" => drupal_get_form('mica_client_dataset_create_form'),
    'node_page' => $node_view,
    "total_items" => $totalHits,
    'list_datasets' => $list_datasets,
    'pager_wrap' => $pager_output,
    'dataset_type' => $dataset_resource
  ));
}

function mica_client_dataset_correct_resource_server($dataset_resource) {
  $resource = array(
    'datasets' => 'datasets',
    'harmonization_datasets' => 'datasets/harmonization',
    'study_datasets' => 'datasets/study'
  );
  return $resource[$dataset_resource];
}

function mica_client_dataset_get_datasets($query, $sort, $sort_by, $dataset_resource) {
  $from = 0;
  $resource = new MicaDatasetResource();
  if (!empty($_GET['page'])) {
    $from = $resource->pagination_list_search_parameters($_GET['page'], 'list-datasets', 5);
  }

  $response = $resource->get_datasets($dataset_resource, NULL, $query, $from, NULL, $sort, $sort_by);
  if (!empty($response)) {
    $_SESSION['list-datasets']['aggregations']['totalHits'] = $response->getTotalHits();
  }

  return $response;
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
  drupal_json_output(mica_client_dataset_themed_list_dataset($list_datasets));
}

function mica_client_dataset_retrieve_harmonizationDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = mica_client_dataset_get_datasets($query, $sort, $sort_order, 'harmonization');
  drupal_json_output(mica_client_dataset_themed_list_dataset($list_datasets));
}

function mica_client_dataset_retrieve_studyDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = mica_client_dataset_get_datasets($query, $sort, $sort_order, 'study');
  drupal_json_output(mica_client_dataset_themed_list_dataset($list_datasets));
}

Function mica_client_dataset_themed_list_dataset($list_datasets) {
  $list_datasets_rendered = '';
  foreach ($list_datasets->getSummaries() as $dataset) {
    $list_datasets_rendered .= theme('mica_client_dataset-list-page-block', array(
      'dataset' => $dataset,
    ));
  }
  $data['list'] = $list_datasets_rendered;
  $data['total'] = $list_datasets->getTotalHits();
  return $data;
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

