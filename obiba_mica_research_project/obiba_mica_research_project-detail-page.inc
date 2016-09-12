<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

include_once('includes/obiba_mica_research_project_resource.inc');

/**
 * @param $project_id
 * @return mixed
 */
function obiba_mica_research_project_page_detail($project_id) {
  $research_project_resource = new MicaResearchProjectResource(NULL);
  
  $response = $research_project_resource->getProject($project_id);

  $model = new stdClass();
  if (!empty($response->content)) {
    $model = json_decode($response->content);
  }

  if (module_exists('obiba_mica_files')) {
    drupal_add_js(drupal_get_path('module', 'obiba_mica_files') . '/js/obiba_mica_files_attachment_download.js');
    $flat_project_attachments = obiba_mica_files_get_flat_attachments('project', $project_id);
    $filtered_tree_path = $flat_project_attachments->findNodeFullPath('/project/' . $project_id);
    if (!empty($filtered_tree_path)) {
      $themed_attachment = $flat_project_attachments->themeFolders($filtered_tree_path, NULL, $project_id);
    }
    obiba_mica_app_angular_load_js_resources('obiba_mica_files');
  }

  drupal_set_title(obiba_mica_commons_get_localized_field($response, 'title'));

  drupal_set_breadcrumb(array(
    l(t('Home'), '<front>'),
    l(t('Research'), MicaClientPathProvider::RESEARCH_PROJECT),
    l(t('Approved Projects'), MicaClientPathProvider::RESEARCH_PROJECT_APPROVED),
  ));

  return theme('obiba_mica_research_project-detail-page', array(
    'project' => $response,
    'model' => $model,
    'attachments' => !empty($themed_attachment) ? $themed_attachment : NULL,
    'file_browser' => theme('obiba_mica_files_browser', array(
      'doc_path' => '/project',
      'doc_id' => $project_id
    )),
  ));
}
