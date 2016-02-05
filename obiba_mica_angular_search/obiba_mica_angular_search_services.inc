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
  $taxonomies =array();
  $request_parameters = drupal_get_query_parameters();
  if (!empty($request_parameters['query'])) {
    $taxonomies_resource = new ObibaSearchResources();
    $taxonomies = $taxonomies_resource->taxonomiesSearch($request_parameters['query']);
  }
  drupal_json_output($taxonomies);
}

/**
 * Get filtered taxonomies
 */
function obiba_mica_angular_search_taxonomies_filter() {
  $taxonomies_resource = new ObibaSearchResources();
  $taxonomies = $taxonomies_resource->taxonomiesFilter();
  drupal_json_output($taxonomies);
}

/**
 * Get taxonomy detail by $taxonomy
 */
function obiba_mica_angular_search_get_taxonomy($taxonomy) {
  drupal_json_output(array('taxonomies' => $taxonomy));
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_angular_search_get_vocabulary($taxonomy, $vocabulary) {
  drupal_json_output(array(
    'taxonomies' => $taxonomy,
    'vocabulary' => $vocabulary
  ));
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_angular_search_query($type, $query) {
  $search_resource = new ObibaSearchResources();
  $search_result = $search_resource->searchQuery($type, $query);
  drupal_json_output($search_result);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_angular_search_variable_coverage($query) {
  $search_resource = new ObibaSearchResources();
  $search_result = $search_resource->variablesCoverage($query);
  drupal_json_output($search_result);
}