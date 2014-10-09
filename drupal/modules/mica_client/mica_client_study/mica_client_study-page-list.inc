<?php

function mica_client_study_page_list() {
  $context['url'] = 'refresh_list_studies';
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
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

  $response = mica_client_study_get_studies($study_query, $study_sort, $study_sort_by);
  $total_studies = $response->getTotalHits();
  pager_default_initialize($total_studies, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $summaries = $response->getSummaries();
  if (!empty($summaries)) {
    foreach ($summaries as $study) {
      if (!empty($study->logo->id)) {
        $logo_url = mica_client_commons_safe_expose_server_url($study->id, $study->logo, 'study');
      }
      else {
        $logo_url = NULL;
      }
      $themed_studies .= theme('mica_client_study-list-page-block', array(
        'study' => $study,
        'logo_url' => $logo_url,
        'network_digests' => $response->getNetworkDigests($study->id)
      ));
    }
  }
  else {
    $themed_studies = t('No study found');
  }
  return theme('mica_client_study_list-page', array(
    "form_search" => drupal_get_form('mica_client_study_create_form'),
    "node_page" => $node_rendred,
    "total_items" => $total_studies,
    "list_studies" => $themed_studies,
    "pager_wrap" => $pager_output
  ));
}

function mica_client_study_retrieve_studies($query, $sort = NULL, $sort_order = NULL) {
  $list_studies = mica_client_study_get_studies($query, $sort, $sort_order);
  $list_studies_rendered = '';
  foreach ($list_studies->getSummaries() as $study) {
    $list_studies_rendered .= theme('mica_client_study-list-page-block', array(
      'study' => $study,
    ));
  }
  $data['list'] = $list_studies_rendered;
  $data['total'] = $list_studies->getTotalHits();
  drupal_json_output($data);
}

function mica_client_study_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'numberOfParticipants.participant.number' => t('Target Number'), //
          'populations.selectionCriteria.countriesIso' => t('Countries') //
        ) //
    );

  return mica_client_commons_create_search_form($context);
}

function mica_client_study_get_studies($query = NULL, $sort = NULL, $order = NULL) {
  $from = 0;
  $study_resource = new MicaStudyResource();
  if (!empty($_GET['page'])) {
    $from = $study_resource->pagination_list_search_parameters($_GET['page'], 'list-studies', 5);
  }

  $response = $study_resource->get_studies($query, $from, NULL, $sort, $order);
  $_SESSION['list-studies']['aggregations']['totalHits'] = $response->getTotalHits();

  return $response;
}

function mica_client_study_studies_table($studies) {
  $rows = array();
  $total = 0;
  if (!empty($studies['totalHits']) && $studies['totalHits'] > 0) {
    $total = $studies['totalHits'];
    $rows = mica_client_study_study_summaries_table_rows($studies['data']);
  }
  $headers = mica_client_study_study_summaries_table_headers();
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

function mica_client_study_study_summaries_table_rows($study_summaries) {
  $rows = array();
  if (!empty($study_summaries)) {
    foreach ($study_summaries as $study_summary) {
      $name = mica_client_commons_get_localized_field($study_summary, 'name');
      $rows[] = array(
        mica_client_commons_get_localized_field($study_summary, 'acronym'),
        l($name, 'mica/study/' . $study_summary->id . '/' . mica_client_commons_to_slug($name)),
        implode(', ', t($study_summary->designs)),
        isset($study_summary->targetNumber->noLimit) ? t('No Limit') :
          isset($study_summary->targetNumber->number) ? $study_summary->targetNumber->number : NULL,
        implode($study_summary->countries),
      );
    }
  }
  return $rows;
}

function mica_client_study_study_summaries_table_headers() {
  return array(
    t('Short Name'),
    t('Name'),
    t('Study Designs'),
    t('Target Number'),
    t('Countries'),
  );
}




