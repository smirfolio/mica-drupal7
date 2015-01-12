<?php

/**
 * @file
 * Mica client studies retrieve Studies lists
 */

function obiba_mica_study_page_list() {
  $context['url'] = 'refresh_list_studies';
  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $study_query = NULL;
  $study_sort = NULL;
  $study_sort_by = NULL;
  $node_rendred = node_view(node_load(variable_get('study_list_page')));
  $node_rendred['#node']->title = '';
  $themed_studies = '';

  if (!empty($_GET['search-query'])) {
    $study_query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $study_sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $study_sort_by = $_GET['search-sort-order'];
  }

  $response = obiba_mica_study_get_studies($study_query, $study_sort, $study_sort_by);
  $total_studies = empty($response) ? 0 : $response->getTotalHits();
  pager_default_initialize($total_studies, MicaClient::SIZE_RESPONSE_SM);
  $pager_output = theme('pager', array('quantity' => MicaClient::SIZE_RESPONSE_SM));
  $summaries = empty($response) ? array() : $response->getSummaries();
  if (!empty($summaries)) {
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
    }
  }
  else {
    $themed_studies = t('No study found');
  }
  return theme('obiba_mica_study_list-page', array(
    "form_search" => drupal_get_form('obiba_mica_study_create_form'),
    "node_page" => $node_rendred,
    "total_items" => $total_studies,
    "list_studies" => $themed_studies,
    "pager_wrap" => $pager_output
  ));
}

function obiba_mica_study_retrieve_studies($query, $sort = NULL, $sort_order = NULL) {
  $list_studies = obiba_mica_study_get_studies($query, $sort, $sort_order);
  $list_studies_rendered = '';
  foreach ($list_studies->getSummaries() as $study) {
    $list_studies_rendered .= theme('obiba_mica_study-list-page-block', array(
      'study' => $study,
    ));
  }
  $data['list'] = $list_studies_rendered;
  $data['total'] = $list_studies->getTotalHits();
  drupal_json_output($data);
}

function obiba_mica_study_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'numberOfParticipants.participant.number' => t('Target Number'), //
          'populations.selectionCriteria.countriesIso' => t('Countries') //
        ) //
    );

  return obiba_mica_commons_create_search_form($context);
}

function obiba_mica_study_get_studies($query = NULL, $sort = NULL, $order = NULL) {
  $from = 0;
  $study_resource = new MicaStudyResource();
  if (!empty($_GET['page'])) {
    $from = $study_resource->pagination_list_search_parameters($_GET['page'], 'list-studies', MicaClient::SIZE_RESPONSE_SM);
  }

  $response = $study_resource->get_studies($query, $from, MicaClient::SIZE_RESPONSE_SM, $sort, $order);
  if (!empty($response)) {
    $_SESSION['list-studies']['aggregations']['totalHits'] = $response->getTotalHits();
  }

  return $response;
}

function obiba_mica_study_studies_table($studies) {
  $rows = array();
  $total = 0;
  if (!empty($studies['totalHits']) && $studies['totalHits'] > 0) {
    $total = $studies['totalHits'];
    $rows = obiba_mica_study_study_summaries_table_rows($studies['data']);
  }
  $headers = obiba_mica_study_study_summaries_table_headers();
  $per_page = 20;

  $args = array('quantity' => $total, 'element' => MicaStudyResource::PAGINATE_studies);
  $current_page = pager_default_initialize($total, $per_page, MicaStudyResource::PAGINATE_studies);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No study found')
    )
  ) . theme('pager', $args);
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
    l(obiba_mica_commons_get_localized_field($study_summary, 'acronym'), 'mica/study/' . $study_summary->id . '/' . obiba_mica_commons_to_slug($name)),
    $name,
    implode(', ', $study_summary->designs),
    isset($study_summary->targetNumber->noLimit) ? t('No Limit') :
      isset($study_summary->targetNumber->number) ? $study_summary->targetNumber->number : NULL,
    implode(', ', $study_summary->countries),
  );
}

function obiba_mica_study_study_summaries_table_headers() {
  return array(
    t('Acronym'),
    t('Name'),
    t('Study Designs'),
    t('Target Number'),
    t('Countries'),
  );
}




