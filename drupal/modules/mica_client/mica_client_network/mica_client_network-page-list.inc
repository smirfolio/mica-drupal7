<?php

include_once('includes/mica_client_network_resource.inc');

function mica_client_network_page_list() {
  $output['title'] = t('Network Catalogue');
  $output['data'] = mica_client_network_networks_list();
  return theme('mica_client_network-list', array("context_detail" => $output));
}

function mica_client_network_get_networks($study_id = NULL) {
  $resource = new MicaNetworkResource();
  return $resource->get_networks($study_id);
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

function mica_client_network_networks_table_headers() {
  return array(
    t('Short Name'),
    t('Name'),
    t('Description'),
  );
}



