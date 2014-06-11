<?php
/**
 * @file
 * Mica studies file
 */

function mica_study_page_detail($study_id)
{
    $page_render_study = NULL;
    $query = new QueryDto();
    $param = 'study/' . $study_id;
    $StudyDto = $query->get_detail($param, '\obiba\mica\StudyDto');
    //dpm($StudyDto);
    drupal_set_title(mica_commons_get_localized_field($StudyDto, 'name'));

    $output = $StudyDto;

    return mica_study_get_study_detail($output) . mica_study_get_timeline_detail($output) . mica_study_get_populations_detail($output);
}

/*
 * Format Study detail
 * */
function mica_study_get_study_detail($study_detail)
{
    return theme('mica_study_detail', array("context_detail" => $study_detail));
}

/**
 * Implements hook_library().
 */
function mica_study_library() {
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
function mica_study_get_timeline_detail($study_detail)
{
    $codec = new \DrSlump\Protobuf\Codec\Json();
    $study_json = $study_detail->serialize($codec);
    $page_render_timeline = null;
    $page_render_timeline .= '
<section> <h2 class="block-title">' . t("Study Timeline") . '</h2><div> <article>
        ';
    $page_render_timeline .= '<div class="timeline-help"> ' . t('
    Each colour in the timeline graph below represents a separate Study Population, while each segment in the graph
    represents a separate Data Collection Event. Clicking on a segment gives more detailed
     information on a Data Collection Event.') . ' </div>';
    drupal_add_library('mica_study', 'micatimeline');
    $page_render_timeline .= '<div id="vis" style="width=100%"></div>';

    drupal_add_js(drupal_get_path('module', 'mica_study') . '/js/example.js', 'file');
    drupal_add_js(array('mica_study' => array('study_json' => $study_json)), 'setting');

    $page_render_timeline .= '</article>  </div></section>';

    return $page_render_timeline;
}

/*
 * Format populations schema
 * */

function mica_study_get_populations_detail($study_detail)
{
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
                <a href="">' . mica_commons_get_localized_field($population, 'name') . '</a>
            </h2>
        </header>';
        if (!empty($population->dataCollectionEvents)) {
            $dce_rows = mica_study_get_dce_table($population->dataCollectionEvents);
            uasort($dce_rows, 'mica_study_sort_dce');
            _mica_commons_normalize_rows($dce_rows);

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
        }
        $page_render_populations .= theme('mica_population_detail', array("context_population_detail" => $population));
    }
    $page_render_populations .= '</article>  </div></section>';
    return $page_render_populations;
}

/*
 * retrieve Data Collection event
 * */
function mica_study_get_dce_table($dataCollectionEvents)
{
    $dce_rows = array();
    foreach ($dataCollectionEvents as $key_dce => $dce_wrapper) {
        $dce_description = NULL;
        if (!empty($dce_wrapper->description)) {
            $dce_description = truncate_utf8(mica_commons_get_localized_field($dce_wrapper, 'description'), 50, TRUE, TRUE);

        }


        $url = url('#');
        // Hide DCE that are not published on study published page

        $dce_rows[$key_dce] = array(
            'data' => array(
                //'label' => l($dce_wrapper->title->value(), 'node/' . $dce_nid,array(FALSE,FALSE,$langcode)),
                'label' => '<a href="' . $url . '" >' . mica_commons_get_localized_field($dce_wrapper, 'name') . '</a>',
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