<?php
/**
 * @file
 * Mica studies file
 */

if (module_exists('mica_client_dataset')) {
  $path_module_dataset = drupal_get_path('module', 'mica_client_dataset');
  include_once($path_module_dataset . '/includes/mica_client_dataset_resource.inc');
}

function mica_client_study_page_detail($study_id) {
  $page_render_study = NULL;
  $themed_attachment = '';
  $study_resource = new MicaStudyResource();
  $study_dto = $study_resource->get_study($study_id);
  if (!empty($study_dto)) {
    drupal_set_title(mica_client_commons_get_localized_field($study_dto, 'name'));

    drupal_set_breadcrumb(array(
      l('Home', '<front>'),
      l(t('Studies'), 'mica/studies'),
    ));

    $dataset_output = (module_exists('mica_client_dataset')) ?
      mica_client_dataset_get_all_datasets_studies($study_id) : NULL;

    $network_output = (module_exists('mica_client_network')) ?
      mica_client_network_networks_list($study_id) : NULL;

    $opal_output = !empty($study_dto->opal) ? mica_client_study_get_opal_url($study_dto->opal) : NULL;
    if (!empty($study_dto->attachments)) {
      foreach ($study_dto->attachments as $attachment) {
        $themed_attachment .= mica_client_study_get_attachment_file($study_dto->id, $attachment);
      }
    }
    return theme('mica_client_study_detail',
      array(
        'study_dto' => $study_dto,
        'study_attachements' => $themed_attachment,
        'timeline' => mica_client_study_get_timeline_detail($study_dto),
        'populations' => mica_client_study_get_populations_detail($study_dto),
        'datasets' => $dataset_output,
        'networks' => $network_output,
        'opal' => $opal_output,
        'study_variables_aggs' => NULL, //mica_client_study_get_variables($study_id),
      ));
  }
  else {
    drupal_set_title(t('Study not found'));
    return '';
  }
}

function mica_client_study_get_opal_url($opal_url) {
  return theme('mica_client_study_opal', array('opal_url' => $opal_url));
}


/**
 * Implements hook_library().
 */
function mica_client_study_library() {
  $libraries = array();
  $lib_path = libraries_get_path('micatimelines');
  // Make sure we have a valid library path before returning library load info.
  if (!empty($lib_path)) {
    $libraries['micatimeline'] = array(
      'title' => 'MicaTimeLine',
      'website' => 'http://obiba.org/',
      'version' => '0.1',
      'js' => array(
        $lib_path . '/js/d3.min.js' => array(),
        $lib_path . '/js/mica-study-timeline.js' => array()
      ),
      'css' => array(
        $lib_path . '/css/timeline.css' => array(),
      )
    );
  }
  return $libraries;
}

/*
 * Format time-line schema
 * */
function mica_client_study_get_timeline_detail($study_detail) {
  $study_json = json_encode($study_detail);

  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/mica_studies.css', 'file');
  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/timeline.css', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/d3.min.js', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/mica-study-timeline.js', 'file');
  $page_render_timeline = '<div id="vis" style="width=100%"></div>';
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/example.js', 'file');
  drupal_add_js(array('mica_client_study' => array('study_json' => $study_json)), 'setting');

  return $page_render_timeline;
}

/*
 * Format populations schema
 * */

function mica_client_study_get_populations_detail($study_detail) {
  $page_render_populations = array();

  if (!empty($study_detail->populations)) {
    foreach ($study_detail->populations as $population) {
      $dce_uids = array();
      if (!empty($population->dataCollectionEvents)) {
        $dce_rows = mica_client_study_get_dce_table($population->dataCollectionEvents);
        uasort($dce_rows, 'mica_client_study_sort_dce');
        _mica_client_commons_normalize_rows($dce_rows);

        $population['dce-tab'] = theme(
          'table',
          array(
            'header' => array(t('Name'), t('Description'), t('Start'), t('End')),
            'rows' => $dce_rows,
            'empty' => t('No data collection event found'),
            'sticky' => FALSE,
            'attributes' => array('id' => 'variables_overview')
          )
        );
        $population['dce-modal'] = mica_client_study_get_dce_detail($study_detail->id, $population->id, $population->dataCollectionEvents);
        foreach ($population->dataCollectionEvents as $dce) {
          $dce_uids[] = $study_detail->id . ':' . $population->id . ':' . $dce->id;
        }
      }
      $page_render_populations[$population->id] = array(
        'data' => $population,
        'html' => theme('mica_population_detail', array(
          'study_id' => $study_detail->id,
          'dce_uids' => $dce_uids,
          'population' => $population
        ))
      );
    }
  }

  return $page_render_populations;
}

/**
 * Create modal DOM for data collection events
 * @param $study_id
 * @param $dataCollectionEvents
 * @return string
 */
function mica_client_study_get_dce_detail($study_id, $population_id, $dataCollectionEvents) {
  $page_render_dces = '';
  $themed_attachment = '';
  foreach ($dataCollectionEvents as $dce) {
    if (!empty($dce->attachments)) {
      foreach ($dce->attachments as $attachment) {
        // TODO this should be addressed from the server-side
//        $themed_attachment .= mica_client_study_get_attachment_file($dce_wrapper->id, $attachment, 'study');
      }
    }
    $page_render_dces .= theme('mica_dce_detail', array(
      'study_id' => $study_id,
      'population_id' => $population_id,
      'dce_uid' => $study_id . ':' . $population_id . ':' . $dce->id,
      'dce' => $dce,
      'attachements' => $themed_attachment
    ));
  }
  return $page_render_dces;
}

/*
 * retrieve Data Collection event
 * */
function mica_client_study_get_dce_table($dataCollectionEvents) {
  $dce_rows = array();
  foreach ($dataCollectionEvents as $key_dce => $dce_wrapper) {
    $dce_description = NULL;
    if (!empty($dce_wrapper->description)) {
      $dce_description = truncate_utf8(mica_client_commons_get_localized_field($dce_wrapper, 'description'), 50, TRUE, TRUE);
    }
    // Hide DCE that are not published on study published page

    $dce_rows[$key_dce] = array(
      'data' => array(
        'label' => l(mica_client_commons_get_localized_field($dce_wrapper, 'name'), '#', array(
          'external' => TRUE,
          'attributes' => array(
            'data-toggle' => 'modal',
            'data-target' => '#' . $dce_wrapper->id
          )
        )),
        'desc' => $dce_description,
        'start_year' => $dce_wrapper->startYear,
        'start_month' => $dce_wrapper->startMonth,
        'end_year' => $dce_wrapper->endYear,
        'end_month' => $dce_wrapper->endMonth,
      )
    );
  }
  return $dce_rows;
}


function mica_client_study_get_attachment_file($study_id, $attachments) {
  return theme('mica_client_study_attachments', array('study_id' => $study_id, 'attachment' => $attachments));
}

/**
 * Get the facets of the variables for this study.
 * @param $dataset_id
 * @return array
 */
function mica_client_study_get_variables($study_id) {
  $dataset_resource = new MicaDatasetResource();
  return $dataset_resource->variables_search(array(
    0 => array(
      'field' => 'studyId',
      'terms' => array($study_id)
    )
  ), 0);
}
