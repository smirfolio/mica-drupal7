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
  if (!empty($query)) {
    $locale = $request_parameters['locale'];
    $target = $request_parameters['target'];
    $cacheKey = 'taxonomies_search-' . $query
      . (!empty($target) ? '-' . $target : '')
      . (!empty($locale) ? '-' . $locale : '');

    $cached_result = obiba_mica_commons_get_cache($cacheKey);
    if (!empty($cached_result)) {
      $taxonomies = $cached_result->data;
    }
    else {
      $taxonomies_resource = new ObibaSearchResources();
      $taxonomies = $taxonomies_resource->taxonomiesSearch($query, $target, $locale);
      obiba_mica_commons_set_cache($cacheKey, $taxonomies);
    }
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
 * Get filtered taxonomy
 */
function obiba_mica_angular_search_taxonomy_filter($name) {
  $taxonomy = array();
  $request_parameters = drupal_get_query_parameters();

  if (!empty($request_parameters['target'])) {
    $cached_result = obiba_mica_commons_get_cache('taxonomy_filter-' . $name . '-' . $request_parameters['target']);

    if (!empty($cached_result)) {
      $taxonomy = $cached_result->data;
    } else {
      $taxonomies_resource = new ObibaSearchResources();
      $taxonomy = $taxonomies_resource->taxonomyFilter($name, $request_parameters['target']);
      obiba_mica_commons_set_cache('taxonomy_filter-' . $name . '-' . $request_parameters['target'], $taxonomy);
    }
  }

  drupal_json_output($taxonomy);
}

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_repository_query($type, $query) {
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
function obiba_mica_repository_variable_coverage($query) {
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

/**
 * Get Vocabulary detail by $taxonomy
 */
function obiba_mica_repository_variable_coverage_download($query) {
    $search_resource = new ObibaSearchResources();
    $search_resource->variablesCoverageDownload($query, MicaClient::HEADER_CSV);
$response = !empty($search_resource->getLastResponse()->body)?$search_resource->getLastResponse()->body:NULL;
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
