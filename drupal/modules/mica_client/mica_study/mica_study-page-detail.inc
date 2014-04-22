<?php
/**
 * @file
 * Mica studies file
 */
require_once(drupal_get_path('module', 'mica_protobuf') . '/mica_protobuf-queryDto.inc');

function mica_study_page_detail($study_id) {
  $query = new QueryDto();
  $param = 'study/' . $study_id;
  $StudyDto = $query->get_detail($param, '\obiba\mica\StudyDto');
  drupal_set_title(mica_commons_get_localized_field($StudyDto, 'name'));
  $output['data'] = $StudyDto;
  return theme('mica_study_detail', array("context_detail" => $output));
}
