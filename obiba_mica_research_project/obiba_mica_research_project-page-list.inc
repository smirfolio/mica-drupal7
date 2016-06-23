<?php

/**
 * @file
 * Mica client research projects retrieve published Research Projects list.
 */

function obiba_mica_research_project_page_list() {
  $context['url'] = 'refresh_list_projects';

  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');

  $project_query = NULL;
  $project_sort = NULL;
  $project_sort_by = NULL;
  $project_limits = NULL;

  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('research_project_page'));
  drupal_set_title($node_rendered['#node']->title);

  if (!empty($_GET['search-query'])) {
    $project_query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $project_sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $project_sort_by = $_GET['search-sort-order'];
  }
  if (!empty($_GET['search-nbr-result'])) {
    $project_limits = $_GET['search-nbr-result'];
  }

  $themed_projects = '';
  $node_rendered['#node']->title = '';

  $response = obiba_mica_research_project_get_projects($project_query, $project_limits, $project_sort, $project_sort_by);
  $total_projects = empty($response) ? 0 : $response->total;
  $project_limits = !(empty($project_limits)) ? $project_limits : MicaClient::getResponsePageSizeSmall();

  pager_default_initialize($total_projects, $project_limits);
  $pager_output = theme('pager', array('quantity' => $project_limits));

  if (!empty($response) && !empty($response->projects)) {
    foreach ($response->projects as $project) {
      $content = NULL;
      if (!empty($project->content)) {
        $content = (json_decode($project->content));
      }
      
      if (user_is_anonymous()) {
        $themed_projects .= theme('obiba_mica_research_project-list-page-block', array(
          'project' => $project,
          'content' => $content
        ));
        $themed_projects .= '<hr class="row">';
      } else {               
        $themed_projects .= theme('obiba_mica_research_project-list-page-authenticated-block', array(
          'project' => $project,
          'content' => $content
        ));
      }
    }
  } else {
    $themed_projects = variable_get_value('project_empty_label');
  }

  $page_template = 'obiba_mica_research_project-list-page';

  if (user_is_anonymous()) {
    return theme($page_template, array(
      'form_search' => drupal_get_form('obiba_mica_research_project_create_form'),
      'node_content' => $node_rendered,
      'list_projects' => $themed_projects,
      'total_items' => $total_projects,
      'pager_wrap' => $pager_output
    ));
  } else {
    $page_template = 'obiba_mica_research_project-list-page-authenticated';

    return theme($page_template, array(
      'node_content' => $node_rendered,
      'list_projects' => $themed_projects,
      'total_items' => $total_projects
    ));
  }
}

function obiba_mica_research_project_create_form() {
  global $language;
  $context = array(
    'options' => array(
      'title.' . $language->language => t('Title'),
    )
  );

  return obiba_mica_commons_create_search_form($context, FALSE, FALSE);
}

function obiba_mica_research_project_get_projects($query = NULL, $limit = NULL, $sort = NULL, $order = NULL) {
  $from = 0;
  $research_project_resource = new MicaResearchProjectResource(NULL, 'METHOD_GET');
  $size_response = intval($limit) > 0 ? $limit : MicaClient::getResponsePageSizeSmall();
  if (!empty($_GET['page'])) {
    $from = $research_project_resource->paginationListSearchParameters($_GET['page'], 'projects', $size_response);
  }
  $response = $research_project_resource->getProjects($query, $from, $size_response, $sort, $order);
  return $response;
}