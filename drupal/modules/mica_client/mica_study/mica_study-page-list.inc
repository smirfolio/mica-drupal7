<?php
/**
 * @file
 * Mica studies file
 */
require_once(drupal_get_path('module', 'mica_protobuf') . '/mica_protobuf-queryDto.inc');


function mica_study_page_list() {
  $output['title'] = t('List of studies');
  $output['data'] = mica_study_studies_table();
  return theme('mica_study_list', array("context_detail" => $output));
}


function mica_study_studies_table() {
  $rows = array();
  $query = new QueryDto();
  $studiesDto = $query->get_list('studies', '\obiba\mica\StudySummaryDto');
  $i = 0;
  foreach ($studiesDto as $study) {
    $name = $study->name[0]->value;
    $rows[] = array(
      $i++,
      l($name, 'mica/study/' . mica_commons_string_to_slug($name) . '/' . $study->id, array(
        'attributes' => array('id' => $name)
      )),
      $study->timestamps->created
    );
  }

  $header = array('', t('Title Studies'), t('Created'));
  $per_page = 20;
  $current_page = pager_default_initialize(count($rows), $per_page);
  $chunks = array_chunk($rows, $per_page, TRUE);

  $output = theme(
      'table',
      array(
        'header' => $header,
        'rows' => $chunks[$current_page],
        'empty' => t('No data found'),
        'sticky' => FALSE,
        'attributes' => array('id' => 'variables_overview')
      )
    ) . theme('pager', array('quantity', count($rows)));

  return $output;
}



