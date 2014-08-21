<?php
include_once('includes/mica_client_dataset_resource.inc');
include_once('mica_client_dataset-variable-page-search.inc');

function mica_client_dataset_page_detail($resource_dataset, $dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  $dataset_dto = NULL;
  $dataset_type_dto = NULL;

  if (!empty($resource_dataset) && $resource_dataset == 'study') {
    $dataset_dto = $dataset_resource->get_dataset('study-dataset', $dataset_id);
    if (!empty($dataset_dto)) {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    }
  }
  else {
    $dataset_dto = $dataset_resource->get_dataset('harmonization-dataset', $dataset_id);
    if (!empty($dataset_dto)) {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    }
  }

  if (!empty($dataset_dto)) {
    drupal_set_title(mica_client_commons_get_localized_field($dataset_dto, 'name'));

    return theme('mica_client_datasets-detail', array(
      'dataset_dto' => $dataset_dto,
      'dataset_type' => $dataset_type_dto
    )) .
    mica_client_dataset_study_tables($dataset_type_dto);
  }
  else {
    drupal_set_title(t('Dataset not found'));
    return '';
  }
}


function mica_client_dataset_study_tables($dataset_type_resource) {
  //dpm($dataset_type_resource);
  $study_summaries = array();
  $title = t('Studies');
  if (!empty($dataset_type_resource->studyTables)) {
    foreach ($dataset_type_resource->studyTables as $key_dataset => $study_table) {
      array_push($study_summaries, $study_table->studySummary);
    }
  }

  if (!empty($dataset_type_resource->studyTable)) {
    $title = t('Study');
    $study_table = $dataset_type_resource->studyTable;
    array_push($study_summaries, $study_table->studySummary);
  }

  $rows = mica_client_study_study_summaries_table_rows($study_summaries);
  $headers = mica_client_study_study_summaries_table_headers();

  $study_tab = theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No data found'),
      'sticky' => FALSE
    )
  );

  return theme('mica_client_datasets-tables', array('tab_var' => $study_tab, 'title_section' => $title));
}

function mica_client_dataset_get_variables($dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  return $dataset_resource->variables_search('dataset', array(
    0 => array(
      'field' => 'datasetId',
      'terms' => array($dataset_id)
    )
  ), 0);
}


