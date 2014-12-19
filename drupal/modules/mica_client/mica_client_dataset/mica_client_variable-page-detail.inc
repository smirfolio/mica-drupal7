<?php
include_once('includes/mica_client_dataset_resource.inc');
include_once('includes/mica_client_variable_statistics.inc');

function mica_client_variable_page_detail($variable_id) {
  $library_chart = mica_client_variable_load_chart_libraries();
  drupal_add_js(
    drupal_get_path('module', 'charts') .
    '/modules/charts_' . $library_chart .
    '/charts_' . $library_chart . '.js', 'file');
  if ($library_chart == 'google') {
    drupal_add_js('http://www.google.com/jsapi', 'file');
  }

  drupal_add_js(drupal_get_path('module', 'mica_client_dataset') . '/js/mica_client_variable_harmo_algo_datatable_init.js', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_dataset') . '/js/mica_client_dataset_get_ajax_variables.js', 'file');
  drupal_add_js(array('mica_client_variable' => array('library' => $library_chart)), 'setting');

  $url_param = explode('?', $_SERVER['REQUEST_URI']);
  $url_query = NULL;
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $url_query);
  }

  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable($variable_id);
  if ($variable->variableType == "Dataschema") {
    // $algos = mica_client_dataset_get_variable_algorithm($variable_id);
    $algos = TRUE;
  }
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
    'harmonization_table_legend' => theme('mica_client_dataset-harmonization-table-legend', array('clickable' => $variable->variableType != 'Harmonized')),
    'variable_dto' => $variable,
    'variable_harmonization_algorithms' => !empty($algos) ? $algos : NULL,
    'variable_harmonization' => mica_client_variable_get_harmonization($variable),
  ));
}

function mica_client_dataset_get_variable_algorithm($variable_id) {
  $algos = array();
  $variable_resource = new MicaDatasetResource();
  $harmonization_variables = $variable_resource->get_variable_harmonizations($variable_id);
  foreach ($harmonization_variables->datasetVariableSummaries as $harmonization_variable) {
    $variable_resolver = $harmonization_variable->resolver;
    $study_id = $variable_resolver->studyId;

    $variable_title = $variable_resolver->name . ' -- ' . $study_id;
    if (!empty($harmonization_variable->studyTable->name)) {
      $variable_title = $variable_title . ' (' . mica_client_commons_get_localized_field($harmonization_variable->studyTable, 'name') . ')';
    }
    $algorithm = _mica_client_variable_attributes_detail($harmonization_variable, 'algorithm', array(
      'maelstrom',
      'Mlstr_harmo'
    ));
    if (!empty($algorithm)) {
      $algos[$variable_title] =
        array(
          'var_id' => $variable_resolver->id,
          'var_detail' => mica_client_commons_markdown($algorithm)
        )//
      ;
    }
  }
  $themed_algo['algo'] = theme('mica_client_variable_harmonization_algorithm', array('variable_harmonization_algorithms' => $algos));
  drupal_json_output($themed_algo);
  // return  $themed_algo['algo'];
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

      $status = trim(strtolower(_mica_client_variable_attributes_detail($variable_harmonization, 'status', array(
        'maelstrom',
        'Mlstr_harmo'
      ))));

      if (empty($status)) {
        $status = '<span class="glyphicon glyphicon-question-sign alert-danger" title="' . t('No status') . '"></span>';
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
        $status = '<span class="glyphicon glyphicon-question-sign alert-danger" title="' . t('No status') . '"></span>';
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
        l($status, 'mica/variable/' . $harmonized_variable_id, array(
          'html' => TRUE,
          'query' => array(
            'title' => $variable_title
          )
        )),
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
  return array(
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
    $statistics = new VariableStatistics($variable, $variable_stat);
    $stat_tab['table'] = $statistics->as_table();
    $stat_tab['chart'] = $statistics->as_chart();
    return drupal_json_output($stat_tab);
  }
  return FALSE;
}

function mica_client_dataset_variable_get_ajax_statistics_test($variable_id = NULL) {
  $stat_tab = '';
  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable($variable_id);
  $variable_stat = $variable_resource->get_variable_aggregation($variable_id);
//  dpm($variable);
//  dpm($variable_stat);
  if (!empty($variable_stat)) {
    $statistics = new VariableStatistics($variable, $variable_stat);
    $stat_tab .= $statistics->as_table();
    $stat_tab .= $statistics->as_chart();
  }

  return $stat_tab;
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

function mica_client_variable_dataset_type($variable) {
  return $variable->variableType == 'Study' ? 'study-dataset' : 'harmonization-dataset';
}