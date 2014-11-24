<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_variable_page_detail($variable_id) {
  $library_chart = mica_client_variable_load_chart_libraries();
  drupal_add_js(
    drupal_get_path('module', 'charts') .
    '/modules/charts_' . $library_chart .
    '/charts_' . $library_chart . '.js', 'file');
  if ($library_chart == 'google') {
    drupal_add_js('http://www.google.com/jsapi', 'file');
  }

  drupal_add_js(drupal_get_path('module', 'mica_client_dataset') . '/js/mica_client_dataset_get_ajax_variables.js', 'file');
  drupal_add_js(array('mica_client_variable' => array('library' => $library_chart)), 'setting');

  $url_param = explode('?', $_SERVER['REQUEST_URI']);
  $url_query = NULL;
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $url_query);
  }

  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable($variable_id);
  if (empty($variable)) {
    drupal_set_title(t('Variable not found'));
    return '';
  }
  $variable->label = _mica_client_variable_attributes_detail($variable, 'label');
  $variable->description = _mica_client_variable_attributes_detail($variable, 'description');
  $variable->comment = _mica_client_variable_attributes_detail($variable, 'comment');

  $title = $variable->name;
  if ($variable->variableType == 'Harmonized') {
    if (!empty($url_query['title'])) {
      $title = $url_query['title'];
    }
    else {
      $title .= ' -- ' . (mica_client_commons_get_localized_field($variable->studySummaries[0], 'acronym'));
    }
  }

  drupal_set_title($title);

  $dataset_type = $variable->variableType == 'Study' ? 'study-dataset' : 'harmonization-dataset';

  drupal_set_breadcrumb(array(
    l('Home', '<front>'),
    l(t('Datasets'), 'mica/datasets'),
    l(($dataset_type == 'study-dataset' ? t('Study Datasets') : t('Harmonization Datasets')), 'mica/datasets/' . $dataset_type . 's'),
    l(mica_client_commons_get_localized_field($variable, 'datasetName'), 'mica/' . mica_client_variable_dataset_type($variable)
      . '/' . $variable->datasetId)
  ));

  _mica_client_dataset_remove_harmonization_taxonomy($variable);

  return theme('mica_client_variable-detail', array(
    'harmonization_table_legend' => theme('mica_client_dataset-harmonization-table-legend', array()),
    'variable_dto' => $variable,
    'variable_harmonization' => mica_client_variable_get_harmonization($variable),
  ));
}

function _mica_client_dataset_remove_harmonization_taxonomy($variable) {

  if (!empty($variable->termAttributes)) {
    $variable->termAttributes = array_filter($variable->termAttributes, function ($termAttribute) {
      return $termAttribute->taxonomy->name !== 'Mlstr_harmo';
    });
  }

}

function mica_client_variable_load_chart_libraries() {
  if (module_exists('charts')) {
    $chart_param = variable_get('charts_default_settings');
    if (!empty($chart_param)) {
      $charts_lib = libraries_load($chart_param['library']);
      if (!empty($charts_lib)) {
        foreach ($charts_lib as $folder) {
          if (!empty($folder['js'])) {
            foreach ($folder as $key_file => $param_files) {
              if ($key_file == 'js') {
                drupal_add_js($charts_lib['library path'] . '/' . key($param_files));
              }
            }
          }
        }
        return $chart_param['library'];
      }
    }
    return 'google';
  }
  return 'google';
}

function mica_client_variable_prepare_prettify() {
  static $paths = array();
  if (mica_client_commons_is_bootstrap_based_theme()) {
    $dir = drupal_get_path('theme', mica_client_commons_get_current_theme());
    $paths['css'] = $dir . '/css/prettify.css';
    $paths['js'] = $dir . '/js/prettify.js';
  }
  if (isset($paths['css'])) {
    drupal_add_css($paths['css']);
  }
  else {
    throw new Exception('prettify.css library not found!');
  }

  if (isset($paths['js'])) {
    drupal_add_js($paths['js']);
  }
  else {
    throw new Exception('prettify.js library not found!');
  }
  drupal_add_js(drupal_get_path('module', 'mica_client_dataset') . '/js/mica_client_prettify.js', 'file');
}

function mica_client_variable_get_harmonizations($variable) {
  mica_client_variable_prepare_prettify();
  $rows = array();
  $variable_resource = new MicaDatasetResource();

  $variable_harmonizations = $variable_resource->get_variable_harmonizations($variable->id);

  if (!empty($variable_harmonizations->datasetVariableSummaries)) {
    foreach ($variable_harmonizations->datasetVariableSummaries as $variable_harmonization) {
      $variable_resolver = $variable_harmonization->resolver;
      $harmonized_variable_id = $variable_resolver->id;
      $study_id = $variable_resolver->studyId;
      $study_summary = _mica_client_variable_study_summary($variable, $study_id);
      $study_acronym = mica_client_commons_get_localized_field($study_summary, 'acronym');
      $variable_title = $variable->name . ' -- ' . $study_acronym;
      if (!empty($variable_harmonization->studyTable->name)) {
        $variable_title = $variable_title . ' (' . mica_client_commons_get_localized_field($variable_harmonization->studyTable, 'name') . ')';
      }

      $status = strtolower(_mica_client_variable_attributes_detail($variable_harmonization, 'status', array(
        'maelstrom',
        'Mlstr_harmo'
      )));

      if (empty($status)) {
        $status = '-';
      }
      elseif ($status == 'complete') {
        $status = '<span class="glyphicon glyphicon-ok alert-success" title="' . t('Complete') . '"></span>';
      }
      elseif ($status == 'impossible') {
        $status = '<span class="glyphicon glyphicon-remove alert-danger" title="' . t('Impossible') . '"></span>';
      }
      elseif ($status == 'undetermined') {
        $status = '<span class="glyphicon glyphicon-question-sign alert-warning" title="' . t('Undetermined') . '"></span>';
      }
      else {
        $status = '-';
      }

      $rows[] = array(
        '<p>' .
        l($variable_title, 'mica/variable/' . $harmonized_variable_id, array(
          'query' => array(
            'title' => $variable_title
          )
        )) . '</p><p class="help-block">' . mica_client_commons_get_localized_field($variable_harmonization->studyTable, 'description') . '</p>',
        l($study_acronym, 'mica/study/' . $study_id),
        mica_client_dataset_get_dce_name_from_dataset($variable_harmonization->studyTable, $study_summary),
        //$variable_harmonization->studyTable->populationId . ':' . $variable_harmonization->studyTable->dataCollectionEventId,
        l($status, 'mica/variable/' . $harmonized_variable_id, array('html' => TRUE)),
        _mica_client_variable_html_truncated(
          _mica_client_variable_attributes_detail($variable_harmonization, 'comment', array(
            'maelstrom',
            'Mlstr_harmo'
          )), t('comment'), 200, FALSE),
      );
    }
  }

  if (!empty($rows)) {
    $headers = array(t('Harmonized Variable'), t('Study'), t('Data Collection Event'), t('Status'), t('Comment'));
    return theme('table', array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No variable found'),
      'sticky' => FALSE,
      'attributes' => array('id' => 'variables_overview')
    ));
  }

}

function mica_client_variable_get_harmonization($harmonized_variable) {
  $rows = array();
  if ($harmonized_variable->variableType != 'Harmonized') {
    ;
  }

  $rows = array(
    'status' => _mica_client_variable_attributes_detail($harmonized_variable, 'status', array(
      'maelstrom',
      'Mlstr_harmo'
    )),
    'comment' => _mica_client_variable_attributes_detail($harmonized_variable, 'comment', array(
      'maelstrom',
      'Mlstr_harmo'
    )),
    'algorithm' => mica_client_commons_markdown(_mica_client_variable_attributes_detail($harmonized_variable, 'algorithm', array(
      'maelstrom',
      'Mlstr_harmo'
    ))),
    'script' => _mica_client_variable_attributes_detail($harmonized_variable, 'script'),
  );

  return $rows;
}

function _mica_client_variable_html_truncated($text, $label, $size = 200, $is_code = FALSE, $pre_class = '') {
  $htmlTruncate = '';
  if (!empty($text)) {

    // split to respect line size
    if ($is_code) {
      $htmlTruncate = "<pre class='prettyprint $pre_class'>";
      // split at ).
      $lines = explode(").", $text);
      $text = implode(")\n.", $lines);
    }
    else {
      $lines = str_split($text, 60);
      $text = implode("\n", $lines);
    }

    if (strlen($text) > $size) {
      $htmlTruncate .= check_markup(truncate_utf8($text, $size, FALSE));

      if ($is_code) {
        $htmlTruncate .= "</pre>";
      }

      $htmlTruncate .= "[" . $label . " " . t("truncated") . "]";
    }
    else {
      $htmlTruncate .= check_markup($text);

      if ($is_code) {
        $htmlTruncate .= "</pre>";
      }
    }
  }
  else {
    $htmlTruncate = '-';
  }
  return $htmlTruncate;
}

function mica_client_variable_get_categories($categories = NULL) {
  $rows = array();
  if (!empty($categories)) {
    foreach ($categories as $category) {
      $rows[] = array(
        $category->name,
        _mica_client_variable_attributes_detail($category, 'label'),
        $category->missing ? '<span class="glyphicon glyphicon-ok"></span>' : NULL
      );
    }
    return theme(
      'table',
      array(
        'header' => array(t('Name'), t('Label'), t('Missing')),
        'rows' => $rows,
        'empty' => t('No category found'),
        'sticky' => FALSE,
      )
    );
  }

  return FALSE;
}


function mica_client_dataset_variable_get_ajax_statistics($variable_id = NULL) {
  $stat_tab = FALSE;
  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable($variable_id);
  $variable_stat = $variable_resource->get_variable_aggregation($variable_id);
  if (!empty($variable_stat)) {
    $stat_tab['table'] = _mica_client_variable_table_stat($variable, $variable_stat);
    $stat_tab['chart'] = _mica_client_variable_chart_stat($variable, $variable_stat);
    return drupal_json_output($stat_tab);
  }
  return FALSE;
}

function mica_client_dataset_variable_get_ajax_statistics_test($variable_id = NULL) {
  $stat_tab = '';
  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable($variable_id);
  $variable_stat = $variable_resource->get_variable_aggregation($variable_id);
  dpm($variable_stat);
  if (!empty($variable_stat)) {
    $stat_tab .= _mica_client_variable_table_stat($variable, $variable_stat);
    $stat_tab .= _mica_client_variable_chart_stat($variable, $variable_stat);
  }

  return $stat_tab;
}


function _mica_client_variable_chart_stat($variable, $variable_stat) {
  switch ($variable->nature) {
    case 'CONTINUOUS':
      break;
    case 'CATEGORICAL':
      $aggregations = array();
      if (!empty($variable_stat->aggregations)) {
        $aggregations = $variable_stat->aggregations;
      } else {
        array_push($aggregations, $variable_stat);
      }

      $labels = array();
      $data = array();
      foreach ($variable->categories as $category) {
        $label = _mica_client_variable_attributes_detail($category, 'label');
        if (empty($label)) {
          $label = $category->name;
        } else {
          $label = $category->name . ' (' . $label . ')';
        }
        $labels[] = $label;
        foreach ($aggregations as $aggregation) {
          if (!empty($aggregation->frequencies)) {
            $study_id = $aggregation->studyTable->studyId;
            $header = _mica_client_variable_study_acronym($variable, $study_id);
            if (!empty($aggregation->studyTable->name)) {
              $header = $header . '(' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name') . ')';
            }
            foreach ($aggregation->frequencies as $frequency) {
              if ($frequency->term == $category->name) {
                $data[$header][] = $frequency->count;
                break;
              }
            }
          }
        }
      }
      if (!empty($data)) {
        $to_render = mica_client_facet_search_stacked_column_chart($labels, $data, NULL, NULL, 400, 'none');
        return render($to_render);
      } else {
        return FALSE;
      }
  }
  return FALSE;
}

function _mica_client_variable_table_stat($variable, $variable_stat) {
  switch ($variable->nature) {
    case 'CONTINUOUS':
      return _mica_client_variable_table_stat_continuous($variable, $variable_stat);
    case 'CATEGORICAL':
      return _mica_client_variable_table_stat_categorical($variable, $variable_stat);
  }
  return 'Statistics not supported (yet) for this variable nature: ' . $variable->nature;
}

function _mica_client_variable_table_stat_continuous($variable, $variable_stat) {
  $rows = array();
  $aggregations = array();

  if ($variable->variableType == 'Dataschema') {
    if (!empty($variable_stat->aggregations)) {
      $aggregations = $variable_stat->aggregations;
    }
  } else {
    array_push($aggregations, $variable_stat);
  }

  foreach ($aggregations as $aggregation) {
    $row = array();
    $study_id = $aggregation->studyTable->studyId;
    $header = l(_mica_client_variable_study_acronym($variable, $study_id), 'mica/study/' . $study_id);
    if (!empty($aggregation->studyTable->name)) {
      $header = $header . ' ' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name');
    }
    $row[] = $header;
    $rows[] = array_merge($row, _mica_client_variable_table_stat_continuous_statistics_to_row($aggregation));
  }

  // combined statistics
  if ($variable->variableType == 'Dataschema') {
    $row = array(
      array(
        'data' => '<strong>' . t('All') . '</strong>',
        'class' => array('active')
      )
    );
    $rows[] = array_merge($row, _mica_client_variable_table_stat_continuous_statistics_to_row($variable_stat));
  }

  $headers = array();
  if ($variable->variableType == 'Dataschema') {
    $headers = array(t('Study'));
  }
  array_push($headers, t('Min'), t('Max'), t('Mean'), t('Std. Dev'), t('Count'));
  return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No statistics available')));
}

function _mica_client_variable_table_stat_continuous_statistics_to_row($aggregation) {
  if (!empty($aggregation->statistics)) {
    $statistics = $aggregation->statistics;
    return array(
      !empty($statistics->min) ? round($statistics->min, 3) : '-',
      !empty($statistics->max) ? round($statistics->max, 3) : '-',
      !empty($statistics->mean) ? round($statistics->mean, 3) : '-',
      !empty($statistics->stdDeviation) ? round($statistics->stdDeviation, 3) : '-',
      $statistics->count
    );
  } else {
    return array(
      '-',
      '-',
      '-',
      '-',
      0
    );
  }
}

function _mica_client_variable_table_stat_categorical($variable, $variable_stat) {
  $headers = array('Value');
  $rows = array();
  $aggregations = array();

  // headers
  if ($variable->variableType == 'Dataschema') {
    if (!empty($variable_stat->aggregations)) {
      $aggregations = $variable_stat->aggregations;
      foreach ($aggregations as $aggregation) {
        $study_id = $aggregation->studyTable->studyId;
        $header = l(_mica_client_variable_study_acronym($variable, $study_id), 'mica/study/' . $study_id);
        if (!empty($aggregation->studyTable->name)) {
          $header = $header . ' ' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name');
        }
        $headers[] = $header;
      }
      if (count($aggregations)>1) {
        $headers[] = t('All');
      }
    }
  }
  else {
    array_push($headers, t('Frequency'));
    array_push($aggregations, $variable_stat);
  }

  // total of non-missing categories (should be done server side!)
  $total_non_missings = array();
  foreach ($aggregations as $aggregation) {
    $total_non_missing = 0;
    if (!empty($aggregation->frequencies)) {
      foreach ($aggregation->frequencies as $frequency) {
        foreach ($variable->categories as $category) {
          if (!$category->missing) {
            $category_name = $category->name;
            if ($frequency->term == $category_name) {
              $total_non_missing += $frequency->count;
              break;
            }
          }
        }
      }
    }
    $total_non_missings[] = $total_non_missing;
  }

  // counts per category
  foreach ($variable->categories as $category) {
    $category_name = $category->name;
    $category_label = _mica_client_variable_attributes_detail($category, 'label');
    $missing = $category->missing;
    $row = array(array(
      'data' => $category->name,
      'title' => $category_label,
    ));
    $count_all = 0;
    $total_non_missing_all = 0;
    for ($i = 0; $i < count($aggregations); $i++) {
      $aggregation = $aggregations[$i];
      $total_non_missing = $total_non_missings[$i];
      $count = 0;
      if (!empty($aggregation->frequencies)) {
        foreach ($aggregation->frequencies as $frequency) {
          if ($frequency->term == $category_name) {
            $count = $frequency->count;
            $count_all += $count;
            $total_non_missing_all += $total_non_missing;
            if (!$missing && $total_non_missing > 0) {
              $percent = round(($count / $total_non_missing) * 100, 1);
              $count .= '<p class="help-inline">(' . $percent . '%)</p>';
            }
            break;
          }
        }
      }
      $row[] = $count;
    }
    if (count($aggregations) > 1) {
      if ($total_non_missing_all > 0) {
        $percent = round(($count_all / $total_non_missing_all) * 100, 1);
        $count_all .= '<p class="help-inline">(' . $percent . '%)</p>';
      }
      $row[] = $count_all;
    }
    $rows[] = $row;
  }

  // total non missing
  $row = array('<strong>' . t('Total non missings') . '</strong>');
  $total_non_missing_all = 0;
  $total_all = 0;
  for ($i = 0; $i < count($aggregations); $i++) {
    $aggregation = $aggregations[$i];
    $total_non_missing = $total_non_missings[$i];
    $total_non_missing_all += $total_non_missing;
    $total_all += $aggregation->total;
    if ($total_non_missing > 0) {
      $percent = round(($aggregation->total / $total_non_missing) * 100, 1);
      $total_non_missing .= '<p class="help-inline">(' . $percent . '%)</p>';
    }
    $row[] = $total_non_missing;
  }
  if (count($aggregations) > 1) {
    if ($total_all > 0) {
      $percent = round(($total_all / $total_non_missing_all) * 100, 1);
      $total_non_missing_all .= '<p class="help-inline">(' . $percent . '%)</p>';
    }
    $row[] = $total_non_missing_all;
  }
  $rows[] = $row;

  // grand total
  $row = array(
    array(
      'data' => '<strong>' . t('Total') . '</strong>',
      'class' => array('active')
    )
  );
  $total_all = 0;
  foreach ($aggregations as $aggregation) {
    $row[] = array(
      'data' => $aggregation->total,
      'class' => array('active')
    );
    $total_all += $aggregation->total;
  }
  if (count($aggregations) > 1) {
    $row[] = array(
      'data' => $total_all,
      'class' => array('active')
    );
  }
  $rows[] = $row;

  return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No statistics available')));
}

/**
 * Get the study summary found in the variable. If not found, fetch the study summary directly.
 * @param $variable
 * @param $study_id
 * @return mixed
 */
function _mica_client_variable_study_summary($variable, $study_id) {
  foreach ($variable->studySummaries as $study) {
    if ($study->id == $study_id) {
      return $study;
    }
  }
  // not found in the dto, then fetch it
  $study_resource = new MicaStudyResource();
  return $study_resource->study($study_id);
}

/**
 * Get the study acronym from the study summary found in the variable. If not found, fetch the
 * study summary directly.
 * @param $variable
 * @param $study_id
 * @return mixed
 */
function _mica_client_variable_study_acronym($variable, $study_id) {
  return mica_client_commons_get_localized_field(_mica_client_variable_study_summary($variable, $study_id), 'acronym');
}

function _mica_client_variable_rebuild_stat($variable_stat, $variable) {
  $stats = array();
  foreach ($variable->studyIds as $key_study => $study_id) {
    foreach ($variable_stat as $key_stud => $stat) {
      if ($key_stud == $key_study) {
        $stats[$study_id]['_all'] = $stat->totalHits;
        foreach ($stat->facets[0]->frequencies as $frequency) {
          $stats[$study_id][$frequency->term] = $frequency->count;
        }
      }
    }
  }
  return $stats;
}

function mica_client_variable_dataset_type($variable) {
  return $variable->variableType == 'Study' ? 'study-dataset' : 'harmonization-dataset';
}