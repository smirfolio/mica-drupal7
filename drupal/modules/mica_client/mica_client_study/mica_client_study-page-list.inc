<?php

function mica_client_study_page_list() {
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/ajax_getlist_items.js', 'file');
  $study_query = NULL;
  $study_sort = NULL;
  $study_sort_by = NULL;
  $node_view = node_view(node_load(variable_get('study_list_page')));
  $node_view['#node']->title = '';
  if (!empty($_GET['studies-query'])) {
    $study_query = $_GET['studies-query'];
  }
  if (!empty($_GET['studies-sort'])) {
    $study_sort = $_GET['studies-sort'];
  }
  if (!empty($_GET['studies-sort-order'])) {
    $study_sort_by = $_GET['studies-sort-order'];
  }

  $studies = mica_client_study_get_studies($study_query, $study_sort, $study_sort_by);
  pager_default_initialize($studies->total, 5, $element = 0);
  $pager_output = theme('pager', array('quantity' => $studies->total));
  $studies = theme('mica_client_study-list-page-block', array(
    'studies' => $studies,
    'pager_wrap' => $pager_output
  ));
  return theme('mica_client_study_list-page', array(
    'form_search' => drupal_get_form('mica_client_study_create_form'),
    'node_page' => $node_view,
    'studies' => $studies
  ));
}

function mica_client_study_retrieve_studies($query, $sort = NULL, $sort_order = NULL) {
  $studies = mica_client_study_get_studies($query, $sort, $sort_order);
  pager_default_initialize($studies->total, 5, $element = 0);
  $pager_output = theme('pager', array('quantity' => $studies->total));
  $studies_rendered = theme('mica_client_study-list-page-block', array(
    'studies' => $studies,
    'pager_wrap' => $pager_output
  ));
  $data['studies'] = $studies_rendered;
  $data['total'] = $studies->total;
  drupal_json_output($data);
}

function mica_client_study_create_form() {
  global $language;
  $sort_name = 'name.' . $language->language;
  $sort_acronym = 'acronym.' . $language->language;

  $form = array();
  $form['#method'] = 'get';
  $form['#prefix'] = '<div class="inline-form">';
  $form['#suffix'] = '</div>';
  $form['studies-sort'] = array(
    '#type' => 'select',
    '#title' => '',
    '#description' => t('Sort by'),
    '#options' => array(
      $sort_name => t('Name'),
      $sort_acronym => t('Acronym'),
      'numberOfParticipants.participant.number' => t('Target Number'),
      'populations.selectionCriteria.countriesIso' => t('Countries'),
    ),
    '#default_value' => !empty($_GET['studies-sort']) ? $_GET['studies-sort'] : NULL,
    '#prefix' => '<div class="right-indent lg-width">',
    '#suffix' => '</div>',
  );

  $form['studies-sort-order'] = array(
    '#type' => 'select',
    '#title' => '',
    '#description' => 'Sort order',
    '#options' => array(
      'asc' => t('ASC'),
      'desc' => t('DESC'),
    ),
    '#default_value' => !empty($_GET['studies-sort-order']) ? $_GET['studies-sort-order'] : NULL,
    '#prefix' => '<div class="right-indent md-width">',
    '#suffix' => '</div>',

  );


  $form['studies-query'] = array(
    '#type' => 'textfield',
    '#title' => '',
    '#description' => 'Filter by',
    '#default_value' => !empty($_GET['studies-query']) ? $_GET['studies-query'] : NULL,
    '#prefix' => '<div class="right-indent lg-width">',
    '#suffix' => '</div>',
  );


  return $form;
}

function mica_client_study_get_studies($query = NULL, $sort = NULL, $order = NULL) {
  $from = 0;
  $study_resource = new MicaStudyResource();
  if (!empty($_GET['page'])) {
    $from = $study_resource->pagination_list_searcch_parameters($_GET['page'], 'studies');
  }
  $studies = $study_resource->get_studies($query, $from, NULL, $sort, $order);
  $_SESSION['studies']['aggregations']['totalHits'] = $studies->total;
  return $studies;
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




