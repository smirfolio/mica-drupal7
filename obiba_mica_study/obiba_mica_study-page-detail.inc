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

/**
 * @file
 * Mica studies file
 */

if (module_exists('obiba_mica_dataset')) {
  $path_module_dataset = drupal_get_path('module', 'obiba_mica_dataset');
  include_once($path_module_dataset . '/includes/obiba_mica_dataset_resource.inc');
}

function obiba_mica_study_page_detail_coverage($study_id) {

  if (!variable_get_value('study_show_coverage_graphs')) {
    exit;
  }
  $cached_study_coverage = obiba_mica_commons_get_cache(__FUNCTION__ . 'study-coverage-cache-' . $study_id);
  if (!empty($cached_study_coverage)) {
    $study_coverage = $cached_study_coverage;
    if ($study_coverage['coverage'] === 'empty') {
      exit;
    }
  }
  else {
    $coverage = obiba_mica_study_coverage($study_id);

    if (empty($coverage['charts'])) {
      $study_coverage['coverage'] = 'empty';
      obiba_mica_commons_set_cache(__FUNCTION__ . 'study-coverage-cache-' . $study_id, $study_coverage);
      exit;
    }

    $study_coverage = theme('obiba_mica_study_detail_coverage', array('coverage' => $coverage['charts']));
    obiba_mica_commons_set_cache('study-coverage-cache-' . $study_id, $study_coverage);
  }

  print $study_coverage;
}

function obiba_mica_study_page_detail_networks($study_id) {
  if (!variable_get_value('study_show_networks')) {
    exit;
  }
  $cached_networks = obiba_mica_commons_get_cache('cached_' . __FUNCTION__ . $study_id);
  if (!empty($cached_networks)) {
    print $cached_networks;
  }
  else {
    $network_output = (module_exists('obiba_mica_network')) ?
      obiba_mica_network_networks_list($study_id) : NULL;

    if (!empty($network_output)) {
      $themed_study_networks = theme('obiba_mica_study_detail_networks', array('networks' => $network_output));
      obiba_mica_commons_set_cache('cached_' . __FUNCTION__ . $study_id, $themed_study_networks);
      print $themed_study_networks;
    }
  }
}

function obiba_mica_study_page_detail_datasets($study_id, $dataset_name = NULL, $network_id = NULL) {
  if (!variable_get_value('study_show_datasets') && empty($network_id)) {
    exit;
  }
  $cached_datasets = obiba_mica_commons_get_cache('cached_' . __FUNCTION__ . $study_id);
  if (!empty($cached_datasets)) {
    print $cached_datasets;
  }
  else {
    if (!is_null($network_id)) {
      $dataset_output = (module_exists('obiba_mica_dataset')) ? obiba_mica_dataset_get_datasets_network($study_id, $dataset_name, $network_id) : NULL;
    }
    else {
      $dataset_output = (module_exists('obiba_mica_dataset')) ? obiba_mica_dataset_get_datasets_studies($study_id, $dataset_name) : NULL;
    }

    if (!empty($dataset_output)) {
      $themed_datasets = theme('obiba_mica_study_detail_datasets', array('datasets' => $dataset_output));
      obiba_mica_commons_set_cache('cached_' . __FUNCTION__ . $study_id, $themed_datasets);
      print $themed_datasets;
    }
  }
  exit;
}

function obiba_mica_study_page_detail($study_id) {
  obiba_mica_study_load_libs();
  drupal_add_js(drupal_get_path('module', 'obiba_mica_study') . '/js/mica-study-detail.js', 'file');

  $url_param = explode('?', request_uri());
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $parts);
  }
  $page_render_study = NULL;
  $themed_attachment = NULL;
  $flat_study_attachments = NULL;

  $study_resource = new DrupalMicaStudyResource();
  $study_dto = $study_resource->getStudy($study_id);
  if (!empty($study_dto)) {
    $acronym = obiba_mica_commons_get_localized_field($study_dto, 'acronym');
    $name = obiba_mica_commons_get_localized_field($study_dto, 'name');
    $title_order_option = variable_get_value('study_title_acronym_display');
    if (!empty($title_order_option)) {
      if ($title_order_option == 1) {
        drupal_set_title($acronym . ' - ' . $name);
      }
      else {
        if ($title_order_option == 2) {
          drupal_set_title($name);
        }
        else {
          if ($title_order_option == 3) {
            drupal_set_title($acronym);
          }
          else {
            drupal_set_title($name);
          }
        }
      }
    }
    else {
      drupal_set_title($name . ' - ' . $acronym);
    }

    drupal_set_breadcrumb(array(
      l(t('Home'), '<front>'),
      l(t('Studies'), 'mica/studies'),
    ));

    $opal_output = !empty($study_dto->opal) ? obiba_mica_study_get_opal_url($study_dto->opal) : NULL;
    $member_detail_modal = '';
    if (module_exists('obiba_mica_persons') && !empty($study_dto)) {
      if (!empty($study_dto->memberships)) {
        $config_resources = new DrupalMicaConfigResource();
        $members_roles = $config_resources->getSpecificConfigs(array('roles'));
        $ordered_membership = array_map(function ($members_role) use ($study_dto) {
          foreach ($study_dto->memberships as $membership) {
            if ($members_role == $membership->role) {
              return $membership;
            }
          }
        }, $members_roles['roles']);

        foreach ($study_dto->memberships as $membership) {
          if (!empty($membership->members)) {
            $member_detail_modal .= obiba_mica_persons_get_person_detail($membership->role, $study_dto->id, $membership->members);
          }
        }
      }
    }
    if (module_exists('obiba_mica_files')) {
      drupal_add_js(drupal_get_path('module', 'obiba_mica_files') . '/js/obiba_mica_files_attachment_download.js');
      $flat_study_attachments = obiba_mica_files_get_flat_attachments('study', $study_id);
      if (!empty($flat_study_attachments)) {
        $filtered_tree_path = $flat_study_attachments->findNodeFullPath('/study/' . $study_id);
      }
      if (!empty($filtered_tree_path)) {
        $themed_attachment = $flat_study_attachments->themeFolders($filtered_tree_path, DrupalMicaFilesResource::POPULATION, $study_id);
      }
      obiba_mica_app_angular_load_js_resources('obiba_mica_files');
    }
    $cached_populations = obiba_mica_commons_get_cache('populations_detail_cache-' . $study_id);
    if (!empty($cached_populations)) {
      $populations = $cached_populations;
    }
    else {
      $populations = obiba_mica_study_get_populations_detail($study_dto, NULL, NULL, $flat_study_attachments);
      obiba_mica_commons_set_cache('populations_detail_cache-' . $study_id, $populations);
    }

    if (obiba_mica_study_have_timeline($study_dto)) {
      obiba_mica_study_get_timeline_detail($study_dto);
      $timeline_wrapper = '<div id="vis" style="width=100%"></div>';
    }
    $has_coverage =  obiba_mica_commons_has_coverage('study', $study_id);
    $options_study_content = array(
      'showNetwork' => variable_get_value('study_show_networks'),
      'showDatasets' => variable_get_value('study_show_datasets'),
      'showCoverage' => variable_get_value('study_show_coverage_graphs'),
      'haveCoverage' => !empty($has_coverage) ? $has_coverage['has_coverage'] : NULL,
    );
    drupal_add_js(array(
      'study_url' => rawurlencode($study_id),
      'optionsStudyContent' => $options_study_content
    ), 'setting');

    $study_theme_cache = obiba_mica_commons_get_cache('study_theme_cache-' . $study_id);
    if (!empty($study_theme_cache)) {
      return $study_theme_cache;
    }
    else {
      $study_theme = theme('obiba_mica_study_detail',
        array(
          'ordered_membership' => !empty($ordered_membership) ? $ordered_membership : NULL,
          'investigators_modal' => !empty($investigator_detail_modal) ? $investigator_detail_modal : NULL,
          'contacts_modal' => !empty($contact_detail_modal) ? $contact_detail_modal : NULL,
          'members_modal' => !empty($member_detail_modal) ? $member_detail_modal : NULL,
          'study_dto' => $study_dto,
          'attachments' => !empty($themed_attachment) ? $themed_attachment : NULL,
          'file_browser' => theme('obiba_mica_files_browser', array(
            'doc_path' => '/study',
            'doc_id' => $study_id
          )),
          'timeline' => !empty($timeline_wrapper) ? $timeline_wrapper : NULL,
          'populations' => $populations,
          'opal' => $opal_output,
          'group_by' => !empty($parts['group-by']) ? $parts['group-by'] : NULL,
        ));
      obiba_mica_commons_set_cache('study_theme_cache-' . $study_id, $study_theme);
      return $study_theme;
    }

  }
  else {
    drupal_set_title(t('Study not found'));
    return '';
  }
}

function obiba_mica_study_have_timeline($study_dto) {
  if (empty($study_dto->populations)) {
    return FALSE;
  }
  else {
    foreach ($study_dto->populations as $population) {
      if (!empty($population->dataCollectionEvents)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

function obiba_mica_study_get_opal_url($opal_url) {
  return theme('obiba_mica_study_opal', array('opal_url' => $opal_url));
}

/**
 * Implements hook_library().
 */
function obiba_mica_study_library() {
  $libraries = array();
  $version_lib = variable_get('obiba-time-line-version', '1.0');
  $lib_path = libraries_get_path('mica-study-timeline-' . $version_lib);
  // Make sure we have a valid library path before returning library load info.
  if (!empty($lib_path)) {
    $libraries['mica-study-timeline'] = array(
      'title' => 'MicaTimeLine',
      'website' => 'http://obiba.org/',
      'version' => '1.0',
      'js' => array(
        $lib_path . '/dist/d3.min.js' => array(),
        $lib_path . '/dist/mica-study-timeline.min.js' => array()
      ),
      'css' => array(
        $lib_path . '/dist/mica-study-timeline.min.css' => array(),
      )
    );
  }

  return $libraries;
}

/*
 * Format time-line schema
 * */
function obiba_mica_study_get_timeline_detail($study_detail) {
  $study_json = json_encode($study_detail);
  drupal_add_css(drupal_get_path('module', 'obiba_mica_study') . '/css/mica_studies.css', 'file');
  drupal_add_library('obiba_mica_study', 'mica-study-timeline');
  drupal_add_js(drupal_get_path('module', 'obiba_mica_study') . '/js/obiba-mica-study-timeline.js', 'file');
  drupal_add_js(array('obiba_mica_study' => array('study_json' => $study_json)), 'setting');
}

/*
 * Format populations schema
 * */

function obiba_mica_study_get_populations_detail($study_detail, $dce_variables_nbr = NULL, $has_coverage = NULL, $flat_study_attachments = NULL) {
  $page_render_populations = array();
  $population_content_render = array();
  $themed_attachment = NULL;
  if (!empty($study_detail->populations)) {
    foreach ($study_detail->populations as $population) {
      if (!empty($flat_study_attachments) && module_exists('obiba_mica_files')) {
        $path_population_attachment = "/study/$study_detail->id/population/$population->id";
        $filtered_tree_path = $flat_study_attachments->findNodeFullPath($path_population_attachment);
        $themed_attachment = $flat_study_attachments->themeFolders($filtered_tree_path, DrupalMicaFilesResource::DCE, $population->id);
      }
      $dce_uids = array();
      if (!empty($population->dataCollectionEvents)) {
        $dce_rows = obiba_mica_study_get_dce_table($population->dataCollectionEvents, $study_detail->id, $population->id);
        uasort($dce_rows, 'obiba_mica_study_sort_dce');
        obiba_mica_commons_normalize_rows($dce_rows);
        $population_content_render['data'] = $population;
        $population_content_render['dce-tab'] = theme(
          'table',
          array(
            'header' => array(
              t('Name'),
              t('Description'),
              t('Start'),
              t('End')
            ),
            'rows' => $dce_rows,
            'empty' => t('No data collection event found'),
            'sticky' => FALSE,
            'attributes' => array('id' => 'variables_overview')
          )
        );
        $population_content_render['dce-modal'] = obiba_mica_study_get_dce_detail(
          $study_detail->id, $population->id,
          $population->dataCollectionEvents,
          $dce_variables_nbr,
          $has_coverage,
          $flat_study_attachments
        );

        foreach ($population->dataCollectionEvents as $dce) {
          $dce_uids[] = $study_detail->id . ':' . $population->id . ':' . $dce->id;
        }
      }

      $page_render_populations[$population->id] = array(
        'data' => $population_content_render,
        'html' => theme('mica_population_detail', array(
          'population_content' => theme('mica_population_content_detail', array(
            'dce_uids' => $dce_uids,
            'population' => $population,
            'attachments' => !empty($themed_attachment) ? $themed_attachment : NULL,
          )),
          'population' => $population_content_render,
        ))
      );
    }
  }

  return $page_render_populations;
}

/**
 * Create modal DOM for data collection events
 *
 * @param $study_id
 * @param $data_collection_events
 *
 * @return string
 */
function obiba_mica_study_get_dce_detail($study_id, $population_id, $data_collection_events, $dce_variables_nbr = NULL, $has_coverage = NULL, $flat_study_attachments = NULL) {
  $page_render_dces = '';
  $themed_dce_attachment = NULL;
  foreach ($data_collection_events as $dce) {
    if (module_exists('obiba_mica_files')) {
      $path_dce_attachment = "/study/$study_id/population/$population_id/data-collection-event/$dce->id";
      if(!empty($flat_study_attachments)){
      $filtered_dce_tree_path = $flat_study_attachments->findNodeFullPath($path_dce_attachment);
      }
      if ($population_id == 1 && $dce->id == 2) {
//        dvm($filtered_dce_tree_path);
      }
      if(!empty($flat_study_attachments)){
      $themed_dce_attachment = $flat_study_attachments->themeFolders($filtered_dce_tree_path, NULL, $dce->id);
      }
    }
    $page_render_dces .= theme('mica_dce_detail', array(
      'has_coverage' => $has_coverage,
      'dce_variables_nbr' => $dce_variables_nbr,
      'study_id' => $study_id,
      'population_id' => $population_id,
      'dce_uid' => $study_id . ':' . $population_id . ':' . $dce->id,
      'dce_id_target' => MicaClientPathHelpers::normalizeModalTarget($study_id . '-' . $population_id . '-' . $dce->id),
      'dce' => $dce,
      'attachments' => !empty($themed_dce_attachment) ? $themed_dce_attachment : NULL,
    ));
  }
  return $page_render_dces;
}

/*
 * retrieve Data Collection event
 * */
function obiba_mica_study_get_dce_table($data_collection_events, $study_id, $population_id) {
  $dce_rows = array();
  foreach ($data_collection_events as $key_dce => $dce_wrapper) {
    $dce_description = NULL;
    if (!empty($dce_wrapper->model->description)) {
      $dce_description = truncate_utf8(strip_tags(obiba_mica_commons_get_localized_field($dce_wrapper->model, 'description')), 50, TRUE, TRUE);
    }
    // Hide DCE that are not published on study published page

    $dce_rows[$key_dce] = array(
      'data' => array(
        'label' => l(obiba_mica_commons_get_localized_field($dce_wrapper, 'name'), '#', array(
          'external' => TRUE,
          'attributes' => array(
            'data-toggle' => 'modal',
            'data-target' => MicaClientPathHelpers::studyPopulationDceModalTarget($study_id, $population_id, $dce_wrapper)
          )
        )),
        'desc' => $dce_description,
        'start_year' => $dce_wrapper->startYear,
        'start_month' => !empty($dce_wrapper->startMonth) ? $dce_wrapper->startMonth : NULL,
        'end_year' => $dce_wrapper->endYear,
        'end_month' => !empty($dce_wrapper->endMonth) ? $dce_wrapper->endMonth : NULL,
      )
    );
  }
  return $dce_rows;
}

function obiba_mica_study_coverage($study_id) {
  $query = RqlQueryBuilder::study_query_charts($study_id);
  $coverage['charts'] = obiba_mica_graphic_search_query_charts(
    $query,
    array('group-by' => 'dceIds', 'with-facets' => 'false'),
    NULL,
    $study_id
  );

  if (!empty($coverage['charts'])) {
    $coverage['has_coverage'] = TRUE;
    return $coverage;
  }
  else {
    return FALSE;
  }
}