<?php

include_once('includes/mica_client_network_resource.inc');

function mica_client_network_page_list() {
  $context['captions'] = array('default' => 'Network', 'plural' => 'Networks');
  $context['url'] = 'refresh_list_networks';
  drupal_add_js(drupal_get_path('module', 'mica_client_commons') . '/js/ajax_getlist_items.js', 'file');
  drupal_add_js(array('context' => $context), 'setting');
  $node_view = node_view(node_load(variable_get('networks_page')));
  $node_view['#node']->title = '';
  $query = NULL;
  $sort = NULL;
  $sort_by = NULL;
  $node_rendred = node_view(node_load(variable_get('networks_page')));
  $node_rendred['#node']->title = '';
  if (!empty($_GET['search-query'])) {
    $query = $_GET['search-query'];
  }
  if (!empty($_GET['search-sort'])) {
    $sort = $_GET['search-sort'];
  }
  if (!empty($_GET['search-sort-order'])) {
    $sort_by = $_GET['search-sort-order'];
  }

  $networks = mica_client_network_get_networks($query, $sort, $sort_by);
  $total_networks = $networks->total;
  // TODO implement search form and pagination

  pager_default_initialize($total_networks, 2);
  $pager_output = theme('pager', array('quantity' => $total_networks));
  $list_networks = theme('mica_client_network-list-page-block', array(
    'list_networks' => $networks,
  ));

  return theme('mica_client_network-list', array(
    "form_search" => drupal_get_form('mica_client_network_create_form'),
    'node_page' => $node_view,
    "total_items" => $total_networks,
    'list_networks' => $list_networks,
    'pager_wrap' => $pager_output
  ));
}

function mica_client_network_get_networks($query, $sort, $sort_by) {
  $from = 0;
  $study_resource = new MicaNetworkResource();
  if (!empty($_GET['page'])) {
    $from = $study_resource->pagination_list_search_parameters($_GET['page'], 'list-networks', 5);
  }
  $networks = $study_resource->get_networks(NULL, $query, $from, NULL, $sort, $sort_by);
  return $networks;
}

function mica_client_network_create_form() {
  $context =
    array(
      'options' => //
        array( //
          'test1' => t('Test1'), //
          'test2' => t('Test2') //
        ) //
    );

  return mica_client_commons_create_search_form($context);
}

function mica_client_network_networks_table($networks_result) {
  $rows = array();
  $total = 0;
  if (!empty($networks_result->total) && $networks_result->total > 0) {
    $total = $networks_result->total;
    $rows = mica_client_network_networks_table_rows($networks_result->networks);
  }
  $headers = mica_client_network_networks_table_headers();
  $per_page = 20;

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
      $name = mica_client_commons_get_localized_field($network, 'name');
      $rows[] = array(
        mica_client_commons_get_localized_field($network, 'acronym'),
        l($name, 'mica/network/' . $network->id . '/' . mica_client_commons_to_slug($name)),
        mica_client_commons_get_localized_field($network, 'description'),
      );
    }
  }
  return $rows;
}

function mica_client_network_retrieve_networks($query, $sort = NULL, $sort_order = NULL) {
  $list_networks = mica_client_network_get_networks($query, $sort, $sort_order);
  dpm($list_networks);
  pager_default_initialize($list_networks->total, 5);
  $pager_output = theme('pager', array('quantity' => 5));
  $list_networks_rendered = theme('mica_client_network-list-page-block', array(
    'list_networks' => $list_networks,
    "pager_wrap" => $pager_output
  ));
  $data['list_studies'] = $list_networks_rendered;
  $data['total'] = $list_networks->total;
  drupal_json_output($data);
}

function mica_client_network_networks_table_headers() {
  return array(
    t('Short Name'),
    t('Name'),
    t('Description'),
  );
}




