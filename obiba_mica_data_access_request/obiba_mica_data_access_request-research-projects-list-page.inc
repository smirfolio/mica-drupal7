<?php

if (module_exists('obiba_mica_research_project')) {
  $path_module_research_projects = drupal_get_path('module', 'obiba_mica_research_project');
  include_once($path_module_research_projects . '/includes/obiba_mica_research_project_resource.inc');
}

function obiba_mica_data_access_request_research_projects_list_page() {
  $node_rendered = obiba_mica_data_access_request();
  drupal_set_title(obiba_mica_data_access_request_title_callback());

  $themed_projects = '';
  $node_rendered['#node']->title = '';

  $response = NULL;
  if (module_exists('obiba_mica_research_project')) {
    $response = obiba_mica_data_access_request_research_project_get_projects();
  }
  if (!empty($response) && !empty($response->projects)) {
    foreach ($response->projects as $project) {
      $content = NULL;
      if (!empty($project->content)) {
        $content = (json_decode($project->content));
      }
      $themed_projects .= theme('obiba_mica_data_access_request-research-project-list-page-block', array(
        'project' => $project,
        'content' => $content
      ));
    }
  } else {
    $themed_projects = variable_get_value('project_empty_label');
  }
  return theme('obiba_mica_data_access_request-research-project-list-page', array(
    'node_content' => $node_rendered,
    'list_projects' => $themed_projects,
    'total_items' => !empty($response) ? $response->total : 0
  ));
}

function obiba_mica_data_access_request_research_project_get_projects() {
  $research_project_resource = new MicaResearchProjectResource(NULL, 'METHOD_GET');
  $response = $research_project_resource->getProjectsWithAccessibleDAR();
  return $response;
}