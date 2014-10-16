<?php

function mica_client_facet_search_resource_return_facets($dto_type = NULL) {
  $path_module = drupal_get_path('module', 'mica_client_facet_search');
  switch ($dto_type) {
    case 'facet_conf_variable':
      $data = file_get_contents($path_module . '/includes/mica_client_facet_search_json_variable_facet.json');
      $facets = drupal_json_decode($data);
      return $facets;
    case 'facet_conf_study' :
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
  switch ($tab_block) {
    case 'search-datasetId' :
      $aggs = array();

      $totalDataset = count($_SESSION[$type]['datasets']);
      $i = 0;
      if (!empty($_SESSION[$type]['datasets'])) {
        foreach ($_SESSION[$type]['datasets'] as $dataset) {
          $values_obj = new stdClass();
          $values_obj->key = $dataset->id;
          $values_obj->count = $totalDataset;
          $aggs[$i] = $values_obj;
          $i++;
        }
      }
      $facet_build[$tab_block]['datasetId']['term'] = $aggs;
      return $facet_build[$tab_block];
    case 'search-networkId' :
      $aggs = array();

      $totalDataset = count($_SESSION[$type]['networks']);
      $i = 0;
      if (!empty($_SESSION[$type]['networks'])) {
        foreach ($_SESSION[$type]['networks'] as $network) {
          $values_obj = new stdClass();
          $values_obj->key = $network->id;
          $values_obj->count = $totalDataset;
          $aggs[$i] = $values_obj;
          $i++;
        }
      }
      $facet_build[$tab_block]['networkId']['term'] = $aggs;
      return $facet_build[$tab_block];
  }

  foreach ($_SESSION[$type]['aggregations'] as $key_tab => $facet) {
    if (is_int($key_tab)) {
      if (!empty($facet->aggregation) && $tab_block == 'search-' . $facet->aggregation) {
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

function mica_client_facet_search_precess_block_theme($block_delta, $type) {
  $items = array();
  $aggregation_facet = NULL;

  $type_string = $type . ':';
  $totalHits = !empty($type) ? $_SESSION[$type]['aggregations']['totalHits'] : NULL;
  $totalCount = !empty($type) ? $_SESSION[$type]['aggregations']['totalCount'] : NULL;

  if (!empty($block_delta)) {
    //  dpm(mica_client_commons_get_dto_facet_aggs($block_delta, $type));
    $facet_pars = mica_client_facet_search_get_dto_facet_aggs($block_delta, $type);
    if (!empty($facet_pars)) {
      $aggregation_facet = key($facet_pars);
      $terms_aggregations = current($facet_pars);
      if (!empty($terms_aggregations) && !empty($terms_aggregations['term'])) {
        $items = mica_client_facet_search_get_checkbox_term_field($terms_aggregations['term'], $type_string, $aggregation_facet, $totalHits, $totalCount);
      }
      if (!empty($terms_aggregations) && !empty($terms_aggregations['range'])) {
        $items = mica_client_facet_search_get_range_field($terms_aggregations['range'], $type_string, $aggregation_facet);
      }
      return theme('mica_client_facet_search_block_search', array('items' => $items, 'formId' => $aggregation_facet));
    }
  }
  return NULL;
}

function mica_client_facet_search_get_checkbox_term_field($fields_terms, $type_string, $aggregation_facet, $totalHits = NULL, $totalCount = NULL) {
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
    if ($aggregation_facet == 'studyIds') {
      $term->name = MicaClient::get_name_entity_by_id_aggregation('variables', 'studies', $term->key);
    }
    if ($aggregation_facet == 'datasetId') {
      $term->name = MicaClient::get_name_entity_by_id_aggregation('variables', 'datasets', $term->key);
    }
    if ($aggregation_facet == 'networkId') {
      $aggregation_facet = 'id';
      $type_string = 'networks:';
      $term->name = MicaClient::get_name_entity_by_id_aggregation('studies', 'networks', $term->key);
    }
    $items[$term->key]['#markup'] = theme('mica_client_facet_search_checkbox_term', array(
      'aggregation_facet' => $aggregation_facet,
      'type_string' => $type_string,
      'term' => !empty($term) ? $term : '',
      //'color' => !empty($color[$key]) ? $color[$key] : '#ce8483',
      'totalHits' => $totalHits,
      'totalCount' => $totalCount
    ));

    $key++;
    if ($key == 12) {
      $key = 0;
    }

  }
  return $items;
}

function mica_client_facet_search_get_range_field($fields_terms, $type_string, $aggregation_facet) {
  $items['range']['#markup'] = theme('mica_client_facet_search_input_text_range', array(
    'aggregation_facet' => $aggregation_facet,
    'fields_terms' => $fields_terms,
    'type_string' => $type_string
  ));
  // return $items;
  return $items;
}


