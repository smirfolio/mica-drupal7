<?php
/**
 * @file
 * Obiba Mica Graphic file
 */

/**
 * Form builder.
 */
function obiba_mica_graphic_settings_form($form, &$form_state) {
  $form['obiba_mica_graphic'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Obiba Mica Graphic module display settings'),
    '#collapsible' => FALSE,
  );

  $form['obiba_mica_graphic']['graphic_labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graphic module display labels'),
    '#collapsible' => FALSE,
  );

  $form['obiba_mica_graphic']['graphic_labels']['labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graphic module labels'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('graphic_label');
  $form['obiba_mica_graphic']['graphic_labels']['labels']['graphic_label'] = array(
    '#type' => 'textfield',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('graphic_label'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

  obiba_mica_graphic_settings_form_display_block($form);
  obiba_mica_graphic_settings_form_display_content($form);

  return system_settings_form($form);
}

function obiba_mica_graphic_settings_form_display_block(&$form) {
  $form['obiba_mica_graphic']['graphic_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graphic module display'),
    '#collapsible' => FALSE,
  );

  $form['obiba_mica_graphic']['graphic_display']['blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graphic module display in blocks'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('graphics_blocks');
  $form['obiba_mica_graphic']['graphic_display']['blocks']['graphics_blocks'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('graphics_blocks'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );
  $all = array('NaN' => t('ALL'));
  $retrieved_networks = obiba_mica_graphic_get_networks_id();

  $networks_options = !empty($retrieved_networks) ? array_merge($all, $retrieved_networks) : $all;
  $info = variable_get_info('graphics_blocks_networks');
  $form['obiba_mica_graphic']['graphic_display']['blocks']['graphics_blocks_networks'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => $info['title'],
    '#options' => $networks_options,
    '#default_value' => variable_get_value('graphics_blocks_networks'),
    '#description' => $info['description'],
  );

  $info = variable_get_info('graphics_blocks_aggregations');

  $form['obiba_mica_graphic']['graphic_display']['blocks']['graphics_blocks_aggregations'] = array(
    '#type' => 'checkboxes',
    '#multiple' => TRUE,
    '#title' => $info['title'],
    '#options' => obiba_mica_graphic_get_aggregations(),
    '#description' => $info['description'],
  );
  $graphics_blocks_aggregations = variable_get_value('graphics_blocks_aggregations');
  if (!empty($graphics_blocks_aggregations) && $graphics_blocks_aggregations != 'none') {
    $form['obiba_mica_graphic']['graphic_display']['blocks']['graphics_blocks_aggregations']['#default_value'] =
      variable_get_value('graphics_blocks_aggregations');
  }


  $block_delta_pam = NetworkStatistics::deltaAggregationsMap();
  foreach ($block_delta_pam as $delta => $aggregations) {
    $info = variable_get_info($delta . '_css');
    $form['obiba_mica_graphic']['graphic_display']['blocks'][$delta . '_css'] = array(
      '#type' => 'textfield',
      '#states' => array(
        'visible' => array(
          ':input[name="graphics_blocks_aggregations[' . $aggregations . ']"]' => array('checked' => TRUE),
        ),
      ),
      '#title' => $info['title'],
      '#default_value' => variable_get_value($delta . '_css'),
      '#maxlength' => 255,
      '#description' => $info['description'],
    );
  }

}

function obiba_mica_graphic_settings_form_display_content(&$form) {

  $form['obiba_mica_graphic']['graphic_display']['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graphic module display in Networks pages'),
    '#collapsible' => FALSE,
  );

  $info = variable_get_info('graphics_content');
  $form['obiba_mica_graphic']['graphic_display']['content']['graphics_content'] = array(
    '#type' => 'checkbox',
    '#title' => $info['title'],
    '#default_value' => variable_get_value('graphics_content'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );

}

function obiba_mica_graphic_get_networks_id() {
  $resource = new MicaNetworkResource();
  $networks = $resource->get_networks(NULL, NULL, NULL, 9999, NULL, NULL);
  $networks_options = array();
  $has_summary = $networks->hasSummaries();
  if (!empty($has_summary)) {
    foreach ($networks->getSummaries() as $network_document) {
      $networks_options[$network_document->id] = obiba_mica_commons_get_localized_field($network_document, 'name');
    }
  }
  return $networks_options;
}

function obiba_mica_graphic_get_aggregations() {
  return array(
    'populations-selectionCriteria-countriesIso' => t('Country of residence'),
    'methods-designs' => t('Study design'),
    'populations-dataCollectionEvents-bioSamples' => t('Biological Samples'),
    'access' => t('Access permitted'),
  );
}