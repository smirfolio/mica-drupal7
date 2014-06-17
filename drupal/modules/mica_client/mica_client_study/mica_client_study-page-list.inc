<?php

function mica_client_study_page_list() {
  $output['title'] = t('Study Catalogue');
  $output['data'] = mica_client_study_studies_table();
  return theme('mica_client_study_list', array("context_detail" => $output));
}

function mica_client_study_studies_table() {
  $rows = array();
  $study_resource = new MicaStudyResource();
  $studies = $study_resource->studies();
  foreach ($studies as $study) {
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



