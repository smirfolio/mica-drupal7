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
function obiba_mica_repository_taxonomies_search() {
  $taxonomies = array();
  $request_parameters = drupal_get_query_parameters();
  $query = $request_parameters['query'];
  // Quote query if there are multiple words (separated by blank spaces)
  $re = "/\\s+/";
  if (preg_match($re, $query)) {
    $re = "/^\"|\"$/";
    $query = '"' . preg_replace($re, '', trim($query)) . '"';
  }
  if (!empty($query)) {
    $locale = $request_parameters['locale'];
    $target = array_key_exists('target', $request_parameters) ? $request_parameters['target'] : '';
    $taxonomies_resource = new ObibaSearchResources();
    $taxonomies = $taxonomies_resource->taxonomiesSearch($query, $target, $locale);
  }
  drupal_json_output($taxonomies);
}

/**
 * Get filtered taxonomies
 */
function obiba_mica_repository_taxonomies_filter() {
  $taxonomies = array();
  $request_parameters = drupal_get_query_parameters();
  if (!empty($request_parameters['target'])) {
    $taxonomies_resource = new ObibaSearchResources();
    $taxonomies = $taxonomies_resource->taxonomiesFilter($request_parameters['target']);
  }
  drupal_json_output($taxonomies);
}

/**
 * Get filtered taxonomy
 */
function obiba_mica_angular_search_taxonomy_filter($name) {
  $taxonomy = array();
  $request_parameters = drupal_get_query_parameters();
  if (!empty($request_parameters['target'])) {
    $taxonomies_resource = new ObibaSearchResources();
    $taxonomy = $taxonomies_resource->taxonomyFilter($name, $request_parameters['target']);
  }
  drupal_json_output($taxonomy);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_repository_query($type, $query) {
  $search_resource = new ObibaSearchResources();
  $search_result = $search_resource->searchQuery($type, $query);
  drupal_json_output($search_result);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_repository_variable_coverage($query) {
  $search_resource = new ObibaSearchResources();
  $search_result = $search_resource->variablesCoverage($query);
  drupal_json_output($search_result);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_repository_variable_coverage_download($query) {
  $search_resource = new ObibaSearchResources();
  $search_resource->variablesCoverageDownload($query, MicaClient::HEADER_CSV);
  $response = !empty($search_resource->getLastResponse()->body) ? $search_resource->getLastResponse()->body : NULL;
  if (!empty($response)) {
    $headers = $search_resource->getLastResponseHeaders();
    $content_mime = $headers['Content-Type'][0];
    $content_disposition = $headers['Content-Disposition'][0];
    $copyright_notice = variable_get_value('mica_copyright_notice');
    $output = !empty($copyright_notice) ? '"' . t($copyright_notice) . '"' . chr(13) : '';
    $output .= $response;
  }
  drupal_add_http_header('Content-Type', $content_mime . '; utf-8');
  drupal_add_http_header('Content-Disposition', $content_disposition);
  ob_clean();
  print $output;
  exit;
}
