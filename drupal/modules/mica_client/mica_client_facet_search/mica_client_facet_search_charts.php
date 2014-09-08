<?php
include_once('includes/mica_client_facet_search_resource_facet_conf.inc');

function mica_client_facet_search_get_facets_chart($data, $library = NULL, $id = NULL) {
  if ($library && $library_info = chart_get_library($library)) {
    $charts_info = array($library => $library_info);
  }
  else {
    $charts_info = charts_info();
  }

  foreach ($charts_info as $library => $chart_library_info) {
    $table['header'][] = array(
      'width' => (1 / count($charts_info) * 100) . '%',
      'data' => $chart_library_info['label'],
    );
  }
  $charts = array();

  foreach ($data as $facet) {
    if (!empty($facet->{'obiba.mica.TermsAggregationResultDto.terms'})) {
      $terms_title = array();
      $count_terms = array();
      $sorted_terms = mica_client_facet_search_group_terms($facet->{'obiba.mica.TermsAggregationResultDto.terms'}, $data['totalHits']);
      foreach ($sorted_terms as $term) {
        $terms_title[] = $term->key;
        $count_terms[] = $term->count;
      }
      $title_chart = mica_client_facet_search_get_title_chart($facet->aggregation);
      if (!empty($title_chart)) {
        $charts[] = mica_client_facet_search_pie_chart($terms_title, $count_terms, $title_chart);
      }
    }
  }
  return $charts;
}

function mica_client_facet_search_group_terms($terms, $total) {
  $temp_val = array();
  $temp_val_other = new stdClass();
  $Total_other = 0;

  foreach ($terms as $key => $row_term) {
    if (($total / $row_term->count < 60)) {
      $temp_val_obj = new stdClass();
      $temp_val_obj->key = $row_term->key;
      $temp_val_obj->count = $row_term->count;
      $temp_val[] = $temp_val_obj;
      $total_count[] = $row_term->count;
    }
    else {
      $temp_val_other->key = t('Others');
      $Total_other = $row_term->count + $Total_other;
      $temp_val_other->count = $Total_other;
    }
  }
  if (!empty($temp_val_other->count)) {
    $temp_val[] = $temp_val_other;
    $total_count[] = $temp_val_other->count;
  }

  array_multisort($total_count, SORT_DESC, $temp_val);
  return $temp_val;
}

function mica_client_facet_search_get_title_chart($aggregations = NULL) {
  foreach (mica_client_facet_search_resource_return_facets('mica_client_dataset') as $agg) {
    if ($aggregations == $agg['aggs']) {
      $title = explode('-', $agg['title']);
      return ucwords(drupal_strtolower($title[1]));
    }
  }
}

function mica_client_facet_search_pie_chart($labels, $data, $title) {
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'pie',
    '#width' => 250,
    '#height' => 175,
    '#title' => $title,
    '#title_font_size' => 13,
    '#chart_library' => 'highcharts',
    '#legend_position' => 'none',
    '#data_labels' => FALSE,
    '#legend' => FALSE,
    '#tooltips' => TRUE,
  );
  $chart['pie_data'] = array(
    '#type' => 'chart_data',
    '#title' => $title,
    '#labels' => $labels,
    '#data' => $data,
  );

  $example['chart'] = $chart;

  return $example;
}
