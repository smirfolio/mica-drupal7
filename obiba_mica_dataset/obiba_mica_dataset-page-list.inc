<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Code to dataset list page.
 */

include_once 'includes/obiba_mica_dataset_resource.inc';

/**
 * Get the dataset list.
 */
function obiba_mica_dataset_get_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered, 'datasets');
}

/**
 * Get the harmonized dataset list.
 */
function obiba_mica_dataset_get_harmonization_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('harmo_dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered,  DrupalMicaDatasetResource::HARMONIZED_DATASET);
}

/**
 * Get the study dataset list.
 */
function obiba_mica_dataset_get_study_datasets_list() {
  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('study_dataset_page'));
  drupal_set_title($node_rendered['#node']->title);
  return obiba_mica_dataset_get_datasets_page($node_rendered, DrupalMicaDatasetResource::COLLECTED_DATASET);
}

/**
 * Render the dataset list on a page template.
 */
function obiba_mica_dataset_get_datasets_page($node_view, $dataset_resource) {
  obiba_mica_commons_list_document_js('refresh_list_datasets_' . $dataset_resource);
  $list_datasets = '';

  $page_number = !empty($_GET['page']) ? $_GET['page'] : NULL;
  $query = !empty($_GET['search-query']) ? $_GET['search-query'] : NULL;
  $sort = !empty($_GET['search-sort']) ? $_GET['search-sort'] : NULL;
  $sort_by = !empty($_GET['search-sort-order']) ? $_GET['search-sort-order'] : NULL;
  $dataset_limits = !empty($_GET['search-nbr-result']) ? $_GET['search-nbr-result'] : NULL;

  $node_view['#node']->title = '';
  $resource_key = $page_number . $dataset_resource . $query . $sort . $sort_by . $dataset_limits;
  $cached_themed_list_datasets = obiba_mica_commons_get_cache('cached_'. __FUNCTION__ . $resource_key);
  if (!empty($cached_themed_list_datasets)) {
    return $cached_themed_list_datasets;
  }
  else {
    $dataset_class_name = obiba_mica_dataset_correct_resource_server($dataset_resource);
    $response = obiba_mica_dataset_get_datasets($query, $sort, $sort_by, $dataset_class_name, $dataset_limits);
    $total_hits = empty($response) ? 0 : $response->getTotalHits();
    $dataset_limits = !empty($dataset_limits) ? $dataset_limits : DrupalMicaClientResource::getResponsePageSizeSmall();
    pager_default_initialize($total_hits, $dataset_limits);
    $pager_output = theme('pager', array('quantity' => $dataset_limits));
    $summaries = empty($response) ? array() : $response->getSummaries();
    if (!empty($summaries)) {
      foreach ($summaries as $dataset) {
        $list_datasets .= theme('obiba_mica_dataset-list-page-block', array(
          'dataset' => $dataset,
        ));
      }
    }
    else {
      $list_datasets = variable_get_value('datasets_empty_label');
    }
    $themed_datasets_list = theme('obiba_mica_dataset-list', array(
      "form_search" => drupal_get_form('obiba_mica_dataset_create_form', $dataset_resource),
      'node_page' => $node_view,
      "total_items" => $total_hits,
      'list_datasets' => $list_datasets,
      'pager_wrap' => $pager_output,
      'dataset_type' => $dataset_resource,
      'study_type' => obiba_mica_dataset_get_study_type($dataset_resource)
    ));
    if ($total_hits !== 0) {
      obiba_mica_commons_set_cache('cached_'. __FUNCTION__ . $resource_key, $themed_datasets_list);
    }
    return $themed_datasets_list;
  }
}

/**
 * Helper to parse the correct resource mica server.
 */
function obiba_mica_dataset_correct_resource_server($dataset_resource) {
  $resource = array(
    'datasets' => NULL,
    DrupalMicaDatasetResource::HARMONIZED_DATASET => 'HarmonizationDataset',
    DrupalMicaDatasetResource::COLLECTED_DATASET => 'StudyDataset',
  );
  return $resource[$dataset_resource];
}

function obiba_mica_dataset_get_study_type($dataset_type) {
  switch ($dataset_type) {
    case DrupalMicaDatasetResource::COLLECTED_DATASET:
      return DrupalMicaStudyResource::INDIVIDUAL_STUDY;
    case DrupalMicaDatasetResource::HARMONIZED_DATASET:
      return DrupalMicaStudyResource::HARMONIZATION_STUDY;
    case DrupalMicaDatasetResource::ALL_DATASETS:
      return DrupalMicaStudyResource::ALL_STUDIES;
  }

  watchdog('Mica Client', 'Invalid dataset type ' . $dataset_type, WATCHDOG_WARNING);
  return DrupalMicaStudyResource::ALL_STUDIES;
}

/**
 * Get the datasets from server.
 */
function obiba_mica_dataset_get_datasets($query, $sort, $sort_by, $dataset_class_name, $dataset_limits = NULL) {
  $from = 0;
  $resource = new DrupalMicaDatasetResource();
  $size_response = !empty($dataset_limits) ? $dataset_limits : variable_get_value('mica_response_page_size_small');
  if (!empty($_GET['page'])) {
    $from = $resource->paginationListSearchParameters($_GET['page'], 'datasets', $size_response);
  }
  $response = $resource->getDatasets($dataset_class_name, NULL, $query, $from, $size_response, $sort, $sort_by);
  if (!empty($response)) {
    $_SESSION['datasets']['aggregations']['total_hits'] = $response->getTotalHits();
  }

  return $response;
}

/**
 * Search form creation on the dataset list page.
 */
function obiba_mica_dataset_create_form($form, &$form_state, $dataset_resource) {
  $localize = obiba_mica_commons_mica_server_localisation();
  $context = array(
    'options' => array(
      'studyTable.studyId,studyTable.populationId,start' => $localize->getTranslation('global.chronological')
    ),
    'default_sort' => 'name',
    'default_sort_order' => 'asc'
  );
  if (!empty($dataset_resource) && $dataset_resource === DrupalMicaDatasetResource::HARMONIZED_DATASET) {
    unset($context['options']['studyTable.studyId,studyTable.populationId,start']);
  }
  return obiba_mica_commons_create_search_form($context);
}

/**
 * Ajax callback to retrieve datasets.
 */
function obiba_mica_dataset_retrieve_datasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, NULL);
  if(!empty($list_datasets)){
  drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
  }
  else{
    return FALSE;
  }
}

/**
 * Ajax callback to retrieve harmonized datasets.
 */
function obiba_mica_dataset_retrieve_harmonizationDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, 'HarmonizationDataset');
  if(!empty($list_datasets)){
    drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
  }
  else{
    return FALSE;
  }
}

/**
 * Ajax callback to retrieve study datasets.
 */
function obiba_mica_dataset_retrieve_studyDatasets($query, $sort = NULL, $sort_order = NULL) {
  $list_datasets = obiba_mica_dataset_get_datasets($query, $sort, $sort_order, 'StudyDataset');
  if(!empty($list_datasets)) {
    drupal_json_output(obiba_mica_dataset_themed_list_dataset($list_datasets));
  }
  else{
    return FALSE;
  }
}

/**
 * Theme block datasets list.
 */
Function obiba_mica_dataset_themed_list_dataset($list_datasets) {
  $list_datasets_rendered = '';
  if (!empty($list_datasets)) {
    foreach ($list_datasets->getSummaries() as $dataset) {
      $list_datasets_rendered .= theme('obiba_mica_dataset-list-page-block', array(
        'dataset' => $dataset,
      ));
    }
    $data['list'] = $list_datasets_rendered;
    $data['total'] = $list_datasets->getTotalHits();
    return $data;
  }
  else {
    return FALSE;
  }
}
