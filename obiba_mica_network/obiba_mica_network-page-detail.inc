<?php

/*
 * @file code for network detail pages
 * */
include_once('includes/obiba_mica_network_resource.inc');

$path_module_study = drupal_get_path('module', 'obiba_mica_study');
include_once($path_module_study . '/obiba_mica_study-page-detail.inc');

function obiba_mica_network_page_detail($network_id) {
  $url_param = explode('?', request_uri());
  if (!empty($url_param[1])) {
    parse_str($url_param[1], $parts);
  }
  $current_detail_network_cache = array();
  $detail_network_cache = obiba_mica_commons_get_cache('network_detail_cache-' . $network_id);
  if (!empty($detail_network_cache->data['network_dto'])) {
    $network_dto = $detail_network_cache->data['network_dto'];
  }
  else {
    $themed_attachment = NULL;
    $network_resource = new MicaNetworkResource();
    $network_dto = $network_resource->get_network($network_id);
    $current_detail_network_cache['network_dto'] = $network_dto;
    obiba_mica_commons_set_cache('network_detail_cache-' . $network_id, $current_detail_network_cache);
  }
  $studies_statistics = '';
  if (!empty($network_dto)) {

    if (!empty($network_dto->networkSummaries)) {
      obiba_mica_network_networks_datatable_init($network_dto->networkSummaries);
    }

    if (!empty($network_dto->studySummaries)) {
      obiba_mica_network_studies_datatable_init($network_dto->studySummaries, $network_id);
    }

    $acronym = obiba_mica_commons_get_localized_field($network_dto, 'acronym');
    $name = obiba_mica_commons_get_localized_field($network_dto, 'name');
    drupal_set_title($acronym . ' - ' . $name);

    drupal_set_breadcrumb(array(
      l(t('Home'), '<front>'),
      l(t('Networks'), MicaClientPathProvider::NETWORKS),
    ));
    $studies_network_ids = array();
    if (module_exists('obiba_mica_persons') && (!empty($network_dto->studyIds) || !empty($network_dto->networkIds))) {
      if (!empty($network_dto->studyIds)) {
        $studies_network_ids = $network_dto->studyIds;
      }
      if ($network_dto->networkSummaries) {
        foreach ($network_dto->networkSummaries as $network_summary) {
          if (!empty($network_summary->studyIds)) {
            $studies_network_ids = array_merge($studies_network_ids, $network_summary->studyIds);
          }
        }
      }
      $entities_id = array(
        'studiesId' => !empty($studies_network_ids) ? $studies_network_ids : NULL,
        'networksId' => !empty($network_dto->networkIds) ? $network_dto->networkIds : NULL
      );
      obiba_mica_persons_datatable_init($entities_id);

      $associated_people_button = theme('obiba_mica_persons-button');
      $associated_people_modal = theme('obiba_mica_persons-modal',
        array('persons_table' => theme('obiba_mica_persons-table')));
    }

    $investigator_detail_modal =
      obiba_mica_persons_get_person_detail('investigator', $network_dto->id,
        $network_dto->investigators);
    $contact_detail_modal = obiba_mica_persons_get_person_detail('contact',
      $network_dto->id, $network_dto->contacts);

    if (module_exists('obiba_mica_files')) {
      drupal_add_js(drupal_get_path('module', 'obiba_mica_files') .
        '/js/obiba_mica_files_attachment_download.js');
      $flat_network_attachments =
        obiba_mica_files_get_flat_attachments('network', $network_id);
      $filtered_tree_path =
        $flat_network_attachments->findNodeFullPath('/network/' . $network_id);
      if (!empty($filtered_tree_path)) {
        $themed_attachment =
          $flat_network_attachments->themeFolders($filtered_tree_path,
            NULL, $network_id);
      }
    }

    $networks_id = array($network_id);
    if (module_exists('obiba_mica_graphic')) {
      if (!empty($network_dto->studyIds) || !empty($network_dto->networkIds)) {
        $have_graphic_content = variable_get_value('graphics_content');
        if ($have_graphic_content) {
          if (!empty($network_dto->networkIds)) {
            $networks_id = array_merge($networks_id, $network_dto->networkIds);
          }
          obiba_mica_app_angular_load_js_resources('obiba_mica_graphic');

          $studies_statistics = obiba_mica_network_statistics_angular_options($networks_id);
        }
      }
    }
    obiba_mica_network_load_charts_libs();
    drupal_add_js(drupal_get_path('module', 'obiba_mica_network') .
      '/js/mica-network-detail.js', 'file');
    drupal_add_js(array(
      'network_url' => rawurlencode($network_id),
      'study_ids' => $network_dto->studyIds
    ), 'setting');

    if (!empty($detail_network_cache->data['network_theme'])) {
      return $detail_network_cache->data['network_theme'];
    }
    else {
      $network_theme = theme('obiba_mica_network-detail', array(
        'investigators_modal' => !empty($investigator_detail_modal) ?
          $investigator_detail_modal : NULL,
        'contacts_modal' => !empty($contact_detail_modal) ?
          $contact_detail_modal : NULL,
        'network_dto' => $network_dto,
        'has_variables' =>
          _obiba_mica_network_has_variables($network_dto->studySummaries),
        'group_by' => !empty($parts['group-by']) ? $parts['group-by'] : 'studyIds',
        'associated_people_button' => !empty($associated_people_button) ?
          $associated_people_button : NULL,
        'associated_people_modal' => !empty($associated_people_modal) ?
          $associated_people_modal : NULL,
        'attachments' => !empty($themed_attachment) ? $themed_attachment : NULL,
        'statistics' => $studies_statistics,
      ));
      $current_detail_network_cache['network_theme'] = $network_theme;
      obiba_mica_commons_set_cache('network_detail_cache-' . $network_id, $current_detail_network_cache);
      return $network_theme;
    }
  }
  else {
    drupal_set_title(t('Network not found'));
    return '';
  }
}

function obiba_mica_network_statistics_angular_options($networks_id) {
  $colors_options = obiba_mica_graphic_charts_colors_options_settings();
  $study_design_options =
    !empty($colors_options) ?
      array_merge(array('legend' => array('position' => 'none')), $colors_options) :
      array('legend' => array('position' => 'none'));
  $bio_samples_options = !empty($colors_options) ?
    array_merge(array(
      'legend' => array('position' => 'right'),
      'pieSliceTextStyle' => array('color' => variable_get_value('pie_slice_text_style_color'))
    ), $colors_options) :
    array(
      'legend' => array('position' => 'right'),
      'pieSliceTextStyle' => array('color' => variable_get_value('pie_slice_text_style_color'))
    );
  $chart_options = array_merge(
    obiba_mica_graphic_charts_options_settings('geoChartOptions',
      array('graphics.country', 'graphics.nbr-studies'),
      'graphics.geo-chart-title', array('colorAxis' => $colors_options)),
    obiba_mica_graphic_charts_options_settings('studiesDesigns',
      array('graphics.study-design', 'graphics.nbr-studies'),
      'graphics.study-design-chart-title', $study_design_options),
    obiba_mica_graphic_charts_options_settings('biologicalSamples',
      array('graphics.bio-samples', 'graphics.nbr-studies'),
      t('graphics.bio-samples-chart-title'), $bio_samples_options)
  );

  drupal_add_js(array(
    'GraphicChartsOptions' => array(
      'entityType' => 'network',
      'entityIds' => implode(',', $networks_id),
      'ChartsOptions' => $chart_options,
    )
  ),
    'setting');
  return theme('obiba_mica_network-charts');
}

function obiba_mica_network_page_detail_coverage($network_id, $study_ids_string) {
  $cached_coverage = obiba_mica_commons_get_cache('network-cache-' . $study_ids_string);
  if (!empty($cached_coverage)) {
    $themed_coverage = $cached_coverage->data;
    if ($themed_coverage === 'empty') {
      exit;
    }
  }
  else {
    $study_ids = json_decode($study_ids_string);

    if (empty($study_ids)) {
      exit;
    }
    $coverage = obiba_mica_network_coverage($study_ids);
    if (empty($coverage)) {
      $themed_coverage = 'empty';
      obiba_mica_commons_set_cache('network-cache-' . $study_ids_string, $themed_coverage);
      exit;
    }
    $themed_coverage = theme('obiba_mica_network_detail_coverage', array('coverage' => $coverage));
    obiba_mica_commons_set_cache('network-cache-' . $study_ids_string, $themed_coverage);
  }
  print $themed_coverage;
}

/**
 * @param $network_dto
 */
function obiba_mica_network_networks_datatable_init($network_summaries) {
  if (drupal_get_library('obiba_mica_dataset', 'datatables')) {
    drupal_add_library('obiba_mica_dataset', 'datatables');
  }
  else {
    obiba_mica_commons_datatables_external_source();
  }

  drupal_add_js(drupal_get_path('module', 'obiba_mica_network') . '/js/obiba_mica_network_networks_datatable_init.js', 'file');

  drupal_add_js(array(
    'table_network_networks_headers' => array(
      array("title" => t('Acronym')),
      array("title" => t('Name'), 'width' => '90%')
    ),
    'table_network_networks_data' => obiba_mica_network_links_table_rows($network_summaries)
  ), 'setting');
}

function obiba_mica_network_links_table_rows($network_summaries) {
  $rows = array();

  if (!empty($network_summaries)) {
    foreach ($network_summaries as $network_summary) {
      $rows[] = array(
        obiba_mica_commons_get_localized_field($network_summary, 'acronym'),
        $network_summary->getPublished() ? MicaClientAnchorHelper::network($network_summary) : t(obiba_mica_commons_get_localized_field($network_summary, 'name'))
      );
    }
  }

  return $rows;
}

/**
 * @param $network_dto
 */
function obiba_mica_network_studies_datatable_init($study_summaries, $id_network = NULL) {
  if (drupal_get_library('obiba_mica_dataset', 'datatables')) {
    drupal_add_library('obiba_mica_dataset', 'datatables');
  }
  else {
    obiba_mica_commons_datatables_external_source();
  }

  drupal_add_js(drupal_get_path('module', 'obiba_mica_network') . '/js/obiba_mica_network_studies_datatable_init.js', 'file');
  drupal_add_js(array(
    'table_headers' => obiba_mica_network_study_table_headers(),
    'table_data' => obiba_mica_network_study_table_rows($study_summaries, $id_network)
  ), 'setting');
}

function obiba_mica_network_study_table_rows($study_summaries, $id_network = NULL) {
  $rows = array();
  $query = NULL;
  if (!empty($study_summaries)) {
    if (!empty($id_network)) {
      $query = 'network(in(Mica_network.id,' . $id_network . '))';
    }
    foreach ($study_summaries as $study_summary) {
      $name = obiba_mica_commons_get_localized_field($study_summary, 'name');
      $rows[] = array(
        obiba_mica_commons_get_localized_field($study_summary, 'acronym'),
        $study_summary->getPublished() ? MicaClientAnchorHelper::study($study_summary) : t($name),
        implode(', ', obiba_mica_commons_clean_string($study_summary->designs)),
        isset($study_summary->targetNumber->noLimit) ? t('No Limit') :
          isset($study_summary->targetNumber->number) ? obiba_mica_commons_format_number($study_summary->targetNumber->number) : NULL,
        obiba_mica_commons_countries($study_summary->countries),
        empty($study_summary->variables)
          ? '-' : MicaClientAnchorHelper::studyVariables(obiba_mica_commons_format_number($study_summary->variables), $study_summary->id, FALSE, $query)
      );
    }
  }

  return $rows;
}

function obiba_mica_network_study_table_headers() {
  return array(
    array("title" => t('Acronym')),
    array("title" => t('Name'), 'width' => '45%'),
    array("title" => t('Study Design'), 'width' => '20%'),
    array("title" => t('Participants'), 'width' => '15%'),
    array("title" => t('Country')),
    array("title" => t('Variables'))
  );
}

function obiba_mica_network_coverage($study_ids) {
  return obiba_mica_search_query_charts(
    MicaClient::addParameterDtoQueryLink(array(
    'variables' =>
      array('terms' => array('studyIds' => $study_ids))
  )),
    array('group-by' => 'studyIds', 'with-facets' => 'false'),
    NULL,
    $study_ids);
}

function _obiba_mica_network_has_variables($study_summaries) {
  if (!empty($study_summaries)) {
    foreach ($study_summaries as $study_summary) {
      if (!empty($study_summary->variables)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}
