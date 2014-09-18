<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_page_detail($dataset_type, $dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  $dataset_dto = NULL;
  $dataset_type_dto = NULL;
  $dataset_harmonizations_dto = NULL;

  $dataset_dto = $dataset_resource->get_dataset($dataset_type, $dataset_id);
  if (!empty($dataset_dto)) {
    if ($dataset_type == 'study-dataset') {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    }
    else {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
      // TODO fix limit=-1
      $dataset_harmonizations_dto =  $dataset_resource->get_variables_harmonizations($dataset_type, $dataset_id, 0, 10000, 'index');
    }

    drupal_set_title(mica_client_commons_get_localized_field($dataset_dto, 'name'));

    drupal_set_breadcrumb(array(
      l('Home', '<front>'),
      l(t('Datasets'), 'mica/datasets'),
      l(($dataset_type == 'study-dataset' ? t('Study Datasets') : t('Harmonization Datasets')), 'mica/datasets/' . $dataset_type . 's')
    ));

    return theme('mica_client_datasets-detail', array(
      'dataset_dto' => $dataset_dto,
      'dataset_type_dto' => $dataset_type_dto,
      'dataset_harmonizations_dto' => $dataset_harmonizations_dto,
      'dataset_variables_aggs' => NULL,//mica_client_dataset_get_variables($dataset_dto->id),
    ));
  }
  else {
    drupal_set_title(t('Dataset not found'));
    return '';
  }
}


function mica_client_dataset_study_tables_table($dataset_type_dto) {
  $study_summaries = array();
  if (!empty($dataset_type_dto->studyTables)) {
    foreach ($dataset_type_dto->studyTables as $study_table) {
      array_push($study_summaries, $study_table->studySummary);
    }
  }

  if (!empty($dataset_type_dto->studyTable)) {
    $study_table = $dataset_type_dto->studyTable;
    array_push($study_summaries, $study_table->studySummary);
  }

  $rows = mica_client_study_study_summaries_table_rows($study_summaries);
  $headers = mica_client_study_study_summaries_table_headers();

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No study found'),
      'sticky' => FALSE
    )
  );
}

function mica_client_dataset_harmonizations_table($dataset_type_dto, $dataset_harmonizations_dto) {
  $rows = array();
  $headers = array(t('Variable'));
  $study_ids = array();

  if (!empty($dataset_type_dto->studyTables)) {
    foreach ($dataset_type_dto->studyTables as $study_table) {
      $study_summary = $study_table->studySummary;
      $study_ids[] = $study_summary->id;
      $acronym = mica_client_commons_get_localized_field($study_summary, 'acronym');
      array_push($headers, l($acronym, 'mica/study/' . $study_summary->id));
    }
  }

  if (!empty($dataset_harmonizations_dto->variableHarmonizations)) {
    foreach ($dataset_harmonizations_dto->variableHarmonizations as $variable_harmonization) {
      $row = array(
        l($variable_harmonization->resolver->name, 'mica/variable/' . $variable_harmonization->resolver->id)
      );

      foreach ($study_ids as $study_id) {
        $found = FALSE;
        foreach ($variable_harmonization->datasetVariableSummaries as $variable_summary) {
          if ($variable_summary->resolver->studyId == $study_id) {
            $status = strtolower(_mica_client_variable_attributes_detail($variable_summary, 'status'));
            $row[] = empty($status) ? '-' : $status;
            $found = TRUE;
            break;
          }
        }
        if (!$found) {
          $row[] = '-';
        }
      }

      $rows[] = $row;
    }
  }

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No harmonized variables found'),
      'sticky' => FALSE
    )
  );


}

/**
 * Get the facets of the variables for this dataset.
 * @param $dataset_id
 * @return array
 */
function mica_client_dataset_get_variables($dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  return $dataset_resource->variables_search(array(
    0 => array(
      'field' => 'datasetId',
      'terms' => array($dataset_id)
    )
  ), 0);
}


