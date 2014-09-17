<?php

function mica_client_study_page_list() {
  $study_query = NULL;
  $study_sort = NULL;
  $study_sort_by = NULL;
  $node_rendred = node_view(node_load(variable_get('study_list_page')));
  $node_rendred['#node']->title = '';
  if (!empty($_POST['studies-query'])) {
    $study_query = $_POST['studies-query'];
  }
  if (!empty($_POST['studies-sort'])) {
    $study_sort = $_POST['studies-sort'];
  }
  if (!empty($_POST['studies-sort-order'])) {
    $study_sort_by = $_POST['studies-sort-order'];
  }

  return theme('mica_client_study_list-page', array(
    "form_search" => drupal_get_form('mica_client_study_create_form'),
    "node_page" => $node_rendred,
    "list_studies" => mica_client_study_get_studies($study_query, $study_sort, $study_sort_by)
  ));
}

function mica_client_study_create_form() {
  global $language;
  $sort_name = 'name.' . $language->language;
  $sort_acronym = 'acronym.' . $language->language;

  $form = array();

  $form['studies-sort'] = array(
    '#type' => 'select',
    '#title' => '',
    '#description' => 'Sort By',
    '#options' => array(
      $sort_name => t('Name'),
      $sort_acronym => t('Acronyme'),
      'numberOfParticipants.participant.number' => t('Target Number'),
      'populations.selectionCriteria.countriesIso' => t('Countries'),
    ),
    '#default_value' => !empty($_POST['studies-sort']) ? $_POST['studies-sort'] : NULL,
    '#prefix' => '<div class="col-md-2">',
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
    '#prefix' => '<div class="col-md-2">',
    '#suffix' => '</div>',

  );


  $form['studies-query'] = array(
    '#type' => 'textfield',
    '#title' => '',
    '#description' => 'Search studies',
    //'#autocomplete_path' => 'mica/autocomplete',
    '#default_value' => !empty($_POST['studies-query']) ? $_POST['studies-query'] : NULL,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );

  //  Form Submit button
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Send'),
//  );
//  $form['#action'] ='studies';
  return $form;
}

//function mica_client_study_autocomplete_retrieve_studies($string) {
//  $study_resource = new MicaStudyResource();
//  $studies = $study_resource->get_studies($string);
//  $result_studies = array();
//  foreach ($studies->studySummaries as $study) {
//    $result_studies[] = mica_client_commons_get_localized_field($study, 'acronym');
//  }
//  dpm($result_studies);
//  dpm($studies);
//  drupal_json_output($result_studies);
//  exit;
//}

function mica_client_study_get_studies($query = NULL, $sort = NULL, $order = NULL) {
  $study_resource = new MicaStudyResource();
  return $studies = $study_resource->get_studies($query, NULL, NULL, $sort, $order);
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




