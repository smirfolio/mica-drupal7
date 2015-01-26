<?php
/*
 * @file code for resource to configure facet search
 * */

function obiba_mica_facet_search_resource_return_facets($dto_type = NULL) {
  if (empty($_SESSION)) {
    return array();
  }
  switch ($dto_type) {
    case 'facet_conf_variable':
      if (!empty($_SESSION['datasets']) && !empty($_SESSION['datasets']['facets-buckets'])) {
        return $_SESSION['datasets']['facets-buckets'];
      }
    case 'facet_conf_study' :
      if (!empty($_SESSION['studies']) && !empty($_SESSION['studies']['facets-buckets'])) {
        return $_SESSION['studies']['facets-buckets'];
      }
  }
  return array();
}

function obiba_mica_facet_search_get_dto_facet_aggs($tab_block, $type) {
  switch ($tab_block) {
    case 'search-datasetId' :
      $facet_build[$tab_block]['datasetId']['term'] = obiba_mica_facet_search_get_datasets();
      return $facet_build[$tab_block];
  }
  if (!empty($_SESSION[$type])) {
    foreach ($_SESSION[$type]['aggregations'] as $key_tab => $facet) {
      if (is_int($key_tab)) {
        if (!empty($facet->aggregation) && $tab_block == 'search-' . $facet->aggregation) {
          if (!empty($facet->{'obiba.mica.TermsAggregationResultDto.terms'})) {
            $facet_build[$tab_block][$facet->aggregation]['term'] = $facet->{'obiba.mica.TermsAggregationResultDto.terms'};
          }
          elseif (!empty($facet->{'obiba.mica.StatsAggregationResultDto.stats'})) {
            $facet_build[$tab_block][$facet->aggregation]['range']['count'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->count;
            $facet_build[$tab_block][$facet->aggregation]['range']['min'] = isset($facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->min) ? $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->min : NULL;
            $facet_build[$tab_block][$facet->aggregation]['range']['max'] = isset($facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->max) ? $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->data->max : NULL;

            $facet_build[$tab_block][$facet->aggregation]['range']['default']['count'] = $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->count;
            $facet_build[$tab_block][$facet->aggregation]['range']['default']['min'] = isset($facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->min) ? $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->min : NULL;
            $facet_build[$tab_block][$facet->aggregation]['range']['default']['max'] = isset($facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->max) ? $facet->{'obiba.mica.StatsAggregationResultDto.stats'}->default->max : NULL;
          }
          else {
            $facet_build[$tab_block][$facet->aggregation] = NULL;
          }

          return $facet_build[$tab_block];
        }
      }
    }
  }
}

function obiba_mica_facet_search_precess_block_theme($block_delta, $type) {
  $items = array();
  $aggregation_facet = NULL;

  $type_string = $type . ':';
  $total_hits = NULL;
  $total_count = NULL;
  if (!empty($type) && !empty($_SESSION[$type]['aggregations'])) {
    $total_hits = $_SESSION[$type]['aggregations']['totalHits'];
    $total_count = $_SESSION[$type]['aggregations']['totalCount'];
  }

  if (!empty($block_delta)) {
    //  dpm(obiba_mica_commons_get_dto_facet_aggs($block_delta, $type));
    $facet_pars = obiba_mica_facet_search_get_dto_facet_aggs($block_delta, $type);
    $agg_type = "";
    if (!empty($facet_pars)) {
      $aggregation_facet = key($facet_pars);
      $terms_aggregations = current($facet_pars);
      if (!empty($terms_aggregations) && !empty($terms_aggregations['term'])) {
        $agg_type = "terms";
        $items = obiba_mica_facet_search_get_checkbox_term_field($terms_aggregations['term'], $type_string, $aggregation_facet, $total_hits, $total_count);
      }
      if (!empty($terms_aggregations) && !empty($terms_aggregations['range'])) {
        $agg_type = "range";
        $items = obiba_mica_facet_search_get_range_field($terms_aggregations['range'], $type_string, $aggregation_facet);
      }
      $input_form = drupal_get_form('obiba_mica_facet_search_autocomplete_form_field', $aggregation_facet);
      if (strstr($input_form['#id'], 'obiba-mica-facet-search-autocomplete-form-field')) {
        unset($input_form);
      }
      return theme('obiba_mica_facet_search_block_search',
        array(
          'input_autocomplete' => !empty($input_form) ? $input_form : NULL,
          'items' => $items,
          'formId' => $aggregation_facet,
          'operatorId' => sprintf("%s:%s:%s:op", $type, $agg_type, $aggregation_facet)
        )
      );
    }
  }
  return NULL;
}

function obiba_mica_facet_search_autocomplete_form_field($form, &$form_state, $aggregation_facet) {
  switch ($aggregation_facet) {
    case 'studyIds' :
    case 'dceIds' :
    case 'datasetId' :
      $entity_search = explode('Id', $aggregation_facet);
      $title = t('Search a @entity...', array('@entity' => $entity_search[0]));
      $form['#attributes']['class'] = 'autocomplete';
      $form['#id'] = 'auto_' . $aggregation_facet;
      $form['#action'] = '';
      $form['terms'] = array(
        '#attributes' => array(
          'id-attribute' => 'variables:' . $aggregation_facet . '[]-',
          'placeholder' => $title
        ),
        '#type' => 'textfield',
        //'#title' => 'City',
        '#maxlength' => 128,
        '#autocomplete_path' => 'bucket/autocomplete/' . $aggregation_facet,
      );
      // ['placeholder']
      return $form;
      break;
    case 'networkId' :
      $title = t('Search a network...');
      $form['#attributes']['class'] = 'autocomplete';
      $form['#id'] = 'auto_' . $aggregation_facet;
      $form['#action'] = '';
      $form['terms'] = array(
        '#type' => 'textfield',
        '#attributes' => array('id-attribute' => 'networks:id[]-', 'placeholder' => $title),
        //'#title' => 'City',
        '#maxlength' => 128,
        '#autocomplete_path' => 'bucket/autocomplete/' . $aggregation_facet,
      );

      return $form;
      break;
  }
  unset($form);
  return NULL;
}

function obiba_mica_facet_search_autocomplete_ajax_response($aggregation, $term_to_mach) {
  switch ($aggregation) {
    case 'studyIds' :
    case 'dceIds' :
    case 'datasetId' :
      drupal_json_output(obiba_mica_facet_search_get_matched_agg_entries("variables", $aggregation, $term_to_mach));
      break;
    case 'networkId' :
      drupal_json_output(obiba_mica_facet_search_get_matched_agg_entries("studies", $aggregation, $term_to_mach));
      break;
  }
}

function obiba_mica_facet_search_get_matched_agg_entries($type, $aggregation, $term_to_mach) {
  foreach ($_SESSION[$type]['aggregations'] as $aggre) {
    if ($aggre->aggregation == $aggregation) {
      $matches = new ArrayObject();

      foreach ($aggre->{"obiba.mica.TermsAggregationResultDto.terms"} as $term) {
        if (stristr($term->title, $term_to_mach)) {
          $matches[$term->key] = $term->title;
        }
      }

      return $matches;
    }
  }

  return new ArrayObject();
}

function obiba_mica_facet_search_get_checkbox_term_field($fields_terms, $type_string, $aggregation_facet, $total_hits = NULL, $total_count = NULL) {
  $key = 1;
  uasort($fields_terms, 'obiba_mica_facet_search_sort_terms');
  foreach ($fields_terms as $term) {
    if ($aggregation_facet == 'studyIds') {
      $type_string = 'studies:';
    }
    else {
      if ($aggregation_facet == 'networkId') {
        $type_string = 'networks:';
      }
    }
    $query_request = !empty($_GET['query']) ? TRUE : FALSE;
    $items[$term->key]['#markup'] = theme('obiba_mica_facet_search_checkbox_term', array(
      'aggregation_facet' => $aggregation_facet,
      'type_string' => $type_string,
      'term' => !empty($term) ? $term : '',
      'totalHits' => $total_hits,
      'totalCount' => $total_count,
      'query_request' => $query_request
    ));

    $key++;
    if ($key == 12) {
      $key = 0;
    }

  }
  return $items;
}

function obiba_mica_facet_search_sort_terms($x, $y) {
  return $x->count < $y->count;
}

function obiba_mica_facet_search_get_range_field($fields_terms, $type_string, $aggregation_facet) {
  $items['range']['#markup'] = theme('obiba_mica_facet_search_input_text_range', array(
    'aggregation_facet' => $aggregation_facet,
    'fields_terms' => $fields_terms,
    'type_string' => $type_string
  ));
  // return $items;
  return $items;
}

function obiba_mica_facet_search_get_datasets() {
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

