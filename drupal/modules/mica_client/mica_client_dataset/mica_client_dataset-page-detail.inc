<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_page_detail($resource_dataset, $dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  $datset_type_resource = NULL;
  if (!empty($resource_dataset) && $resource_dataset == 'dataset') {
    $study_datasets_dto = $dataset_resource->get_dataset('harmonization-dataset', $dataset_id);
    $datset_type_resource = $study_datasets_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    drupal_set_title('Harmonized dataset: ' . mica_client_commons_get_localized_field($study_datasets_dto, 'name'));
    $varaibles_tab = mica_client_dataset_get_variables('harmonization-dataset', $dataset_id);
    dpm($study_datasets_dto);
  }
  elseif (!empty($resource_dataset) && $resource_dataset == 'study') {
    $study_datasets_dto = $dataset_resource->get_dataset('study-dataset', $dataset_id);
    $datset_type_resource = $study_datasets_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    drupal_set_title('Study dataset: ' . mica_client_commons_get_localized_field($study_datasets_dto, 'name'));
    $varaibles_tab = mica_client_dataset_get_variables('study-dataset', $dataset_id);
    dpm($study_datasets_dto);
  }


  // drupal_set_title(mica_client_commons_get_localized_field($StudyDto, 'name'));

  return theme('mica_client_datasets-detail', array(
    'dataset_dto' => $study_datasets_dto,
    'datset_type' => $datset_type_resource
  )) .
  mica_client_dataset_study_tables($datset_type_resource) .
  $varaibles_tab;
}


function mica_client_dataset_study_tables($datset_type_resource) {
  $study_tab_rows = array();
  ///$datset_type_resource
  if (!empty($datset_type_resource->studyTables)) {
    foreach ($datset_type_resource->studyTables as $key_dataset => $study_table) {
      $study_tab_rows[$key_dataset] = array(
        'data' => array(
          'study' => l($study_table->studyId, 'mica/study/' . $study_table->studyId .
            '/' . $study_table->studyId),
          'project' => $study_table->project,
          'table' => $study_table->table
        )
      );

    }
    $study_tab = theme(
      'table',
      array(
        'header' => array(t('Study'), t('Project'), t('Table')),
        'rows' => $study_tab_rows,
        'empty' => t('No data found'),
        'sticky' => FALSE,
        'attributes' => array('id' => 'variables_overview')
      )
    );
  }

  if (!empty($datset_type_resource->studyTable)) {
    $study_tab['study-dataset'] = $datset_type_resource->studyTable;
  }


  return theme('mica_client_datasets-tables', array('tab_var' => $study_tab, 'title_section' => t('Studies')));
}

function mica_client_dataset_get_variables($resources, $id_dataset) {

  $row_variablas = array();
  $dataset_resource = new MicaDatasetResource();
  $variables = $dataset_resource->get_varaibles($resources, $id_dataset);
  foreach ($variables->getVariablesList() as $key_varable => $list) {
    // dpm($list);
    $row_variablas[$key_varable] = array(
      'name' => l($list->name, 'mica/variable/' . mica_client_commons_to_slug($list->name) . '/' . $list->id),
      'label' => mica_client_commons_get_localized_field($list->getAttributes(0), 'values'),
      'dataset' => mica_client_commons_get_localized_field($list, 'datasetName'),
    );
  }
  $per_page = $dataset_resource::SIZE_RESPONSE;
  pager_default_initialize($variables->total, $per_page);
  // dpm( theme('pager', array('quantity' => $variables->total)));
  $var_tab = theme('table',
      array(
        'header' => array(t('Name'), t('Label'), t('Dataset')),
        'rows' => $row_variablas,
        'empty' => t('No data found'),
        'sticky' => FALSE,
        'attributes' => array('id' => 'variables_overview')
      )
    ) . theme('pager', array('quantity' => 5, 'tags' => array('<<', '<', '', '>', '>>')));
  return theme('mica_client_datasets-tables', array('tab_var' => $var_tab, 'title_section' => t('Variables')));
}
