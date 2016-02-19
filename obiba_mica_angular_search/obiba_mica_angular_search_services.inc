<?php
/**
 * @file
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Search for taxonomies
 */
function obiba_mica_angular_search_taxonomies_search() {
  $taxonomies = array();
  $request_parameters = drupal_get_query_parameters();
  if (!empty($request_parameters['query'])) {
    $cached_result = obiba_mica_commons_get_cache('taxonomies_search-' . $request_parameters['query']);
    if (!empty($cached_result)) {
      $taxonomies = $cached_result->data;
    }
    else {
      $taxonomies_resource = new ObibaSearchResources();
      $taxonomies = $taxonomies_resource->taxonomiesSearch($request_parameters['query']);
      obiba_mica_commons_set_cache('taxonomies_search-' . $request_parameters['query'], $taxonomies);
    }
  }
  drupal_json_output($taxonomies);
}

/**
 * Get filtered taxonomies
 */
function obiba_mica_angular_search_taxonomies_filter() {
  $taxonomies = array();
  $request_parameters = drupal_get_query_parameters();
  if (!empty($request_parameters['target'])) {
    $cached_result = obiba_mica_commons_get_cache('taxonomies_filter-' . $request_parameters['target']);
    if (!empty($cached_result)) {
      $taxonomies = $cached_result->data;
    }
    else {
      $taxonomies_resource = new ObibaSearchResources();
      $taxonomies = $taxonomies_resource->taxonomiesFilter($request_parameters['target']);
      obiba_mica_commons_set_cache('taxonomies_filter-' . $request_parameters['target'], $taxonomies);
    }
  }
  drupal_json_output($taxonomies);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_angular_search_query($type, $query) {
  $cached_result = obiba_mica_commons_get_cache('search_query-' . $type . '_' . $query);
  if (!empty($cached_result)) {
    $search_result = $cached_result->data;
  }
  else {
    $search_resource = new ObibaSearchResources();
    $search_result = $search_resource->searchQuery($type, $query);
    obiba_mica_commons_set_cache('search_query-' . $type . '_' . $query, $search_result);
  }
  drupal_json_output($search_result);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_angular_search_variable_coverage($query) {
  $cached_result = obiba_mica_commons_get_cache('variable_coverage-' . $query);
  if (!empty($cached_result)) {
    $search_result = $cached_result->data;
  }
  else {
    $search_resource = new ObibaSearchResources();
    $search_result = $search_resource->variablesCoverage($query);
    obiba_mica_commons_set_cache('variable_coverage-' . $query, $search_result);
  }
  drupal_json_output($search_result);
}
