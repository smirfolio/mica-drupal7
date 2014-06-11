<?php

function mica_client_study_page_list() {
  $output['title'] = t('Study Catalogue');
  $output['data'] = mica_client_study_studies_table();
  return theme('mica_client_study_list', array("context_detail" => $output));
}

function mica_client_study_studies_table() {
  $rows = array();
  $studies = mica_client_commons_get_list('studies', '\obiba\mica\StudySummaryDto');
  foreach ($studies as $study) {
    dpm($study);
    $name = mica_client_commons_get_localized_field($study, 'name');
    $rows[] = array(
      mica_client_commons_get_localized_field($study, 'acronym'),
      l($name, 'mica/study/' . mica_client_commons_to_slug($name) . '/' . $study->id),
      implode(', ', t($study->designs)),
      $study->targetNumber->noLimit ? t('No Limit') : $study->targetNumber->number,
      implode($study->countries),
    );
  }

  $headers = array(
    t('Short Name'),
    t('Name'),
    t('Study Design'),
    t('Target number of participants'),
    t('Country of residence'),
  );
  $per_page = 20;
  $current_page = pager_default_initialize(count($rows), $per_page);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
    )
  ) . theme('pager', array('quantity', count($rows)));
}



