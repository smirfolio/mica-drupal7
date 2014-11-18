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
      $facet_build[$tab_block]['datasetId']['term'] = mica_client_facet_search_get_datasets();
      return $facet_build[$tab_block];
    case 'search-networkId' :
      $facet_build[$tab_block]['networkId']['term'] = mica_client_facet_search_get_networks();
      return $facet_build[$tab_block];
  }

  foreach ($_SESSION[$type]['aggregations'] as $key_tab => $facet) {
    if (is_int($key_tab)) {
      if (!empty($facet->aggregation) && $tab_block == 'search-' . $facet->aggregation) {
        if (!empty($facet->{'obiba.mica.TermsAggregationResultDto.terms'})) {
          $facet_build[$tab_block][$facet->aggregation]['term'] = $facet->{'obiba.mica.TermsAggregationResultDto.terms'};
        }
        elseif (!empty($facet->{'obiba.mica.StatsAggregationResultDto.stats'})) {
          $facet_build[$tab_block][$facet->aggregation]['range']['count'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->count;
          $facet_build[$tab_block][$facet->aggregation]['range']['min'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->min;
          $facet_build[$tab_block][$facet->aggregation]['range']['max'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->max;
          $facet_build[$tab_block][$facet->aggregation]['range']['default']['count'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->count;
          $facet_build[$tab_block][$facet->aggregation]['range']['default']['min'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->min;
          $facet_build[$tab_block][$facet->aggregation]['range']['default']['max'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->max;
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
  $totalHits = NULL;
  $totalCount = NULL;
  if (!empty($type) && !empty($_SESSION[$type]['aggregations'])) {
    $totalHits = $_SESSION[$type]['aggregations']['totalHits'];
    $totalCount = $_SESSION[$type]['aggregations']['totalCount'];
  }

  if (!empty($block_delta)) {
    //  dpm(mica_client_commons_get_dto_facet_aggs($block_delta, $type));
    $facet_pars = mica_client_facet_search_get_dto_facet_aggs($block_delta, $type);
    $agg_type = "";
    if (!empty($facet_pars)) {
      $aggregation_facet = key($facet_pars);
      $terms_aggregations = current($facet_pars);
      if (!empty($terms_aggregations) && !empty($terms_aggregations['term'])) {
        $agg_type = "terms";
        $items = mica_client_facet_search_get_checkbox_term_field($terms_aggregations['term'], $type_string, $aggregation_facet, $totalHits, $totalCount);
      }
      if (!empty($terms_aggregations) && !empty($terms_aggregations['range'])) {
        $agg_type = "range";
        $items = mica_client_facet_search_get_range_field($terms_aggregations['range'], $type_string, $aggregation_facet);
      }

      return theme('mica_client_facet_search_block_search',
        array(
          'items' => $items,
          'formId' => $aggregation_facet,
          'operatorId' => sprintf("%s:%s:%s:op", $type, $agg_type, $aggregation_facet)
        )
      );
    }
  }
  return NULL;
}

function mica_client_facet_search_get_checkbox_term_field($fields_terms, $type_string, $aggregation_facet, $totalHits = NULL, $totalCount = NULL) {
  $key = 1;
  //dpm($fields_terms);
  uasort($fields_terms, 'mica_client_facet_search_sort_terms');
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
    $query_request = !empty($_GET['query']) ? TRUE : FALSE;
    $items[$term->key]['#markup'] = theme('mica_client_facet_search_checkbox_term', array(
      'aggregation_facet' => $aggregation_facet,
      'type_string' => $type_string,
      'term' => !empty($term) ? $term : '',
      'totalHits' => $totalHits,
      'totalCount' => $totalCount,
      'query_request' => $query_request
    ));

    $key++;
    if ($key == 12) {
      $key = 0;
    }

  }
  return $items;
}

function mica_client_facet_search_sort_terms($x, $y) {
  return $x->count < $y->count;
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

function mica_client_facet_search_get_datasets() {
  $datasets = array();
  if (!empty($_SESSION['variables']) && !empty($_SESSION['variables']['aggregations'])) {
    $aggs = $_SESSION['variables']['aggregations'];
    array_filter($aggs, function ($agg) use (&$datasets) {
      if ($agg instanceof stdClass //
        && $agg->aggregation === 'datasetId' //
        && !empty($agg->{'obiba.mica.TermsAggregationResultDto.terms'})
      ) {
        $datasets = $agg->{'obiba.mica.TermsAggregationResultDto.terms'};
        return TRUE;
      }
    });
  }

  return $datasets;
}

function mica_client_facet_search_get_networks() {
  $networks = array();
  if (!empty($_SESSION['studies']) && !empty($_SESSION['studies']['networks'])) {
    $studies_networks = $_SESSION['studies']['networks'];
    array_filter($studies_networks, function (stdClass $studies_network) use (&$networks) {

      if (empty($studies_network->{'obiba.mica.NetworkDigestDto.studies'})) {
        $study_ids = $studies_network->studyIds;
      }
      else {
        $study_ids = $studies_network->{'obiba.mica.NetworkDigestDto.studies'}->ids;
      }

      $network = new stdClass();
      $network->key = $studies_network->id;
      $network->default = $_SESSION['studies']['aggregations']['totalCount'];
      $network->count = count($study_ids);
      array_push($networks, $network);
      return TRUE;
    });
  }

  return $networks;
}

