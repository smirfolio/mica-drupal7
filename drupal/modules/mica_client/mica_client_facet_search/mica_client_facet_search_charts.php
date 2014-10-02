<?php
include_once('includes/mica_client_facet_search_resource_facet_conf.inc');

function mica_client_facet_search_get_facets_chart($type = NULL, $data, $library = NULL, $id = NULL) {
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

      foreach ($facet->{'obiba.mica.TermsAggregationResultDto.terms'} as $term) {
        $terms_title[] = $term->key;
        $count_terms[] = $term->count;
      }
      $title_chart = mica_client_facet_search_get_title_chart($type, $facet->aggregation);
      if (!empty($title_chart)) {
        $charts[] = mica_client_facet_search_pie_chart($terms_title, $count_terms, $title_chart);
      }
    }
  }
  return $charts;
}

function mica_client_facet_search_get_title_chart($type = NULL, $aggregations = NULL) {
  foreach (mica_client_facet_search_resource_return_facets($type) as $agg) {
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
