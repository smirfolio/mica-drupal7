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
        $page_render_populations .= theme('mica_population_detail', array("context_population_detail" => $population));
    }

    $page_render_populations .= '</article>  </div></section>';
    return $page_render_populations;
}

