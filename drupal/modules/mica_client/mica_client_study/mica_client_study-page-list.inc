<?php

function mica_client_study_page_list() {
  $study_query = NULL;
  $node_rendred = node_view(node_load(variable_get('study_list_page')));
  $node_rendred['#node']->title = '';
  if (!empty($_POST['studies-query'])) {
    $study_query = $_POST['studies-query'];
  }

  return theme('mica_client_study_list-page', array(
    "form_search" => drupal_get_form('mica_client_study_create_form'),
    "node_page" => $node_rendred,
    "list_studies" => mica_client_study_get_studies($study_query)
  ));
}

function mica_client_study_create_form() {
  $form = array();
  // Autocomplete field

  $form['studies-sort'] = array(
    '#type' => 'select',
    '#title' => '',
    '#description' => 'Sort By',
    '#options' => array(
      'name' => t('Name'),
      'countries' => t('Yes'),
    ),
    '#autocomplete_path' => 'mica/autocomplete',
    '#prefix' => '<div class="col-md-2">',
    '#suffix' => '</div>',
  );

  $form['studies-query'] = array(
    '#type' => 'textfield',
    '#title' => '',
    '#description' => 'Search studies',
    '#autocomplete_path' => 'mica/autocomplete',
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div>',
  );

  // Form Submit button
//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t('Send'),
//    '#validate' => array('validate_message'),
//  );
  return $form;
}

function mica_client_study_retrieve_studies($string) {
  $study_resource = new MicaStudyResource();
  $studies = $study_resource->get_studies($string);
  $result_studies = array();
  foreach ($studies->studySummaries as $study) {
    $result_studies[] = mica_client_commons_get_localized_field($study, 'acronym');
  }
  dpm($result_studies);
  dpm($studies);
  drupal_json_output($result_studies);
  exit;
}

function mica_client_study_get_studies($query = NULL) {
  $study_resource = new MicaStudyResource();
  return $studies = $study_resource->get_studies($query);
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




