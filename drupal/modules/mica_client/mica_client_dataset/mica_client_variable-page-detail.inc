<?php
include_once('includes/mica_client_dataset_resource.inc');

function mica_client_variable_page_detail($id_variable, $resource_variable) {
  drupal_add_js(drupal_get_path('module', 'mica_client_dataset') . '/js/mica_client_dataset_get_ajax_variables.js', 'file');
  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable('variable', $id_variable);
  $variable->label = _mica_client_variable_attributes_detail($variable, 'label');
  $variable->description = _mica_client_variable_attributes_detail($variable, 'description');
  $variable->comment = _mica_client_variable_attributes_detail($variable, 'comment');
  $variable->categoriestab = mica_client_variable_get_categories($variable->categories);
  $variable->harmonizationtab = mica_client_variable_get_harmonizations($variable);
  drupal_set_title($variable->name);
  return theme('mica_client_variable-detail', array('variable_dto' => $variable));
}

function mica_client_variable_prepare_prettify() {
  static $paths = array();
  if (mica_client_commons_is_bootstrap_based_theme()) {
    $dir = drupal_get_path('theme', 'micado_bootstrap');
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
  foreach ($variable->studyIds as $study_id) {
    $id_variable_resource = $variable->datasetId . ':' . $variable->name . ':Harmonized:' . $study_id;
    $harmonized_variable = $variable_resource->get_variable('variable', $id_variable_resource);
    if (_mica_client_variable_attributes_detail($harmonized_variable, 'status') ||
      _mica_client_variable_attributes_detail($harmonized_variable, 'comment') ||
      _mica_client_variable_attributes_detail($harmonized_variable, 'script')
    ) {
      $rows[] = array(
        _mica_client_variable_acronym_study($study_id),
        _mica_client_variable_attributes_detail($harmonized_variable, 'status'),
        _mica_client_variable_html_truncated(
          _mica_client_variable_attributes_detail($harmonized_variable, 'comment'), t('comment'), 200, FALSE),
        _mica_client_variable_html_truncated(
          _mica_client_variable_attributes_detail($harmonized_variable, 'script'), t('script'), 100, TRUE)
      );

    }
  }
  if (!empty($rows)) {
    $headers = array(t('study'), t('Status'), t('Comment'), t('Script'));
    return theme('table', array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No data found'),
      'sticky' => FALSE,
      'attributes' => array('id' => 'variables_overview')
    ));
  }

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
  return $htmlTruncate;
}

function mica_client_variable_get_categories($categories = NULL) {
  $rows = array();
  if (!empty($categories)) {
    foreach ($categories as $category) {
      $rows[] = array(
        $category->name,
        _mica_client_variable_attributes_detail($category, 'label'),
        $category->missing
      );
    }
    return theme(
      'table',
      array(
        'header' => array(t('Name'), t('Label'), t('Missing')),
        'rows' => $rows,
        'empty' => t('No data found'),
        'sticky' => FALSE,
        'attributes' => array('id' => 'variables_overview')
      )
    );
  }

  return FALSE;
}

function mica_client_variable_get_stat_view_type($variable) {
  $is_categorical = FALSE;
  foreach ($variable->categories as $category) {
    if ($category->missing == FALSE) {
      $is_categorical = TRUE;
      break;
    }
  }
  $type = $variable->valueType;

  if ($is_categorical) {
    return 'facet';
  }
  if ($type == 'integer' || $type == 'decimal') {
    return 'summary';
  }
  return 'TodoTerm';
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

function _mica_client_variable_attributes_detail($variable, $field) {
  if (!empty($variable->attributes)) {
    foreach ($variable->attributes as $attribute) {
      if (!empty($attribute->name) && $attribute->name == $field) {
        return mica_client_commons_get_localized_field($attribute, 'values');
      }
    }
  }
  return NULL;
}

function mica_client_dataset_variable_get_ajax_statistics($id_variable = NULL) {
  $variable_resource = new MicaDatasetResource();
  $variable = $variable_resource->get_variable('variable', $id_variable);
  $statistic_view_type = mica_client_variable_get_stat_view_type($variable);
  $variable_stat = $variable_resource->get_variable('variable', $id_variable, $statistic_view_type);
  if (!empty($variable_stat)) {
    $callback_stats = 'mica_client_variable_table_stat_' . $statistic_view_type;
    $stat_tab = $callback_stats($variable, $variable_stat);
  }
  print $stat_tab;

}

function mica_client_variable_table_stat_summary($variable, $variable_stat) {
  $rows = array();
  $math_dto = 'Math.ContinuousSummaryDto.continuous';
  foreach ($variable->studyIds as $key_stud => $stat) {
    $rows[] = array(
      _mica_client_variable_acronym_study($stat),
      !empty($variable_stat[$key_stud]->{$math_dto}->summary->min) ?
        round($variable_stat[$key_stud]->{$math_dto}->summary->min, 3) : 'inf',
      !empty($variable_stat[$key_stud]->{$math_dto}->summary->max) ?
        round($variable_stat[$key_stud]->{$math_dto}->summary->max, 3) : 'inf',
      !empty($variable_stat[$key_stud]->{$math_dto}->summary->mean) ?
        round($variable_stat[$key_stud]->{$math_dto}->summary->mean, 3) : 'inf',
      !empty($variable_stat[$key_stud]->{$math_dto}->summary->stdDev) ?
        round($variable_stat[$key_stud]->{$math_dto}->summary->stdDev, 3) : 'nan',
      $variable_stat[$key_stud]->{$math_dto}->summary->n
    );
  }
  $headers = array('Study', 'Min', 'Max', 'Mean', 'Std. Dev', 'Count');
  return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No studies available')));
}

function mica_client_variable_table_stat_facet($variable, $variable_stat) {
  $stats = _mica_client_variable_rebuild_stat($variable_stat, $variable);
  $headers = array('Value');
  foreach ($stats as $study_id => $stat) {
    $headers[] = _mica_client_variable_acronym_study($study_id);
  }
  $rows = array();
  // Get total of non-missing categories
  $totals = array();
  foreach ($variable->categories as $category) {
    if (!$category->missing) {
      $category_name = $category->name;
      foreach ($stats as $study_id => $stat) {
        $s = isset($stat[$category_name]) ? $stat[$category_name] : 0;
        $totals[$study_id] = isset($totals[$study_id]) ? $totals[$study_id] + $s : $s;
      }
    }
  }

  foreach ($variable->categories as $category) {
    $category_name = $category->name;
    $category_label = _mica_client_variable_attributes_detail($category, 'label');;
    $missing = $category->missing;
    $row = array($category_label);
    foreach ($stats as $study_id => $stat) {
      if (!$missing && isset($stat[$category_name]) && $totals[$study_id] > 0) {
        $percent = round(($stat[$category_name] / $totals[$study_id]) * 100, 1);
        $row[] = isset($stat[$category_name]) ? $stat[$category_name] . '<br>(' . $percent . '%)' : 0;
      }
      else {
        $row[] = isset($stat[$category_name]) ? $stat[$category_name] : 0;
      }
    }
    $rows[] = $row;
  }
  $row = array(
    array(
      'data' => t('All'),
      'class' => array('active')
    )
  );
  foreach ($stats as $study_id => $stat) {
    $row[] = array(
      'data' => isset($stat['_all']) ? $stat['_all'] : 0,
      'class' => array('active')
    );
  }
  $rows[] = $row;
  return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No studies available')));

}


function _mica_client_variable_acronym_study($study_id) {
  $study_resourc = new MicaStudyResource();
  $study = $study_resourc->study($study_id);
  return mica_client_commons_get_localized_field($study, 'acronym');
}

function _mica_client_variable_rebuild_stat($variable_stat, $variable) {
  $stats = array();
  foreach ($variable->studyIds as $key_study => $study_id) {
    foreach ($variable_stat as $key_stud => $stat) {
      if ($key_stud == $key_study) {
        $stats[$study_id]['_all'] = $stat->totalHits;
        foreach ($stat->facets[0]->frequencies as $key_attrib => $frequency) {
          $stats[$study_id][$key_attrib] = $frequency->count;
        }
      }
    }
  }
  return $stats;
}


//function mica_client_dataset_get_variables($resources, $id_dataset) {
//
//  $row_variablas = array();
//  $dataset_resource = new MicaDatasetResource();
//  $variables = $dataset_resource->get_dataset_varaibles($resources, $id_dataset);
//
//  foreach ($variables->getVariablesList() as $key_varable => $list) {
//    // dpm($list);
//    $row_variablas[$key_varable] = array(
//      'name' => l($list->name, 'mica/study/' . mica_client_commons_to_slug($list->name) . '/' . $list->id),
//      'label' => mica_client_commons_get_localized_field($list->getAttributes(0), 'values'),
//      'dataset' => mica_client_commons_get_localized_field($list, 'datasetName'),
//    );
//  }
//  $per_page = $dataset_resource::SIZE_RESPONSE;
//  pager_default_initialize($variables->total, $per_page);
//  // dpm( theme('pager', array('quantity' => $variables->total)));
//  $var_tab = theme('table',
//      array(
//        'header' => array(t('Name'), t('Label'), t('Dataset')),
//        'rows' => $row_variablas,
//        'empty' => t('No data found'),
//        'sticky' => FALSE,
//        'attributes' => array('id' => 'variables_overview')
//      )
//    ) . theme('pager', array('quantity' => 5, 'tags' => array('<<', '<', '', '>', '>>')));
//  return theme('mica_client_datasets-tables', array('tab_var' => $var_tab, 'title_section' => t('Variables')));
//}
