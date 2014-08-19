<?php
include_once('includes/mica_client_dataset_resource.inc');

$module_study_path = $path_module_protobuf = drupal_get_path('module', 'mica_client_study');
include_once($module_study_path . '/mica_client_study-page-list.inc');

function mica_client_dataset_variable_page_search($request) {

  drupal_set_title(t('Variables @request search', array('@request' => $request)));

  //drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/mica_studies.css', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/mica-client-study-search.js', 'file');
  drupal_add_js(array('mica_client_study' => array('queries' => '')), 'setting');


  $variable_resource = new MicaDatasetResource();
  $study_resource = new MicaStudyResource();

  $variables = $variable_resource->variables_search($request);

  $studies = $study_resource->studies_search();

  $output = '<ul class="nav nav-tabs" role="tablist">
  <li class="active"><a href="#variabletab" role="tab" data-toggle="tab">' . t('Variables') . ' (' . $variables['totalHits'] . ')' . '</a></li>
  <li><a href="#studytab" role="tab" data-toggle="tab">' . t('Studies') . ' (' . $studies['totalHits'] . ')' . '</a></li>

</ul>

<!-- Tab panes -->
<div class="tab-content">
  <div class="tab-pane active" id="variabletab">'
    . mica_client_dataset_variables_table($variables) . '</div>
  <div class="tab-pane" id="studytab">' . mica_client_study_studies_table($studies) . '</div>

</div>';

  return $output;

}


function mica_client_dataset_variables_table($variables) {
  if (!empty($variables['data'])) {
    foreach ($variables['data'] as $variable) {
      $name = $variable->name;
      $rows[] = array(
        l($name, 'mica/variable/' . mica_client_commons_to_slug($name) . '/' . $variable->id),
        !empty($variable->variableLabel) ? mica_client_commons_get_localized_field($variable, 'variableLabel') : '-',
        !empty($variable->datasetName) ? mica_client_commons_get_localized_field($variable, 'datasetName') : '-',
      );
    }
  }
//dpm($studies['totalHits']);
  $headers = array(
    t('Variables'),
    t('Label'),
    t('Dataset')
  );

  $args = array('quantity' => $variables['totalHits'], 'element' => MicaDatasetResource::PAGINATE_variable);
  pager_default_initialize($variables['totalHits'], MicaDatasetResource::SIZE_RESPONSE, MicaDatasetResource::PAGINATE_variable);

  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => $rows, // empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No data found')
    )
  ) . theme('pager', $args);
}
