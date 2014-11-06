<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_dataset_page_detail($dataset_type, $dataset_id) {
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
  $dataset_resource = new MicaDatasetResource();
  $dataset_dto = NULL;
  $dataset_type_dto = NULL;
  $variables_dataset = NULL;
  $variables_table_output = NULL;
  $dataset_dto = $dataset_resource->get_dataset($dataset_type, $dataset_id);
  if (!empty($dataset_dto)) {
    $from = 0;
    $dataset_sort = 'index';
    $dataset_sort_by = NULL;
    $dataset_query = NULL;
    if (!empty($_GET['search-query'])) {
      $dataset_query = $_GET['search-query'];
    }
    if (!empty($_GET['search-sort'])) {
      $dataset_sort = $_GET['search-sort'];
    }
    if (!empty($_GET['search-sort-order'])) {
      $dataset_sort_by = $_GET['search-sort-order'];
    }
    if (!empty($_GET['page'])) {
      $from = $dataset_resource->pagination_list_search_parameters($_GET['page'], 'list-datasets', 10);
    }
    if ($dataset_type == 'study-dataset') {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.StudyDatasetDto.type');
      $variables_dataset = $dataset_resource->get_variables($dataset_type,
        $dataset_id,
        $from, 10,
        $dataset_sort,
        $dataset_sort_by,
        $dataset_query
      );

      if (!empty($variables_dataset)) {
        $_SESSION['list-datasets']['aggregations']['totalHits'] = $variables_dataset->total;
        $variables_dataset->harmonization = NULL;
        $variables_dataset->study = TRUE;
        $variables_table_output = mica_client_dataset_study_variable_table($variables_dataset);
      }

    }
    else {
      $dataset_type_dto = $dataset_dto->getExtensionList('obiba.mica.HarmonizationDatasetDto.type');

      $variables_dataset = $dataset_resource->get_variables_harmonizations($dataset_type,
        $dataset_id,
        $from, 10,
        $dataset_sort,
        $dataset_sort_by,
        $dataset_query
      );
      if (!empty($variables_dataset)) {
        $_SESSION['list-datasets']['aggregations']['totalHits'] = $variables_dataset->total;

        $variables_dataset->study = NULL;
        $variables_dataset->harmonization = TRUE;
        $variables_table_output = mica_client_dataset_harmonizations_table($dataset_type_dto, $variables_dataset);
      }
    }

    drupal_set_title(mica_client_commons_get_localized_field($dataset_dto, 'name'));

    drupal_set_breadcrumb(array(
      l('Home', '<front>'),
      l(t('Datasets'), 'mica/datasets'),
      l(($dataset_type == 'study-dataset' ? t('Study Datasets') : t('Harmonization Datasets')), 'mica/datasets/' . $dataset_type . 's')
    ));

    return theme('mica_client_dataset-detail', array(
      //TODO implement resources to perform queries in variables resources
      //   "form_search" => drupal_get_form('mica_client_dataset_create_form'),
      'dataset_dto' => $dataset_dto,
      'coverage_dataset' => mica_client_dataset_coverage_variables($dataset_dto->id),
      'dataset_type_dto' => $dataset_type_dto,
      'variables_dataset' => $variables_dataset,
      'variables_table' => $variables_table_output,
      'dataset_variables_aggs' => NULL, //mica_client_dataset_get_variables($dataset_dto->id),
    ));
  }
  else {
    drupal_set_title(t('Dataset not found'));
    return '';
  }
}

function mica_client_dataset_coverage_variables($dataset_id) {

  $query_datasets_param =
    MicaClient::add_parameter_dto_query_link(array('variables' => array('terms' => array('datasetId' => $dataset_id))));

  $search_resources = new MicaSearchResource();
  $coverages = $search_resources->taxonomies_coverage($query_datasets_param);

  $taxonomy_charts = array();

  if (!empty($coverages->taxonomies)) {
    foreach ($coverages->taxonomies as $taxonomy_coverage) {
      $labels = array();
      $counts = array();
      foreach ($taxonomy_coverage->vocabularies as $key => $vocabulary_coverage) {
        if (!empty($vocabulary_coverage->count)) {
          $labels[] = mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles');
          $counts[] = $vocabulary_coverage->count;
        }
      }
      if (!empty($counts)) {
        $data[t('Variables')]['#type'] = 'chart_data';
        $data[t('Variables')]['#title '] = t('Variables');
        $data[t('Variables')] = $counts;
        $taxonomy_charts[] = array(
          'taxonomy' => $taxonomy_coverage->taxonomy,
          'chart' => mica_client_facet_search_stacked_column_chart($labels, $data, t('Number of variables'), 1000, 450, 'none')
        );
      }
    }
  }
  return $taxonomy_charts;
}

function mica_client_dataset_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'name' => 'name'
        ) //
    );

  return mica_client_commons_create_search_form($context, FALSE);
}

function mica_client_dataset_study_tables_table($dataset_type_dto) {
  $study_tables = array();
  if (!empty($dataset_type_dto->studyTables)) {
    foreach ($dataset_type_dto->studyTables as $study_table) {
      array_push($study_tables, $study_table);
    }
  }

  if (!empty($dataset_type_dto->studyTable)) {
    array_push($study_tables, $dataset_type_dto->studyTable);
  }

  $rows = mica_client_dataset_study_tables_rows($study_tables);
  $headers = mica_client_study_study_summaries_table_headers();
  array_splice($headers, 2, 0, array(t('Population'), t('Data collection Event')));

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

function mica_client_dataset_study_tables_rows($study_tables) {
  $rows = array();
  if (!empty($study_tables)) {
    foreach ($study_tables as $study_table) {
      $row = mica_client_study_study_summaries_table_row($study_table->studySummary);
      $population_name = $study_table->populationId;
      $dce_name = $study_table->dataCollectionEventId;
      foreach ($study_table->studySummary->populationSummaries as $population_summary) {
        if ($population_summary->id == $study_table->populationId) {
          $population_name = mica_client_commons_get_localized_field($population_summary, 'name');
          foreach ($population_summary->dataCollectionEventSummaries as $dce_summary) {
            if ($dce_summary->id == $study_table->dataCollectionEventId) {
              $dce_name = mica_client_commons_get_localized_field($dce_summary, 'name');
            }
          }
        }
      }
      array_splice($row, 2, 0, array($population_name, $dce_name));
      $rows[] = $row;
    }
  }
  return $rows;
}

function mica_client_dataset_study_variable_table($dataset_harmonizations_dto) {
  $rows = array();
  $headers = array(t('Variable'), t('Domains'));
  if (!empty($dataset_harmonizations_dto->variables)) {
    $total = $dataset_harmonizations_dto->total;
    $per_page = 10;
    pager_default_initialize($total, $per_page);

    foreach ($dataset_harmonizations_dto->variables as $variable) {
      $var_row = l($variable->name, 'mica/variable/' . $variable->id);
      $domains = _mica_client_variable_domains_list($variable);
      $rows[] = array($var_row, $domains);
    }

    return theme(
      'table',
      array(
        'header' => $headers,
        'rows' => $rows,
        'empty' => t('No harmonized variables found'),
        'sticky' => FALSE
      )
    ) . theme('pager');
  }

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
    $total = $dataset_harmonizations_dto->total;
    $per_page = 10;
    pager_default_initialize($total, $per_page);

    foreach ($dataset_harmonizations_dto->variableHarmonizations as $variable_harmonization) {
      $row = array(
        l($variable_harmonization->resolver->name, 'mica/variable/' . $variable_harmonization->resolver->id)
      );

      foreach ($study_ids as $study_id) {
        $found = FALSE;
        foreach ($variable_harmonization->datasetVariableSummaries as $variable_summary) {
//          $comments_harmonization = (_mica_client_variable_attributes_detail($variable_summary, 'comments', array(
//            'maelstrom',
//            'Mlstr_harmo'
//          )));
//
//          $script_harmonization = (_mica_client_variable_attributes_detail($variable_summary, 'script', array()));
//
//          dpm($variable_summary);
//        dpm($script_harmonization);
          if ($variable_summary->resolver->studyId == $study_id) {
            $status = strtolower(_mica_client_variable_attributes_detail($variable_summary, 'status', array(
              'maelstrom',
              'Mlstr_harmo'
            )));
            $harmonized_variable_id = $variable_harmonization->resolver->datasetId . ':' . $variable_harmonization->resolver->name . ':Harmonized:' . $study_id;
            if (empty($status)) {
              $row[] = l('-', 'mica/variable/' . $harmonized_variable_id);
            }
            elseif ($status == 'complete') {
              $row[] = l('<span data-toggle="tooltip" title="Completed" class="glyphicon glyphicon-ok alert-success" title="' . t('Complete') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                array('html' => TRUE));
            }
            elseif ($status == 'impossible') {
              $row[] = l('<span class="glyphicon glyphicon-remove alert-danger" title="' . t('Impossible') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                array('html' => TRUE));
            }
            elseif ($status == 'undetermined') {
              $row[] = l('<span class="glyphicon glyphicon-question-sign alert-warning" title="' . t('Undetermined') . '"></span>', 'mica/variable/' . $harmonized_variable_id,
                array('html' => TRUE));
            }
            else {
              $row[] = l('-', 'mica/variable/' . $harmonized_variable_id);
            }
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
  ) . theme('pager');

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
