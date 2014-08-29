<?php

function mica_client_facet_search_resource_return_facets($dto_type = NULL) {
  $path_module = drupal_get_path('module', 'mica_client_facet_search');
  switch ($dto_type) {
    case 'mica_client_dataset':
      $data = file_get_contents($path_module . '/includes/mica_client_facet_search_json_variable_facet.json');
      $facets = drupal_json_decode($data);
      return $facets;
    case 'mica_client_study' :
      $data = file_get_contents($path_module . '/includes/mica_client_facet_search_json_study_facet.json');
      $facets = drupal_json_decode($data);
      return $facets;
    default :
      $data = file_get_contents($path_module . '/includes/mica_client_facet_search_json_variable_facet.json');
      $facets = drupal_json_decode($data);
      return $facets;
  }

}

function mica_client_facet_search_get_dto_facet_aggs($tab_block, $type) {
  foreach ($_SESSION[$type]['aggregations'] as $key_tab => $facet) {
    if (is_int($key_tab)) {
      if ($tab_block == 'search-' . $facet->aggregation) {
        if (!empty($facet->{'obiba.mica.TermsAggregationResultDto.terms'})) {
          $facet_build[$tab_block][$facet->aggregation]['term'] = $facet->{'obiba.mica.TermsAggregationResultDto.terms'};
        }
        elseif (!empty($facet->{'obiba.mica.StatsAggregationResultDto.stats'})) {
          $facet_build[$tab_block][$facet->aggregation]['range']['count'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->count;
          $facet_build[$tab_block][$facet->aggregation]['range']['min'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->min;
          $facet_build[$tab_block][$facet->aggregation]['range']['max'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->max;

        }
        else {
          $facet_build[$tab_block][$facet->aggregation] = NULL;
        }
        return $facet_build[$tab_block];
      }
    }
  }
}

function mica_client_facet_search_precess_block_theme($block_delta, $type, $relationship = NULL) {
  $items = array();
  $agregation_facet = NULL;
  $relationship_string = !empty($relationship) ? $relationship . ':' : NULL;
  if (!empty($block_delta)) {
    //  dpm(mica_client_commons_get_dto_facet_aggs($block_delta, $type));
    $facet_pars = mica_client_facet_search_get_dto_facet_aggs($block_delta, $type);
    if (!empty($facet_pars)) {
      $agregation_facet = key($facet_pars);
      $terms_aggregations = current($facet_pars);
      if (!empty($terms_aggregations) && !empty($terms_aggregations['term'])) {
        $items = mica_client_facet_search_get_checkbox_term_field($terms_aggregations['term'], $relationship_string, $agregation_facet);
      }
      if (!empty($terms_aggregations) && !empty($terms_aggregations['range'])) {
        $items = mica_client_facet_search_get_range_field($terms_aggregations['range'], $relationship_string, $agregation_facet);
      }
    }
  }
  return theme('mica_client_facet_search_block_search', array('items' => $items, 'formId' => $agregation_facet));
}

function mica_client_facet_search_get_checkbox_term_field($fields_terms, $relationship_string, $agregation_facet) {
  $color = array(
    1 => "#2a85a0",
    2 => "#20E4E4",
    3 => "#942a25",
    4 => "#e45822",
    5 => "#ffc40d",
    6 => "#e4dd95",
    7 => "#004000",
    8 => "#008000",
    9 => "#550000",
    10 => "#ad6704",
    11 => "#ce7656",
    12 => "#ce8483",


  );
  $key = 1;
  foreach ($fields_terms as $term) {
    //  dpm($fields_terms);
    $items[$term->key]['#markup'] = theme('mica_client_facet_search_checkbox_term', array(
      'agregation_facet' => $agregation_facet,
      'relationship_string' => $relationship_string,
      'term' => $term,
      'color' => $color[$key]
    ));

    $key++;
    if ($key == 12) {
      $key = 0;
    }
  }
  return $items;
}

function mica_client_facet_search_get_range_field($fields_terms, $relationship_string, $agregation_facet) {
  $items['range']['#markup'] = theme('mica_client_facet_search_input_text_range', array(
    'agregation_facet' => $agregation_facet,
    'fields_terms' => $fields_terms,
    'relationship_string' => $relationship_string
  ));
  // return $items;
  return $items;
}


