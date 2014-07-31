<?php

function mica_client_study_page_search($request) {
  $output['title'] = t('Study search page');
  $output['data'] = mica_client_study_studies_search_table($request);
  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/mica_studies.css', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/mica-client-study-search.js', 'file');
  drupal_add_js(array('mica_client_study' => array('queries' => 'test_param')), 'setting');
  return theme('mica_client_study_search', array("context_detail" => $output));
}

function mica_client_study_studies_search_table($request) {
  $rows = array();
  $study_resource = new MicaStudyResource();
  $studies = $study_resource->studies_search($request);
  foreach ($studies['data'] as $study) {
    $name = mica_client_commons_get_localized_field($study, 'name');
    $rows[] = array(
      mica_client_commons_get_localized_field($study, 'acronym'),
      l($name, 'mica/study/' . mica_client_commons_to_slug($name) . '/' . $study->id),
      implode(', ', t($study->designs)),
      isset($study->targetNumber->noLimit) ? t('No Limit') :
        isset($study->targetNumber->number) ? $study->targetNumber->number : NULL,
      implode($study->countries),
    );
  }
//dpm($studies['totalHits']);
  $headers = array(
    t('Short Name'),
    t('Name'),
    t('Study Design'),
    t('Target number of participants'),
    t('Country of residence'),
  );
  $per_page = $study_resource::SIZE_RESPONSE;
  pager_default_initialize($studies['totalHits'], $per_page);


  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows, // empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
    )
  ) . theme('pager', array('quantity' => 10));
}



