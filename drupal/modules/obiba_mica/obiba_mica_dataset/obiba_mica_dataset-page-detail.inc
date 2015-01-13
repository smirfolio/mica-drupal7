<?php
include_once('includes/obiba_mica_dataset_resource.inc');

function obiba_mica_dataset_page_detail($dataset_type, $dataset_id) {
  if (drupal_get_library('obiba_mica_dataset', 'datatables')) {
    drupal_add_library('obiba_mica_dataset', 'datatables');
  }
  else {
    obiba_mica_dataset_datatables_external_source();
  }
  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(drupal_get_path('module', 'obiba_mica_dataset') . '/js/obiba_mica_dataset_datatable_init.js', 'file');
  // drupal_add_js(drupal_get_path('module', 'obiba_mica_dataset') . '/js/obiba_mica_dataset_download_harmonizations.js', 'file');
  $dataset_resource = new MicaDatasetResource();
  $dataset_dto = NULL;
  $dataset_type_dto = NULL;
  $variables_dataset = NULL;
  $variables_table_output = NULL;
  unset($_SESSION['ajax']);
  $dataset_dto = $dataset_resource->get_dataset($dataset_type, $dataset_id);
  $_SESSION['ajax']['variable'] = serialize($dataset_dto);
  if (!empty($dataset_dto)) {
    $variables_dataset = $dataset_resource->get_variables($dataset_type, $dataset_id, 0, 1);
    if ($dataset_type == 'study-dataset') {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    }
    else {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    }
    drupal_set_title(obiba_mica_commons_get_localized_field($dataset_dto, 'name'));

    drupal_set_breadcrumb(array(
      l('Home', '<front>'),
      l(t('Datasets'), 'mica/datasets'),
      l(($dataset_type == 'study-dataset' ? t('Study Datasets') : t('Harmonization Datasets')), 'mica/datasets/' . $dataset_type . 's')
    ));

    return theme('obiba_mica_dataset-detail', array(
      //TODO implement resources to perform queries in variables resources
      //   "form_search" => drupal_get_form('obiba_mica_dataset_create_form'),
      'dataset_dto' => $dataset_dto,
      'coverage' => obiba_mica_dataset_coverage($dataset_dto->id),
      'dataset_type_dto' => $dataset_type_dto,
      'dataset_type' => $dataset_type,
      'harmonization_table_legend' => theme('obiba_mica_dataset-harmonization-table-legend', array('clickable' => TRUE)),
      'variables_dataset' => $variables_dataset,
    ));
  }
  else {
    drupal_set_title(t('Dataset not found'));
    return '';
  }
}

/*
 * Ajax Variable table Call header
 * */
function obiba_mica_dataset_Variables_table_ajax_header($dataset_type) {
  $dataset_dto = unserialize($_SESSION['ajax']['variable']);
  if ($dataset_type == 'study-dataset') {
    // $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    $header = obiba_mica_dataset_studies_Variables_table_ajax_header();
  }
  else {
    $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    $header = obiba_mica_dataset_harmonizations_Variables_table_ajax_header($dataset_type_dto);
  }

  $data['header'] = $header;
  return drupal_json_output($data);
}

function obiba_mica_dataset_get_sorted_by_column() {
  if (!empty($_GET['sColumns'])) {
    $_columns = explode(',', $_GET['sColumns']);
    foreach ($_columns as $key => $_column) {
      if (!empty($_GET['bSortable_' . $key])) {
        if ($_GET['iSortCol_0'] == $key) {
          $sorting['sort'] = $_column;
          $sorting['order'] = $_GET['sSortDir_0'];
          return $sorting;
        }
      }
    }
  }
}

/*
 * Ajax Variable table Call data
 * */

function obiba_mica_dataset_Variables_table_ajax_data($dataset_type, $id_dataset) {
  $dataset_resource = new MicaDatasetResource();
  $from = 0;
  $size = 10;
  $dataset_sort_by = NULL;
  $dataset_query = NULL;

  if (!empty($_GET['iDisplayStart'])) {
    $from = $_GET['iDisplayStart'];
  }
  if (!empty($_GET['iDisplayLength'])) {
    $size = $_GET['iDisplayLength'];
  }

  $sort = obiba_mica_dataset_get_sorted_by_column($dataset_type);

  $dataset_dto = unserialize($_SESSION['ajax']['variable']);

  if ($dataset_type == 'study-dataset') {
    //$dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
    $variables_dataset = $dataset_resource->get_variables($dataset_type,
      $id_dataset,
      $from,
      $size,
      !empty($sort['sort']) ? $sort['sort'] : 'index',
      !empty($sort['order']) ? $sort['order'] : NULL
    );

    $data_variable = obiba_mica_dataset_studies_table_data($variables_dataset);

  }
  else {
    $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');
    $variables_dataset = $dataset_resource->get_variables_harmonizations($dataset_type,
      $id_dataset,
      $from,
      $size,
      !empty($sort['sort']) ? $sort['sort'] : 'index',
      !empty($sort['order']) ? $sort['order'] : NULL
    );
    $data_variable = obiba_mica_dataset_harmonizations_table_data($dataset_type_dto, $variables_dataset);
  }

  $data['sEcho'] = $_GET["sEcho"] ? $_GET["sEcho"] : 1;
  $data['iTotalRecords'] = $variables_dataset->total;
  $data['iTotalDisplayRecords'] = $variables_dataset->total;
  $data['aaData'] = $data_variable;
  return drupal_json_output($data);
}

/*
 * studies dataset ajax variable table
 *
 * */
function obiba_mica_dataset_studies_Variables_table_ajax_header() {
  return array(
    array(
      "sTitle" => '',
      "data" => "index",
      "mDataProp" => "index",
      "name" => "index",
      "visible" => FALSE
    ),
    array(
      "sTitle" => t('Variable'),
      "data" => "name",
      "mDataProp" => "name",
      "name" => "name",
      "width" => "25%"
    ),
    array(
      "sTitle" => t('Label'),
      "data" => "label",
      "mDataProp" => "label",
      "name" => "label",
      "orderable" => FALSE
    ),
    array(
      "sTitle" => t('Classifications'),
      "data" => "classifications",
      "mDataProp" => "classifications",
      "name" => "classifications",
      "orderable" => FALSE
    )
  );
}

function obiba_mica_dataset_studies_table_data($variables_dataset) {
  $rows = array();
  if (!empty($variables_dataset->variables)) {
    foreach ($variables_dataset->variables as $variable) {
      $var_row = l($variable->name, 'mica/variable/' . $variable->id);
      $domains = _obiba_mica_variable_domains_list($variable);
      $rows[] = array(
        "index" => '',
        "name" => $var_row,
        "label" => obiba_mica_commons_get_localized_field($variable, 'name'),
        "classifications" => $domains
      );
    }
  }
  return $rows;
}

/*********End Studies ajax header *************/

/*
 * Harmonization ajax variable table
 * */
function obiba_mica_dataset_harmonizations_Variables_table_ajax_header($dataset_type_dto) {
  $nbrStudies = count($dataset_type_dto->studyTables);
  $witdhColStudy = (100 - (1 + 25)) / $nbrStudies;
  if (!empty($dataset_type_dto->studyTables)) {
    $header[] = array(
      "sTitle" => '',
      "data" => "index",
      "name" => "index",
      "mDataProp" => "index",
      "visible" => FALSE
    );

    $header[] = array(
      "sTitle" => t('Variable'),
      "data" => "variable",
      "name" => "name",
      "mDataProp" => "name",
      "width" => "25%"
    );
    foreach ($dataset_type_dto->studyTables as $study_table) {
      $study_summary = $study_table->studySummary;
      $acronym = obiba_mica_commons_get_localized_field($study_summary, 'acronym');
      $title_header = l($acronym, 'mica/study/' . $study_summary->id);
      $title_header = str_replace('"', '\'', $title_header);
      if (!empty($study_table->name)) {
        $name = ' <small title="' . obiba_mica_commons_get_localized_field($study_table, 'description') . '">' . obiba_mica_commons_get_localized_field($study_table, 'name') . '</small>';
        $name = str_replace('"', '\'', $name);
        $header[] = array(
          "data" => str_replace(' ', '_', $acronym . obiba_mica_commons_get_localized_field($study_table, 'name')),
          "sTitle" => $title_header . $name,
          "name" => str_replace(' ', '_', $acronym . obiba_mica_commons_get_localized_field($study_table, 'name')),
          "orderable" => FALSE,
          "width" => $witdhColStudy . "%"
        );
      }
      else {
        $header[] = array(
          "data" => $acronym,
          "sTitle" => $title_header,
          "name" => $acronym,
          "orderable" => FALSE,
          "width" => $witdhColStudy . "%"
        );
      }
    }
  }
  return $header;
}

function obiba_mica_dataset_harmonizations_table_data($dataset_type_dto, $dataset_harmonizations_dto) {
  $rows = array();
  if (!empty($dataset_type_dto->studyTables)) {

    if (!empty($dataset_harmonizations_dto->variableHarmonizations)) {

      foreach ($dataset_harmonizations_dto->variableHarmonizations as $variable_harmonization) {

        $row = array(
          "index" => '',
          "variable" =>
            l($variable_harmonization->resolver->name, 'mica/variable/' . $variable_harmonization->resolver->id)
        );

        foreach ($dataset_type_dto->studyTables as $study_table) {
          $found = FALSE;
          /*********************/
          $study_summary = $study_table->studySummary;
          $acronym = obiba_mica_commons_get_localized_field($study_summary, 'acronym');
          if (!empty($study_table->name)) {
            $Key_row = $acronym . obiba_mica_commons_get_localized_field($study_table, 'name');
          }
          else {
            $Key_row = $acronym;
          }
          $Key_row = str_replace(' ', '_', $Key_row);
          /*********************/
          foreach ($variable_harmonization->datasetVariableSummaries as $variable_summary) {
            if ($variable_summary->resolver->studyId == $study_table->studyId
              && $variable_summary->resolver->project == $study_table->project
              && $variable_summary->resolver->table == $study_table->table
            ) {
              $status = trim(strtolower(_obiba_mica_variable_attributes_detail($variable_summary, 'status', array(
                'maelstrom',
                'Mlstr_harmo'
              ))));
              $harmonized_variable_id = $variable_summary->resolver->id;
              $variable_title = $variable_summary->resolver->name . ' -- ' . obiba_mica_commons_get_localized_field($study_table->studySummary, 'acronym');
              if (!empty($study_table->name)) {
                $variable_title = $variable_title . ' (' . obiba_mica_commons_get_localized_field($study_table, 'name') . ')';
              }
              if (empty($status)) {
                $row[$Key_row] = l('<span class="glyphicon glyphicon-question-sign alert-danger" title="' . t('No status') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                  array(
                    'html' => TRUE,
                    'query' => array(
                      'title' => $variable_title
                    )
                  ));
              }
              elseif ($status == 'complete') {
                $row[$Key_row] = l('<span data-toggle="tooltip" title="Completed" class="glyphicon glyphicon-ok alert-success" title="' . t('Complete') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                  array(
                    'html' => TRUE,
                    'query' => array(
                      'title' => $variable_title
                    )
                  ));
              }
              elseif ($status == 'impossible') {
                $row[$Key_row] = l('<span class="glyphicon glyphicon-remove alert-danger" title="' . t('Impossible') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                  array(
                    'html' => TRUE,
                    'query' => array(
                      'title' => $variable_title
                    )
                  ));
              }
              elseif ($status == 'undetermined') {
                $row[$Key_row] = l('<span class="glyphicon glyphicon-question-sign alert-warning" title="' . t('Undetermined') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                  array(
                    'html' => TRUE,
                    'query' => array(
                      'title' => $variable_title
                    )
                  ));
              }
              else {
                $row[$Key_row] = l('-', 'mica/variable/' . $harmonized_variable_id);
              }
              $found = TRUE;
              break;
            }
          }
          if (!$found) {
            $row[$Key_row] = '<span class="glyphicon glyphicon-question-sign alert-danger" title="' . t('No status') . '"></span>';
          }
        }

        $rows[] = $row;
      }
    }
  }

  return $rows;
}

/*End harmonization variable ajax table */

function obiba_mica_dataset_coverage($dataset_id) {
  return obiba_mica_facet_search_query_charts(MicaClient::add_parameter_dto_query_link(array('variables' => array('terms' => array('datasetId' => $dataset_id)))));
}

function obiba_mica_dataset_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'name' => 'name'
        ) //
    );

  return obiba_mica_commons_create_search_form($context, FALSE);
}

function obiba_mica_dataset_study_tables_table($dataset_type_dto) {
  $study_tables = array();
  if (!empty($dataset_type_dto->studyTables)) {
    foreach ($dataset_type_dto->studyTables as $study_table) {
      array_push($study_tables, $study_table);
    }
  }

  if (!empty($dataset_type_dto->studyTable)) {
    array_push($study_tables, $dataset_type_dto->studyTable);
  }

  $rows = obiba_mica_dataset_study_tables_rows($study_tables);
  $headers = obiba_mica_study_study_summaries_table_headers();
  //array_splice($headers, 2, 0, array(t('Data Collection Events')));

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

function obiba_mica_dataset_study_tables_rows($study_tables) {
  $rows = array();
  if (!empty($study_tables)) {
    $study_dces = array();
    foreach ($study_tables as $study_table) {
      $population_name = $study_table->populationId;
      $dce_name = $study_table->dataCollectionEventId;
      foreach ($study_table->studySummary->populationSummaries as $population_summary) {
        if ($population_summary->id == $study_table->populationId) {
          $population_name = obiba_mica_commons_get_localized_field($population_summary, 'name');
          foreach ($population_summary->dataCollectionEventSummaries as $dce_summary) {
            if ($dce_summary->id == $study_table->dataCollectionEventId) {
              $dce_name = obiba_mica_commons_get_localized_field($dce_summary, 'name');
            }
          }
        }
      }
      $dce_full_name = $population_name . ' -- ' . $dce_name;
      if (!in_array($study_table->studyId, array_keys($study_dces))) {
        $study_dces[$study_table->studyId] = array();
      }
      if (!in_array($dce_full_name, $study_dces[$study_table->studyId])) {
        $study_dces[$study_table->studyId][] = $dce_full_name;
      }
    }
    $study_ids = array();
    foreach ($study_tables as $study_table) {
      if (!in_array($study_table->studyId, $study_ids)) {
        $study_ids[] = $study_table->studyId;
        $row = obiba_mica_study_study_summaries_table_row($study_table->studySummary);
        $dec_list = '<ul>';
        if (!empty($study_dces[$study_table->studyId])) {

          foreach ($study_dces[$study_table->studyId] as $dce_full_name) {
            $dec_list = $dec_list . '<li>' . $dce_full_name . '</li>';
          }
        }
        $dec_list = $dec_list . '</ul>';
        //array_splice($row, 2, 0, array($dec_list));
        $rows[] = $row;
      }
    }
  }
  return $rows;
}

/**
 * @param $dataset_id
 * @return array
 */
function obiba_mica_dataset_page_detail_download($dataset_id) {
  global $language;
  $dataset_resource = new MicaDatasetResource();
  $response = $dataset_resource->download_variables_harmonizations($dataset_id, $language->language);
  if (!empty($response)) {
    $headers = $dataset_resource->getLastResponseHeaders();
    drupal_add_http_header('Content-Type', $headers['Content-Type'][0] . '; utf-8');
    drupal_add_http_header('Content-Disposition', $headers['Content-Disposition'][0]);
    ob_clean();
    print $response->body;
    exit;
  }
}

/**
 * Get the facets of the variables for this dataset.
 * @param $dataset_id
 * @return array
 */
function obiba_mica_dataset_get_variables($dataset_id) {
  $dataset_resource = new MicaDatasetResource();
  return $dataset_resource->variables_search(array(
    0 => array(
      'field' => 'datasetId',
      'terms' => array($dataset_id)
    )
  ), 0);
}
