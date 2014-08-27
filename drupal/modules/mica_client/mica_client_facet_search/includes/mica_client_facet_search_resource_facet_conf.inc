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
  foreach ($fields_terms as $term) {
    //  dpm($fields_terms);
    $items[$term->key] = array(
      '#markup' => '<div id="checkthebox" class="terms_checkbox" term="' . $agregation_facet . '-' . $term->key . '"><input type="checkbox" name="' .
        $relationship_string . $agregation_facet . '[]" value="' . $agregation_facet . '.' . $term->key . '" id="' .
        $agregation_facet . '-' . $term->key . '" >' .
        $term->key . '(' . $term->count . ') </div>'
    );
  }
  return $items;
}

function mica_client_facet_search_get_range_field($fields_terms, $relationship_string, $agregation_facet) {
  $items['range'] = array(
    '#markup' => '  <div  id="range" class="facet_terms_range form-inline"  term="' . $agregation_facet . '-range">
      ranges from ' . $fields_terms['min'] . ' to ' . $fields_terms['max'] . '
<br />
  <label for="edit-range-from" >From </label>
<input type="text" id="range-auto-fill"  termselect ="' . $agregation_facet . '"  term="' . $agregation_facet . '-min" value="' . $fields_terms['min'] . '"
maxlength="75" class="form-control form-item-range-from">

  <label for="edit-range-to" class="control-label">To </label>
<input type="text" id="range-auto-fill"  termselect ="' . $agregation_facet . '" term="' . $agregation_facet . '-max" value="' . $fields_terms['max'] . '"
maxlength="75" class="form-control form-item-range-from">

<input type="hidden" id="' .
      $agregation_facet . '" name="' .
      $relationship_string . $agregation_facet . '-range[]" value="" maxlength="75" class="form-control form-item-range-from">

<div class="btn btn-primary btn-xs" id="checkthebox">Go</div>
</div>
'
  );
  // return $items;
  return $items;
}


