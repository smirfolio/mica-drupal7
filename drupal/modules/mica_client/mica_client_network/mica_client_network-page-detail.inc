<?php
include_once('includes/mica_client_network_resource.inc');

function mica_client_network_page_detail($network_id) {
  $url_param = explode('?', $_SERVER['REQUEST_URI']);
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $parts);
  }

  $network_resource = new MicaNetworkResource();
  $network_dto = NULL;

  $network_dto = $network_resource->get_network($network_id);
  if (!empty($network_dto)) {
    drupal_set_title(mica_client_commons_get_localized_field($network_dto, 'name'));

    drupal_set_breadcrumb(array(
      l('Home', '<front>'),
      l(t('Networks'), 'mica/networks'),
    ));

    return theme('mica_client_network-detail', array(
      'network_dto' => $network_dto,
      'coverage' => mica_client_network_coverage($network_dto->studyIds),
      'group_by' => !empty($parts['group-by']) ? $parts['group-by'] : NULL,
    ));
  }
  else {
    drupal_set_title(t('Network not found'));
    return '';
  }
}

function  mica_client_network_study_table($network_dto) {
  $rows = mica_client_network_study_table_rows($network_dto->studySummaries);
  $headers = mica_client_network_study_table_headers();

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

function mica_client_network_study_table_rows($study_summaries) {
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

function mica_client_network_study_table_headers() {
  return array(
    t('Short Name'),
    t('Name'),
    t('Study Designs'),
    t('Target Number'),
    t('Countries'),
  );
}

function mica_client_network_coverage($study_ids) {
  return mica_client_facet_search_query_charts(MicaClient::add_parameter_dto_query_link(array('variables' => array('terms' => array('studyIds' => $study_ids)))));
}


