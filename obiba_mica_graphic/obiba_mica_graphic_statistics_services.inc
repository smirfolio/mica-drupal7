<?php
/**
 * @file
 * Mica networks file
 */

function obiba_mica_graphic_studies_nbr_countries_query($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-geoChart-cache-' . $id_networks);
  if (empty($json_response)) {
    $network_resource = new NetworkStatistics($id_networks);
    $json_response = $network_resource->GeoStudiesQuery('populations-selectionCriteria-countriesIso',
      array(t('Country'), t('Nbr of Studies'))
    );
    cache_set('data-studies-nb-geoChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }
}

function obiba_mica_graphic_recruitment_source_statistics($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-recruitment-source-pieChart-cache-' . $id_networks);
  if (empty($json_response)) {
    $chart_data = array();
    $network_resources = new NetworkStatistics($id_networks);
    $json_response = $network_resources->queryForPieChart($chart_data,
      'populations-recruitment-dataSources',
      array(t('Recruitment Target'), t('% of studies')));

    $json_response['TableData'] = $network_resources->getTableData($chart_data, TRUE);
    cache_set('data-studies-nb-recruitment-source-pieChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }
}

function obiba_mica_graphic_study_design_statistics($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-study-design-pieChart-cache-' . $id_networks);

  if (empty($json_response)) {
    $chart_data = array();
    $network_resources = new NetworkStatistics($id_networks);
    $json_response = $network_resources->queryForPieChart($chart_data,
      'methods-designs',
      array(t('Study design'), t('Number of studies')));

    $json_response['TableData'] = $network_resources->getTableData($chart_data);
    cache_set('data-studies-nb-study-design-pieChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }

}

function obiba_mica_graphic_biological_samples_statistics($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-biological-samples-pieChart-cache-' . $id_networks);

  if (empty($json_response)) {
    $chart_data = array();
    $network_resources = new NetworkStatistics($id_networks);
    $json_response = $network_resources->queryForPieChart($chart_data,
      'populations-dataCollectionEvents-bioSamples',
      array(t('Collected biological samples'), t('Number of studies')));

    $json_response['TableData'] = $network_resources->getTableData($chart_data);
    cache_set('data-studies-nb-biological-samples-pieChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }

}

function obiba_mica_graphic_data_access_statistics($id_networks = NULL) {
  $json_response = cache_get('data-studies-nb-data-access-pieChart-cache-' . $id_networks);

  if (empty($json_response)) {
    $chart_data = array();
    $network_resources = new NetworkStatistics($id_networks);
    $json_response = $network_resources->queryForPieChart($chart_data,
      'access',
      array(t('Access given to'), t('Number of studies'))
    );

    $json_response['TableData'] = $network_resources->getTableData($chart_data);
    cache_set('data-studies-nb-data-access-pieChart-cache-' . $id_networks . '-', $json_response, 'cache', time() + (60 * 60));
    drupal_json_output($json_response);
  }
  else {
    drupal_json_output($json_response);
  }
}
