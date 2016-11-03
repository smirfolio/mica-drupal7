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
 * @file code for list networks page
 */

function obiba_mica_network_page_list() {
  $context['url'] = 'refresh_list_networks';
  drupal_add_js(drupal_get_path('module', 'obiba_mica_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');

  $node_rendered = obiba_mica_commons_get_translated_node(variable_get_value('networks_page'));

  drupal_set_title($node_rendered['#node']->title);
  $node_rendered['#node']->title = '';

  $list_networks = '';

  $page_number = !empty($_GET['page']) ? $_GET['page'] : NULL;
  $query = !empty($_GET['search-query']) ? $_GET['search-query'] : NULL;
  $sort = !empty($_GET['search-sort']) ? $_GET['search-sort'] : NULL;
  $sort_by = !empty($_GET['search-sort-order']) ? $_GET['search-sort-order'] : NULL;
  $network_limits = !empty($_GET['search-nbr-result']) ? $_GET['search-nbr-result'] : NULL;

  $resource_key = $page_number . $query . $sort . $sort_by . $network_limits;
  $cached_themed_list_network = obiba_mica_commons_get_cache('cached_' . __FUNCTION__ . $resource_key);
  if (!empty($cached_themed_list_network)) {
    return $cached_themed_list_network;
  }
  else {
    $response = obiba_mica_network_get_networks(NULL, $query, $sort, $sort_by, $network_limits);
    $total_networks = empty($response) ? 0 : $response->getTotalHits();
    $network_limits = !empty($network_limits) ? $network_limits : DrupalMicaClientResource::getResponsePageSizeSmall();
    pager_default_initialize($total_networks, $network_limits);
    $pager_output = theme('pager', array('quantity' => $network_limits));
    $summaries = empty($response) ? array() : $response->getSummaries();
    if (!empty($summaries)) {
      foreach ($summaries as $network) {
        if (!empty($network->logo->id)) {
          $logo_url = obiba_mica_commons_safe_expose_server_url($network->id, $network->logo, 'network');
        }
        else {
          $logo_url = NULL;
        }

        $list_networks .= theme('obiba_mica_network-list-page-block', array(
          'network' => $network,
          'logo_url' => $logo_url,
          'digests' => $network
        ));
      }
    }
    else {
      $list_networks = variable_get_value('networks_empty_label');
    }
    $themed_list_networks_page = theme('obiba_mica_network-list', array(
      'form_search' => drupal_get_form('obiba_mica_network_create_form'),
      'node_page' => $node_rendered,
      'total_items' => $total_networks,
      'list_networks' => $list_networks,
      'pager_wrap' => $pager_output
    ));
    if ($total_networks !== 0) {
      obiba_mica_commons_set_cache('cached_' . __FUNCTION__ . $resource_key, $themed_list_networks_page);
    }
    return $themed_list_networks_page;
  }
}

function obiba_mica_network_get_networks($study_id, $query = NULL, $sort = NULL, $sort_by = NULL, $network_limits = NULL) {
  $from = 0;
  $study_resource = new DrupalMicaNetworkResource();
  $size_response = !empty($network_limits) ? $network_limits : DrupalMicaClientResource::getResponsePageSizeSmall();
  if (!empty($_GET['page'])) {
    $from = $study_resource->paginationListSearchParameters($_GET['page'], 'networks', $size_response);
  }
  $networks = $study_resource->getNetworks($study_id, $query, $from, $size_response, $sort, $sort_by);
  return $networks;
}

function obiba_mica_network_create_form() {
  $context =
    array(
      'options' => array(),
      'default_sort' => 'acronym',
      'default_sort_order' => 'desc'
    );

  return obiba_mica_commons_create_search_form($context);
}

function obiba_mica_network_networks_table($networks_result) {
  $rows = array();
  $total = $networks_result->getTotalHits();

  if ($total > 0) {
    $rows = obiba_mica_network_networks_table_rows($networks_result->getSummaries());
  }
  $headers = obiba_mica_network_networks_table_headers();
  $per_page = 20;

  if (empty($total)) {
    return NULL;
  }

  $args = array(
    'quantity' => $total,
    'element' => DrupalMicaNetworkResource::PAGINATE_NETWORKS
  );
  $current_page = pager_default_initialize($total, $per_page, DrupalMicaNetworkResource::PAGINATE_NETWORKS);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return $themed_network_table = theme(
      'table',
      array(
        'header' => $headers,
        'rows' => empty($chunks) ? array() : $chunks[$current_page],
        'empty' => variable_get_value('networks_empty_label')
      )
    ) . theme('pager', $args);
}

function obiba_mica_network_networks_table_rows($networks) {
  $rows = array();

  if (!empty($networks)) {
    foreach ($networks as $network) {
      $stats = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
      $study_count = MicaClientAnchorHelper::networkStudies($stats->studies, $network->id);
      $rows[] = array(
        MicaClientAnchorHelper::network($network),
        obiba_mica_commons_get_localized_field($network, 'name'),
        $study_count,
      );
    }
  }
  return $rows;
}

function obiba_mica_network_retrieve_networks($query, $sort = NULL, $sort_order = NULL) {
  $list_networks = obiba_mica_network_get_networks(NULL, $query, $sort, $sort_order);
  $list_networks_rendered = '';
  foreach ($list_networks->getSummaries() as $network) {
    $list_networks_rendered .= theme('obiba_mica_network-list-page-block', array(
      'network' => $network
    ));
  }
  $data['list'] = $list_networks_rendered;
  $data['total'] = $list_networks->total;
  drupal_json_output($data);
}

function obiba_mica_network_networks_table_headers() {
  return array(
    t('Acronym'),
    t('Name'),
    t('Studies'),
  );
}




