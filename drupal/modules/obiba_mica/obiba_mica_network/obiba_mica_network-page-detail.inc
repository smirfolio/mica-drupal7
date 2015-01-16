<?php

/*
 * @file code for network detail pages
 * */
include_once('includes/obiba_mica_network_resource.inc');

$path_module_study = drupal_get_path('module', 'obiba_mica_study');
include_once($path_module_study . '/obiba_mica_study-page-detail.inc');

function obiba_mica_network_page_detail($network_id) {
  $url_param = explode('?', request_uri());
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $parts);
  }

  $network_resource = new MicaNetworkResource();
  $network_dto = NULL;

  $network_dto = $network_resource->get_network($network_id);
  if (!empty($network_dto)) {
    $acronym = obiba_mica_commons_get_localized_field($network_dto, 'acronym');
    $name = obiba_mica_commons_get_localized_field($network_dto, 'name');
    drupal_set_title($acronym . ' - ' . $name);

    drupal_set_breadcrumb(array(
      l(t('Home'), '<front>'),
      l(t('Networks'), 'mica/networks'),
    ));

    return theme('obiba_mica_network-detail', array(
      'investigators_modal' => obiba_mica_study_get_contact_detail('investigator', $network_dto->id, $network_dto->investigators),
      'contacts_modal' => obiba_mica_study_get_contact_detail('contact', $network_dto->id, $network_dto->contacts),
      'network_dto' => $network_dto,
      'coverage' => obiba_mica_network_coverage($network_dto->studyIds),
      'group_by' => !empty($parts['group-by']) ? $parts['group-by'] : NULL,
    ));
  }
  else {
    drupal_set_title(t('Network not found'));
    return '';
  }
}

function  obiba_mica_network_study_table($network_dto) {
  $rows = obiba_mica_network_study_table_rows($network_dto->studySummaries);
  $headers = obiba_mica_network_study_table_headers();

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows,
      'empty' => t('No study found'),
      'sticky' => FALSE
    )
  );
}

function obiba_mica_network_study_table_rows($study_summaries) {
  $rows = array();
  if (!empty($study_summaries)) {
    foreach ($study_summaries as $study_summary) {
      $name = obiba_mica_commons_get_localized_field($study_summary, 'name');
      $rows[] = array(
        obiba_mica_commons_get_localized_field($study_summary, 'acronym'),
        l($name, 'mica/study/' . $study_summary->id . '/' . obiba_mica_commons_to_slug($name)),
        implode(', ', t($study_summary->designs)),
        isset($study_summary->targetNumber->noLimit) ? t('No Limit') :
          isset($study_summary->targetNumber->number) ? $study_summary->targetNumber->number : NULL,
        implode(', ', $study_summary->countries),
      );
    }
  }
  return $rows;
}

function obiba_mica_network_study_table_headers() {
  return array(
    t('Acronym'),
    t('Name'),
    t('Study Design'),
    t('Target Number'),
    t('Country'),
  );
}

function obiba_mica_network_coverage($study_ids) {
  return obiba_mica_facet_search_query_charts(MicaClient::add_parameter_dto_query_link(array('variables' => array('terms' => array('studyIds' => $study_ids)))));
}


