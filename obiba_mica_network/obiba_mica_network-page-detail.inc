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
  $themed_attachment = NULL;
  $network_resource = new MicaNetworkResource();
  $network_dto = $network_resource->getNetwork($network_id);

  $studies_statistics = '';
  if (!empty($network_dto)) {

    if (!empty($network_dto->networkSummaries)) {
      $ids = array_map(function ($summary) {
        return $summary->id;
      }, $network_dto->networkSummaries);
      obiba_mica_network_networks_datatable_init($network_dto->networkSummaries, $network_resource->get_network_details($ids));
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
      if (!empty($network_dto->networkSummaries)) {
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
        !empty($network_dto->investigators) ? $network_dto->investigators : NULL);
    $contact_detail_modal = obiba_mica_persons_get_person_detail('contact',
      $network_dto->id, !empty($network_dto->contacts) ? $network_dto->contacts : NULL);

    if (module_exists('obiba_mica_files')) {
      drupal_add_js(drupal_get_path('module', 'obiba_mica_files') .
        '/js/obiba_mica_files_attachment_download.js');
      $flat_network_attachments =
        obiba_mica_files_get_flat_attachments('network', $network_id);
      if (!empty($flat_network_attachments)) {
        $filtered_tree_path =
          $flat_network_attachments->findNodeFullPath('/network/' . $network_id);
      }
      if (!empty($filtered_tree_path)) {
        $themed_attachment =
          $flat_network_attachments->themeFolders($filtered_tree_path,
            NULL, $network_id);
      }
      obiba_mica_app_angular_load_js_resources('obiba_mica_files');
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
      'networkUrl' => rawurlencode($network_id),
      'study_ids' => $network_dto->studyIds
    ), 'setting');
    $network_theme = obiba_mica_commons_get_cache('network_theme_cache-' . $network_id);
    if (!empty($network_theme)) {
      return $network_theme;
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
        'file_browser' => theme('obiba_mica_files_browser', array(
          'doc_path' => '/network',
          'doc_id' => $network_id
        )),
        'statistics' => $studies_statistics,
      ));
      obiba_mica_commons_set_cache('network_theme_cache-' . $network_id, $network_theme);
      return $network_theme;
    }
  }
  else {
    drupal_set_title(t('Network not found'));
    return '';
  }
}

function obiba_mica_network_page_detail_datasets($network_id) {
  if (!variable_get_value('study_show_datasets')) {
    exit;
  }

  $cached_datasets = obiba_mica_commons_get_cache('network-datasets-cache-' . $network_id);

  if (!empty($cached_datasets)) {
    $themed_datasets = $cached_datasets;
  }
  else {
    $dataset_output = (module_exists('obiba_mica_dataset')) ? obiba_mica_dataset_get_datasets_network(NULL, 'HarmonizationDataset', $network_id) : NULL;
    $themed_datasets = empty($dataset_output) ? 'empty' : theme('obiba_mica_study_detail_datasets', array('datasets' => $dataset_output));
    obiba_mica_commons_set_cache('network-datasets-cache-' . $network_id, $themed_datasets);
  }

  if ($themed_datasets !== 'empty') {
    print $themed_datasets;
  }
}

function obiba_mica_network_statistics_angular_options($networks_id) {
    obiba_mica_graphic_local_graphics_options(
    array('entityType' => 'network',
          'entityIds' => implode(',', $networks_id)));
  return theme('obiba_mica_network-charts');
}

function obiba_mica_network_page_detail_coverage($study_ids_string) {
  $cached_coverage = obiba_mica_commons_get_cache('network-cache-' . $study_ids_string);
  if (!empty($cached_coverage)) {
    $themed_coverage = $cached_coverage;
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
function obiba_mica_network_networks_datatable_init($network_summaries, $network_details) {
  if (drupal_get_library('obiba_mica_dataset', 'datatables')) {
    drupal_add_library('obiba_mica_dataset', 'datatables');
  }
  else {
    obiba_mica_commons_datatables_external_source();
  }

  drupal_add_js(drupal_get_path('module', 'obiba_mica_network') . '/js/obiba_mica_network_networks_datatable_init.js', 'file');

  drupal_add_js(array(
    'table_network_networks_headers' => obiba_mica_network_network_table_headers(),
    'table_network_networks_data' => obiba_mica_network_links_table_rows($network_summaries, $network_details)
  ), 'setting');
}

function obiba_mica_network_links_table_rows($network_summaries, $network_details) {
  $rows = array();

  /**
   * Helper closure to calculate total number of participants and a list of all countries
   *
   * @param $network
   * @return array
   */
  $get_participants_countries = function ($network) {
    if (empty($network->studySummaries)) {
      return array('targets' => 0, 'countries' => '');
    }
    $targets = 0;
    foreach ($network->studySummaries as $summary) {
      $targets += empty($summary->targetNumber) ? 0 : $summary->targetNumber->number;
      if (!empty($summary->countries)) {
        $countries[] = implode(',', $summary->countries);
      }
    };

    return array(
      'targets' => obiba_mica_commons_format_number($targets),
      'countries' => obiba_mica_commons_countries(array_unique($countries))
    );
  };

  if (!empty($network_details) && !empty($network_details->networks)) {
    foreach ($network_details->networks as $network) {
      $extra = $get_participants_countries($network);
      $study_variables = empty($network->{'obiba.mica.CountStatsDto.networkCountStats'}->studyVariables) ? '-' :
        MicaClientAnchorHelper::networkVariables(obiba_mica_commons_format_number($network->{'obiba.mica.CountStatsDto.networkCountStats'}->studyVariables),
          $network->id, array(), 'dataset(in(Mica_dataset.className,StudyDataset))');
      $dataschema_variables = empty($network->{'obiba.mica.CountStatsDto.networkCountStats'}->dataschemaVariables) ? '-' :
        MicaClientAnchorHelper::networkVariables(obiba_mica_commons_format_number($network->{'obiba.mica.CountStatsDto.networkCountStats'}->dataschemaVariables),
          $network->id, array(), 'dataset(in(Mica_dataset.className,HarmonizationDataset))');
      $rows[] = array(
        MicaClientAnchorHelper::network($network),
        obiba_mica_commons_get_localized_field($network, 'name'),
        $network->{'obiba.mica.CountStatsDto.networkCountStats'}->studies,
        $extra['targets'],
        $extra['countries'],
        $study_variables,
        $dataschema_variables
      );
    }
  }

  $unpublished_networks = array_filter($network_summaries, function ($summary) {
    return !$summary->published;
  });

  if (!empty($unpublished_networks)) {
    foreach ($unpublished_networks as $unpublished_network) {
      $rows[] = array(
        obiba_mica_commons_get_localized_field($unpublished_network, 'acronym'),
        t(obiba_mica_commons_get_localized_field($unpublished_network, 'name')),
        '-',
        '-',
        '-',
        '-',
        '-'
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
      $acronym = obiba_mica_commons_get_localized_field($study_summary, 'acronym');
      $name = obiba_mica_commons_get_localized_field($study_summary, 'name');
      $rows[] = array(
        $study_summary->published ? MicaClientAnchorHelper::study($study_summary) : $acronym,
        $name,
        implode(', ', isset($study_summary->designs) ? obiba_mica_commons_clean_string($study_summary->designs) : array()),
        !empty($study_summary->targetNumber->noLimit) && $study_summary->targetNumber->noLimit === TRUE ? t('No Limit') :
          (isset($study_summary->targetNumber->number) ? obiba_mica_commons_format_number($study_summary->targetNumber->number) : NULL),
        isset($study_summary->countries) ? obiba_mica_commons_countries($study_summary->countries) : NULL,
        empty($study_summary->variables)
          ? '-' : MicaClientAnchorHelper::studyVariables(obiba_mica_commons_format_number($study_summary->variables), $study_summary->id, FALSE, $query)
      );
    }
  }

  return $rows;
}

function obiba_mica_network_study_table_headers() {
  return array(
    array("title" => t('Acronym'), 'width' => '15%'),
    array("title" => t('Name'), 'width' => '40%'),
    array("title" => t('Study Design'), 'width' => '15%'),
    array("title" => t('Participants'), 'width' => '10%'),
    array("title" => t('Country'), 'width' => '15%'),
    array("title" => t('Variables'), 'width' => '5%')
  );
}

function obiba_mica_network_network_table_headers() {
  return array(
    array("title" => t('Acronym'), 'width' => '15%'),
    array("title" => t('Name'), 'width' => '40%'),
    array("title" => t('Studies'), 'width' => '5%'),
    array("title" => t('Participants'), 'width' => '10%'),
    array("title" => t('Countries'), 'width' => '20%'),
    array("title" => t('Study Variables'), 'width' => '5%'),
    array("title" => t('DataSchema Variables'), 'width' => '5%')
  );
}

function obiba_mica_network_coverage($study_ids) {
  $query = RqlQueryBuilder::network_query_charts($study_ids);
  return obiba_mica_graphic_search_query_charts(
    $query,
    array('group-by' => 'studyIds', 'with-facets' => 'false'),
    NULL,
    $study_ids
  );
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
