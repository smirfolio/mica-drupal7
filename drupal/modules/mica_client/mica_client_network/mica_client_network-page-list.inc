<?php

include_once('includes/mica_client_network_resource.inc');

function mica_client_network_page_list() {
  $context['url'] = 'refresh_list_networks';
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');

  $node_view = node_view(node_load(variable_get('networks_page')));
  $node_view['#node']->title = '';
  $query = NULL;
  $sort = NULL;
  $sort_by = NULL;
  $list_networks = '';
  if (!empty($_GET['search-query'])) {
    $query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $sort_by = $_GET['search-sort-order'];
  }

  $response = mica_client_network_get_networks(NULL, $query, $sort, $sort_by);
  $total_networks = empty($response) ? 0 : $response->getTotalHits();


  pager_default_initialize($total_networks, MicaClient::SIZE_RESPONSE_SM);
  $pager_output = theme('pager', array('quantity' => MicaClient::SIZE_RESPONSE_SM));
  $summaries = empty($response) ? array() : $response->getSummaries();
  if (!empty($summaries)) {
    foreach ($summaries as $network) {
      if (!empty($network->logo->id)) {
        $logo_url = mica_client_commons_safe_expose_server_url($network->id, $network->logo, 'network');
      }
      else {
        $logo_url = NULL;
      }

      $list_networks .= theme('mica_client_network-list-page-block', array(
        'network' => $network,
        'logo_url' => $logo_url,
        'digests' => $network
      ));
    }
  }
  else {
    $list_networks = t('No network found');
  }

  return theme('mica_client_network-list', array(
    "form_search" => drupal_get_form('mica_client_network_create_form'),
    'node_page' => $node_view,
    "total_items" => $total_networks,
    'list_networks' => $list_networks,
    'pager_wrap' => $pager_output
  ));
}

function mica_client_network_get_networks($study_id, $query = NULL, $sort = NULL, $sort_by = NULL) {
  $from = 0;
  $study_resource = new MicaNetworkResource();
  if (!empty($_GET['page'])) {
    $from = $study_resource->pagination_list_search_parameters($_GET['page'], 'list-networks', MicaClient::SIZE_RESPONSE_SM);
  }
  $networks = $study_resource->get_networks($study_id, $query, $from, MicaClient::SIZE_RESPONSE_SM, $sort, $sort_by);
  if (!empty($networks)) {
    $_SESSION['list-networks']['aggregations']['totalHits'] = $networks->getTotalHits();
  }
  return $networks;
}

function mica_client_network_create_form() {
  $context =
    array(
      'options' => //
        array()
    );

  return mica_client_commons_create_search_form($context);
}

function mica_client_network_networks_table($networks_result) {
  $rows = array();
  $total = $networks_result->getTotalHits();
  if ($total > 0) {
    $rows = mica_client_network_networks_table_rows($networks_result->getSummaries());
  }
  $headers = mica_client_network_networks_table_headers();
  $per_page = 20;

  if (empty($total)) {
    return NULL;
  }

  $args = array('quantity' => $total, 'element' => MicaNetworkResource::PAGINATE_networks);
  $current_page = pager_default_initialize($total, $per_page, MicaNetworkResource::PAGINATE_networks);
  $chunks = array_chunk($rows, $per_page, TRUE);
  return theme(
    'table',
    array(
      'header' => $headers,
      'rows' => empty($chunks) ? array() : $chunks[$current_page],
      'empty' => t('No network found')
    )
  ) . theme('pager', $args);
}

function mica_client_network_networks_table_rows($networks) {
  $rows = array();

  if (!empty($networks)) {
    foreach ($networks as $network) {
      $stats = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
      $study_count = MicaClientAnchorHelper::network_studies($stats->studies, $network->id);
      $name = mica_client_commons_get_localized_field($network, 'name');
      $rows[] = array(
        mica_client_commons_get_localized_field($network, 'acronym'),
        l($name, 'mica/network/' . $network->id . '/' . mica_client_commons_to_slug($name)),
        $study_count,
      );
    }
  }
  return $rows;
}

function mica_client_network_retrieve_networks($query, $sort = NULL, $sort_order = NULL) {
  $list_networks = mica_client_network_get_networks(NULL, $query, $sort, $sort_order);
  $list_networks_rendered = '';
  //dpm($list_networks);
  foreach ($list_networks->getSummaries() as $network) {
    $list_networks_rendered .= theme('mica_client_network-list-page-block', array(
      'network' => $network
    ));
  }
  $data['list'] = $list_networks_rendered;
  $data['total'] = $list_networks->total;
  drupal_json_output($data);
}

function mica_client_network_networks_table_headers() {
  return array(
    t('Short Name'),
    t('Name'),
    t('Studies'),
  );
}




