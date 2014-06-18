<?php
/**
 * @file
 * Mica studies file
 */

function mica_client_study_page_detail($study_id) {
  $page_render_study = NULL;
  $study_resource = new MicaStudyResource();
  $StudyDto = $study_resource->study($study_id);
  drupal_set_title(mica_client_commons_get_localized_field($StudyDto, 'name'));

  $output = $StudyDto;

  return mica_client_study_get_study_detail($output) . mica_client_study_get_timeline_detail($output) . mica_client_study_get_populations_detail($output);
}

/*
 * Format Study detail
 * */
function mica_client_study_get_study_detail($study_detail) {
  return theme('mica_client_study_detail', array("context_detail" => $study_detail));
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
        $lib_path . '/css/mica_studies.css' => array(),
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
  $codec = new \DrSlump\Protobuf\Codec\Json();
  $study_json = $study_detail->serialize($codec);
  $page_render_timeline = NULL;
  $page_render_timeline .= '
<section> <h2 class="block-title">' . t("Study Timeline") . '</h2><div> <article>
        ';
  $page_render_timeline .= '<div class="timeline-help"> ' . t('
    Each colour in the timeline graph below represents a separate Study Population, while each segment in the graph
    represents a separate Data Collection Event. Clicking on a segment gives more detailed
     information on a Data Collection Event.') . ' </div>';


  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/mica_studies.css', 'file');
  drupal_add_css(drupal_get_path('module', 'mica_client_study') . '/css/timeline.css', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/d3.min.js', 'file');
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/mica-study-timeline.js', 'file');
  $page_render_timeline .= '<div id="vis" style="width=100%"></div>';
  drupal_add_js(drupal_get_path('module', 'mica_client_study') . '/js/example.js', 'file');
  drupal_add_js(array('mica_client_study' => array('study_json' => $study_json)), 'setting');

  $page_render_timeline .= '</article>  </div></section>';

  return $page_render_timeline;
}

/*
 * Format populations schema
 * */

function mica_client_study_get_populations_detail($study_detail) {
  $page_render_populations = NULL;
  $page_render_populations .= '
<section> <h2 class="block-title">' . t("Populations") . '</h2><div> <article>
        ';
  foreach ($study_detail->populations as $population) {
    $page_render_populations .= '<header>
            <h2>
             <svg width="25" height="25">
                    <rect width="20" height="20" x="2" y="2" rx="5" ry="5" style="fill:#9a3034;"> </rect>
             </svg>
                <a href="">' . mica_client_commons_get_localized_field($population, 'name') . '</a>
            </h2>
        </header>';
    if (!empty($population->dataCollectionEvents)) {
      $dce_rows = mica_client_study_get_dce_table($population->dataCollectionEvents);
      uasort($dce_rows, 'mica_client_study_sort_dce');
      _mica_client_commons_normalize_rows($dce_rows);

      $population['dce-tab'] = theme(
        'table',
        array(
          'header' => array(t('Name'), t('Description'), t('Start'), t('End')),
          'rows' => $dce_rows,
          'empty' => t('No data found'),
          'sticky' => FALSE,
          'attributes' => array('id' => 'variables_overview')
        )
      );

      $population['dce-modal'] = mica_client_study_get_dce_detail($study_detail->id, $population->dataCollectionEvents);
    }
    $page_render_populations .= theme('mica_population_detail', array("context_population_detail" => $population));
  }
  $page_render_populations .= '</article>  </div></section>';
  return $page_render_populations;
}

/**
 * Create modal DOM for data collection events
 * @param $study_id
 * @param $dataCollectionEvents
 * @return string
 */
function mica_client_study_get_dce_detail($study_id, $dataCollectionEvents) {
  $page_render_dces = '';
  foreach ($dataCollectionEvents as $key_dce => $dce_wrapper) {
    $page_render_dces .= theme('mica_dce_detail', array('study_id' => $study_id, 'context_detail' => $dce_wrapper));
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

    $url = url('#');
    // Hide DCE that are not published on study published page

    $dce_rows[$key_dce] = array(
      'data' => array(
        'label' => sprintf("<a href=\"#\" data-toggle=\"modal\" data-target=\"#%s\">%s</a>",
          $dce_wrapper->id,
          mica_client_commons_get_localized_field($dce_wrapper, 'name')),
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