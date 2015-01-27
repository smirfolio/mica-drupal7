<?php
include_once('includes/obiba_mica_search_resource_facet_conf.inc');

function obiba_mica_search_get_facets_chart($type = NULL, $data, $library = NULL, $id = NULL) {
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
        if (!empty($term->count)) {
          $terms_title[] = $term->key;
          $count_terms[] = $term->count;
        }
      }
      if (count($terms_title) > 1) {
        $title_chart = obiba_mica_search_get_title_chart($type, $facet->aggregation);
        if (!empty($title_chart)) {
          $charts[] = obiba_mica_search_pie_chart($terms_title, $count_terms, $title_chart);
        }
      }
    }
  }

  return $charts;
}

function obiba_mica_search_get_title_chart($type = NULL, $aggregations = NULL) {
  foreach (obiba_mica_search_resource_return_facets($type) as $agg) {
    if ($aggregations == $agg['aggs']) {
      $title = explode('-', $agg['title']);
      return ucwords(drupal_strtolower($title[1]));
    }
  }
}

function obiba_mica_search_vocabulary_chart($vocabulary_coverage) {
  if (empty($vocabulary_coverage->buckets)) {
    return obiba_mica_search_vocabulary_pie_chart($vocabulary_coverage);
  }
  return obiba_mica_search_vocabulary_bar_chart($vocabulary_coverage, TRUE);
}

function obiba_mica_search_vocabulary_pie_chart($vocabulary_coverage) {
  if (empty($vocabulary_coverage->hits)) {
    return '';
  }
  //dpm($vocabulary_coverage);

  $labels = array();
  $data = array();
  foreach ($vocabulary_coverage->terms as $term_coverage) {
    if (!empty($term_coverage->hits)) {
      $labels[] = obiba_mica_commons_get_localized_field($term_coverage->term, 'titles');
      $data[] = $term_coverage->hits;
    }
  }

  if (count($data) <= 1) {
    return '';
  }

  return obiba_mica_search_pie_chart($labels, $data, obiba_mica_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'), NULL, 400, 'bottom');
}

function obiba_mica_search_vocabulary_bar_chart($vocabulary_coverage, $with_buckets = FALSE) {
  if (empty($vocabulary_coverage->hits)) {
    return '';
  }
  //dpm($vocabulary_coverage);

  $labels = array();
  $data = array();
  if ($with_buckets) {
    $bucket_names = array();
    foreach ($vocabulary_coverage->buckets as $bucket) {
      $bucket_names[] = $bucket->value;
    }
    foreach ($vocabulary_coverage->terms as $term_coverage) {
      if (!empty($term_coverage->hits)) {
        $labels[] = obiba_mica_commons_get_localized_field($term_coverage->term, 'titles');
        foreach ($bucket_names as $bucket_name) {
          if (empty($data[$bucket_name])) {
            $data[$bucket_name] = array();
          }
          $found = FALSE;
          foreach ($term_coverage->buckets as $term_bucket) {
            if ($term_bucket->value == $bucket_name) {
              $found = TRUE;
              $data[$bucket_name][] = $term_bucket->hits;
              break;
            }
          }
          if (!$found) {
            $data[$bucket_name][] = 0;
          }
        }
      }
    }
  }
  else {
    foreach ($vocabulary_coverage->terms as $term_coverage) {
      if (!empty($term_coverage->hits)) {
        $labels[] = obiba_mica_commons_get_localized_field($term_coverage->term, 'titles');
        $data[] = $term_coverage->hits;
      }
    }
    $data = array(t('All') => $data);
  }

  if (!empty($data)) {
    return obiba_mica_search_stacked_column_chart($labels, $data, obiba_mica_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'), NULL, 400, 'none');
  }
  else {
    return FALSE;
  }
}

function obiba_mica_search_term_chart($term_coverage) {
  if (empty($term_coverage->hits) || empty($term_coverage->buckets)) {
    return '';
  }
  //dpm($term_coverage);

  $labels = array();
  $data = array();
  foreach ($term_coverage->buckets as $term_bucket) {
    if (!empty($term_bucket->hits)) {
      $labels[] = $term_bucket->value;
      $data[] = $term_bucket->hits;
    }
  }
  //return obiba_mica_search_pie_chart($labels, $data, '', 100, 100, 'none');
  return obiba_mica_search_mini_column_chart($labels, $data, '', 200, 50, 'none');
}

/**
 * Make a chart from taxonomy coverage.
 * @param $query
 * @param $bucket_filter bucket filter closure with 2 arguments: the bucket and the $bucket_filter_arg
 * @param null $bucket_filter_arg argument to be passed to the bucket filter closure
 * @return array
 */
function obiba_mica_search_query_charts($query, Callable $bucket_filter = NULL, $bucket_filter_arg = NULL, $default_dto_search = NULL) {
  $search_resources = new MicaSearchResource();
  $coverages = $search_resources->taxonomies_coverage($query, $default_dto_search);
  //dpm($coverages);
  $taxonomy_charts = array();

  if (!empty($coverages->taxonomies)) {
    foreach ($coverages->taxonomies as $taxonomy_coverage) {
      $labels = array();
      $data = array();
      foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) {
        if (!empty($vocabulary_coverage->count)) {
          $labels[] = obiba_mica_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles');
          if (!empty($vocabulary_coverage->buckets)) {
            foreach ($vocabulary_coverage->buckets as $bucket) {
              if (empty($bucket_filter) || $bucket_filter($bucket, $bucket_filter_arg)) {
                $data[$bucket->value][] = $bucket->count;
              }
            }
          }
          else {
            $data[t('Variables')][] = $vocabulary_coverage->count;
          }
        }
      }
      if (!empty($data)) {
        $taxonomy_charts[] = array(
          'taxonomy' => $taxonomy_coverage->taxonomy,
          'chart' => obiba_mica_search_stacked_column_chart($labels, $data, t('Number of variables'), 1000, 450, 'none')
        );
      }
    }
  }
  return $taxonomy_charts;
}

function obiba_mica_search_pie_chart($labels, $data, $title, $width = 250, $height = 175, $legend_position = 'none') {
  $chart_param = variable_get('charts_default_settings');
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'pie',
    '#colors' => obiba_mica_search_charts_colors(),
    '#width' => $width,
    '#height' => $height,
    '#title' => empty($title) ? ' ' : $title,
    '#chart_library' => $chart_param['library'],
    '#legend_position' => $legend_position,
    '#data_labels' => FALSE,
    '#legend' => $legend_position != 'none',
    '#tooltips' => TRUE,
  );
  $chart['pie_data'] = array(
    '#type' => 'chart_data',
    '#title' => empty($title) ? ' ' : $title,
    '#labels' => $labels,
    '#data' => $data,
  );

  return $chart;
}

function obiba_mica_search_mini_column_chart($labels, $data, $title, $width = 250, $height = 175, $legend_position = 'none') {
  $chart_param = variable_get('charts_default_settings');
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'column',
    '#colors' => obiba_mica_search_charts_colors(),
    '#width' => $width,
    '#height' => $height,
    '#title' => empty($title) ? ' ' : $title,
    '#legend_position' => $legend_position,
    '#legend' => $legend_position != 'none',
    '#chart_library' => $chart_param['library'],
  );
  $chart['counts'] = array(
    '#type' => 'chart_data',
    '#title' => t('Counts'),
    '#data' => $data,
  );
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $labels,
    '#labels_font_size' => '0px',
    '#labels_rotation' => 90,
    '#labels_color' => 'transparent',
    '#grid_line_color' => 'transparent',
    '#minor_grid_line_color' => 'transparent',
  );
  $chart['yaxis'] = array(
    '#type' => 'chart_yaxis',
    '#labels_color' => 'transparent',
    '#labels_font_size' => '0px',
    '#grid_line_color' => 'transparent',
  );
  return $chart;
}

function obiba_mica_search_stacked_column_chart($labels, $data, $title, $width = 250, $height = 175, $legend_position = 'none') {
  $chart_param = variable_get('charts_default_settings');
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'column',
    '#colors' => obiba_mica_search_charts_colors(),
    '#stacking' => TRUE,
    '#width' => $width,
    '#height' => $height,
    '#title' => empty($title) ? ' ' : $title,
    '#legend_position' => $legend_position,
    '#legend' => $legend_position != 'none',
    '#chart_library' => $chart_param['library'],
  );
  foreach ($data as $key => $datum) {
    $chart[$key] = array(
      '#type' => 'chart_data',
      '#title' => ' ' . $key, // google chart has a bug when title is a number
      '#data' => $datum,
    );
  }
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $labels,
    //'#labels_rotation' => 90,
  );
  return $chart;
}

function obiba_mica_search_charts_colors() {
  // http://paletton.com/#uid=63G0A0kgXCa57FeaZFGlFCCqIHv
  return array(
    '#6285BC',
    '#59BE9A',
    '#7D66C1',
    '#FFCE78',
    '#88A0C5',
    '#83C7AF',
    '#9C8CCA',
    '#FFDFA8',
    '#4976BD',
    '#3EBF92',
    '#6B4EC2',
    '#FFC052',
    '#A8B3C4',
    '#A6C6BB',
    '#B3ACC9',
    '#FFF0D6',
    '#316CCA',
    '#22CC90',
    '#5B35CE',
    '#FFB22A'
  );
}

function obiba_mica_search_charts_gray_colors() {
  return array(
    '#111',
    '#333',
    '#555',
    '#777',
    '#999',
    '#bbb',
    '#ddd',
    '#222',
    '#444',
    '#666',
    '#888',
    '#aaa',
    '#ccc',
    '#eee',
  );
}
