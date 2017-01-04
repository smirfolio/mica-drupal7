<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Mica client studies retrieve Studies lists
 */

function obiba_mica_study_page_list() {
  $context['url'] = 'refresh_list_studies';
  if (!variable_get_value('studies_list_show_trimmed_description_study')) {
    drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/obiba-mica-commons-list-shorten-text.js', 'file');
    drupal_add_js(array(
      'linkRead' => array(
        'more' => t('Read more'),
        'less' => t('Read less'),
      )
    ), 'setting');
  }
  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $study_query = NULL;
  $study_sort = NULL;
  $study_sort_by = NULL;
  $study_limits = NULL;

  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('study_list_page'));
  drupal_set_title($node_rendered['#node']->title);

  $themed_studies = '';
  $node_rendered['#node']->title = '';

  if (!empty($_GET['search-query'])) {
    $study_query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $study_sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $study_sort_by = $_GET['search-sort-order'];
  }

  if (!empty($_GET['search-nbr-result'])) {
    $study_limits = $_GET['search-nbr-result'];
  }

  $response = obiba_mica_study_get_studies($study_query, $study_sort, $study_sort_by, $study_limits);
  $total_studies = empty($response) ? 0 : $response->getTotalHits();
  $study_limits = !empty($study_limits) ? $study_limits : DrupalMicaClientResource::getResponsePageSizeSmall();

  pager_default_initialize($total_studies, $study_limits);
  $pager_output = theme('pager', array('quantity' => $study_limits));
  $summaries = empty($response) ? array() : $response->getSummaries();
  if (!empty($summaries)) {
    $i = 0;
    foreach ($summaries as $study) {
      if (!empty($study->logo->id)) {
        $logo_url = obiba_mica_commons_safe_expose_server_url($study->id, $study->logo, 'study');
      }
      else {
        $logo_url = NULL;
      }
      $themed_studies .= theme('obiba_mica_study-list-page-block', array(
        'study' => $study,
        'logo_url' => $logo_url,
        'network_digests' => $response->getNetworkDigests($study->id)
      ));
      $i++;
    }
  }
  else {
    $themed_studies = variable_get_value('studies_empty_label');
  }
  $show_rapid_search_form = variable_get_value('studies_list_show_search_form');
  return theme('obiba_mica_study_list-page', array(
    "form_search" => !empty($show_rapid_search_form) ? drupal_get_form('obiba_mica_study_create_form') : '',
    "node_page" => $node_rendered,
    "total_items" => $total_studies,
    "list_studies" => $themed_studies,
    "pager_wrap" => $pager_output
  ));
}

function obiba_mica_study_retrieve_studies($query, $sort = NULL, $sort_order = NULL, $size_response_param = NULL) {
  $list_studies = obiba_mica_study_get_studies($query, $sort, $sort_order, $size_response_param);
  $list_studies_rendered = '';
  if (!empty($list_studies)) {
    foreach ($list_studies->getSummaries() as $study) {
      $list_studies_rendered .= theme('obiba_mica_study-list-page-block', array(
        'study' => $study,
      ));
    }
    $data['list'] = $list_studies_rendered;
    $data['total'] = $list_studies->getTotalHits();
    drupal_json_output($data);
  }
  else {
    return FALSE;
  }
}

function obiba_mica_study_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'numberOfParticipants.participant.number' => t('Target Number'), //
        ) //
    );

  return obiba_mica_commons_create_search_form($context);
}

function obiba_mica_study_get_studies($query = NULL, $sort = NULL, $order = NULL, $study_limits = NULL) {
  $from = 0;
  $study_resource = new DrupalMicaStudyResource();
  $size_response = intval($study_limits) > 0 ? $study_limits : DrupalMicaClientResource::getResponsePageSizeSmall();
  $type = 'studies';

  prepopulate_session_with_studies_count_if_needed($type, $study_resource);

  if (!empty($_GET['page'])) {
    $from = $study_resource->paginationListSearchParameters($_GET['page'], $type, $size_response);
  }

  if (empty($sort)) {
    $study_list_sort_option = variable_get_value('study_list_name_acronym_sort');
    if (!empty($study_list_sort_option)) {
      if ($study_list_sort_option == 1) {
        $sort = 'name';
      }
      else {
        if ($study_list_sort_option == 2) {
          $sort = 'acronym';
        }
      }
    }
  }

  $response = $study_resource->getStudies($query, $from, $size_response, $sort, $order);

  populate_session_with_studies_count($response, $type);

  return $response;
}

function prepopulate_session_with_studies_count_if_needed($type, DrupalMicaStudyResource $study_resource) {

  if (empty(@$_SESSION[$type])) {
    $studies = $study_resource->getStudies(NULL, 0, 1, NULL, NULL);
    populate_session_with_studies_count($studies, $type);
  }
}

function populate_session_with_studies_count($response, $type) {
  if (!empty($response)) {
    $_SESSION[$type]['aggregations']['total_hits'] = $response->getTotalHits();
  }
}

function obiba_mica_study_studies_table($studies) {
  $rows = array();
  $total = 0;
  if (!empty($studies['total_hits']) && $studies['total_hits'] > 0) {
    $total = $studies['total_hits'];
    $rows = obiba_mica_study_study_summaries_table_rows($studies['data']);
  }
  $headers = obiba_mica_study_study_summaries_table_headers();
  $per_page = 20;

  $args = array(
    'quantity' => $total,
    'element' => DrupalMicaStudyResource::PAGINATE_STUDIES
  );
  $current_page = pager_default_initialize($total, $per_page, DrupalMicaStudyResource::PAGINATE_STUDIES);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => empty($chunks) ? array() : $chunks[$current_page],
      'empty' => variable_get_value('studies_empty_label')
    )
  ) . theme('pager', $args);
}

function obiba_mica_study_study_summaries_table_headers() {

  return array(
    array("title" => t('Acronym')),
    array("title" => t('Name')),
    array("title" => t('Study Design')),
    array("title" => t('Target Number')),
    array("title" => t('Countries')),
  );
}

function obiba_mica_study_study_summaries_table_rows($study_summaries) {
  $rows = array();
  if (!empty($study_summaries)) {
    foreach ($study_summaries as $study_summary) {
      $rows[] = obiba_mica_study_study_summaries_table_row($study_summary);
    }
  }
  return $rows;
}

function obiba_mica_study_study_summaries_table_row($study_summary) {
  $name = obiba_mica_commons_get_localized_field($study_summary, 'name');
  return array(
    l(obiba_mica_commons_get_localized_field($study_summary, 'acronym'), 'mica/study/' . $study_summary->id),
    $name,
    implode(', ', obiba_mica_commons_clean_string($study_summary->designs)),
    isset($study_summary->targetNumber->noLimit) ? t('No Limit') :
      isset($study_summary->targetNumber->number) ? obiba_mica_commons_format_number($study_summary->targetNumber->number) : NULL,
    isset($study_summary->countries) ? obiba_mica_commons_countries($study_summary->countries) : NULL,
  );
}
