<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_page_detail($resource_dataset, $dataset_id) {
  dpm($resource_dataset, $dataset_id);
  $dataset_resource = new MicaDatasetResource();
  $dataset_type_resource = NULL;
  if (!empty($resource_dataset) && $resource_dataset == 'dataset') {
    $study_datasets_dto = $dataset_resource->get_dataset('harmonization-dataset', $dataset_id);
    $dataset_type_resource = $study_datasets_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    drupal_set_title(mica_client_commons_get_localized_field($study_datasets_dto, 'name'));
    // dpm($study_datasets_dto);
  }
  elseif (!empty($resource_dataset) && $resource_dataset == 'study') {
    $study_datasets_dto = $dataset_resource->get_dataset('study-dataset', $dataset_id);
    $dataset_type_resource = $study_datasets_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    drupal_set_title(mica_client_commons_get_localized_field($study_datasets_dto, 'name'));
    //  dpm($study_datasets_dto);
  }

  return theme('mica_client_datasets-detail', array(
    'dataset_dto' => $study_datasets_dto,
    'dataset_type' => $dataset_type_resource
  )) .
  mica_client_dataset_study_tables($dataset_type_resource);
  //.
//  mica_client_dataset_variables($resource_dataset, $dataset_id);
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

function mica_client_dataset_variables($resource_dataset, $id_dataset) {
  $dataset_resource = new MicaDatasetResource();
  $parmDto_request = array(0 => array('field' => 'datasetId', 'terms' => array($id_dataset)));
  $var_tab = mica_client_dataset_variables_table($dataset_resource->variables_search($resource_dataset, $parmDto_request));
  return theme('mica_client_datasets-tables', array('tab_var' => $var_tab, 'title_section' => t('Variables')));;
}

function mica_client_dataset_variables_table($variables) {
  if (!empty($variables['data'])) {
    foreach ($variables['data'] as $variable) {
      $name = $variable->name;
      $rows[] = array(
        l($name, 'mica/variable/' . mica_client_commons_to_slug($name) . '/' . $variable->id),
        !empty($variable->variableLabel) ? mica_client_commons_get_localized_field($variable, 'variableLabel') : '-',
        !empty($variable->datasetName) ? mica_client_commons_get_localized_field($variable, 'datasetName') : '-',
      );
    }
  }
//dpm($studies['totalHits']);
  $headers = array(
    t('Variables'),
    t('Label'),
    t('Dataset')
  );

  $args = array('quantity' => $variables['totalHits'], 'element' => MicaDatasetResource::PAGINATE_variables);
  pager_default_initialize($variables['totalHits'], MicaDatasetResource::SIZE_RESPONSE, MicaDatasetResource::PAGINATE_variables);

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows, // empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
    )
  ) . theme('pager', $args);
}


