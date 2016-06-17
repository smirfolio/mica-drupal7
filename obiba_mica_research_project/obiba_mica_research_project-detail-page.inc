<?php

include_once('includes/obiba_mica_research_project_resource.inc');

/**
 * @param $project_id
 * @return mixed
 */
function obiba_mica_research_project_page_detail($project_id) {
  $research_project_resource = new MicaResearchProjectResource(NULL, 'METHOD_GET');   
  
  $response = $research_project_resource->getProject($project_id);

  $researcher = NULL;
  $institution = NULL;

  if (!empty($response->content)) {
    $content = json_decode($response->content);

    if (!empty($content->name)) {
      $researcher = $content->name;
    }
    if (!empty($content->institution)) {
      $institution = $content->institution;
    }
  }

  drupal_set_title(obiba_mica_commons_get_localized_field($response, 'title'));

  drupal_set_breadcrumb(array(
    l(t('Home'), '<front>'),
    l(t('Research Projects'), MicaClientPathProvider::RESEARCH_PROJECT_APPROVED),
  ));

  return theme('obiba_mica_research_project-detail-page', array(
    'project' => $response,
    'creator' => NULL,
    'researcher' => $researcher,
    'institution' => $institution
  ));
}

function convert_and_format_string_date($str_date) {
  return format_date(strtotime($str_date), 'custom', 'd-m-Y h:i a');
}