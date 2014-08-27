<?php

function mica_client_study_page_list() {
  $output['title'] = t('Study Catalogue');
  $output['data'] = mica_client_study_studies_table(mica_client_study_get_studies());
  return theme('mica_client_study_list', array("context_detail" => $output));
}

function mica_client_study_get_studies() {
  $study_resource = new MicaStudyResource();
  return $studies = $study_resource->studies_search();
}

function mica_client_study_studies_table($studies) {
  $rows = array();
  $rows = mica_client_study_study_summaries_table_rows($studies['data']);
  $headers = mica_client_study_study_summaries_table_headers();
  $per_page = 20;

//  $args = array('quantity'=>$studies['totalHits'], 'element' => MicaDatasetResource::PAGINATE_Variable);
//  pager_default_initialize($variables['totalHits'], MicaDatasetResource::SIZE_RESPONSE, MicaDatasetResource::PAGINATE_Variable);

  $args = array('quantity' => $studies['totalHits'], 'element' => MicaStudyResource::PAGINATE_studies);
  $current_page = pager_default_initialize($studies['totalHits'], $per_page, MicaStudyResource::PAGINATE_studies);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
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




