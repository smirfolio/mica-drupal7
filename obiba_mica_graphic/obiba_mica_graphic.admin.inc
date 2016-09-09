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
 * Obiba Mica Graphic file
 */

/**
 * Form builder.
 */
function obiba_mica_graphic_settings_form($form, &$form_state) {
  $form['obiba_mica_graphic'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Obiba Mica display settings'),
    '#collapsible' => FALSE,
  );

  $form['obiba_mica_graphic']['graphic_labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display labels'),
    '#collapsible' => FALSE,
  );

  $form['obiba_mica_graphic']['graphic_labels']['labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Labels'),
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

  $form['obiba_mica_graphic']['graphic_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('display'),
    '#collapsible' => FALSE,
  );

  obiba_mica_graphic_settings_form_general_display($form);
  obiba_mica_graphic_settings_form_display_block($form);
  obiba_mica_graphic_settings_form_display_content($form);

  return system_settings_form($form);
}

function obiba_mica_graphic_settings_form_general_display(&$form) {
  $form['obiba_mica_graphic']['graphic_display']['general_display'] = array(
    '#type' => 'fieldset',
    '#title' => t('General display'),
    '#collapsible' => FALSE,
  );

  $color_fields = obiba_mica_graphic_get_nbr_colors();
  // Draggable form widget
  $info = variable_get_info('mica_graphic_colors');
  $form_obiba_mica_graphic_colors = array(
    '#prefix' => _obiba_mica_admin_search_title_description_draggable_field($info['title'], $info['description']),
    '#tree' => TRUE,
    '#theme' => 'obiba_mica_drag_components',
    '#title' => $info['title'],
    '#required' => FALSE,
    '#description' => $info['description'],
  );

  $wrapped_obiba_mica_graphic_colors_form = _obiba_mica_graphic_admin_get_draggable_colors_form($form_obiba_mica_graphic_colors, $color_fields, 'mica_graphic_colors');
  $form['obiba_mica_graphic']['graphic_display']['general_display']['mica_graphic_colors'] = array_merge($form_obiba_mica_graphic_colors, $wrapped_obiba_mica_graphic_colors_form);


  $info = variable_get_info('pie_slice_text_style_color');
  $form['obiba_mica_graphic']['graphic_display']['general_display']['pie_slice_text_style_color'] = array(
    '#type' => 'textfield',
    '#prefix' => '<div class="col-md-2">',
    '#suffix' => '</div>',
    '#attributes' => array('TYPE' => 'color'),
    '#title' => $info['title'],
    '#default_value' => variable_get_value('pie_slice_text_style_color'),
    '#maxlength' => 255,
    '#description' => $info['description'],
  );


}

/**
 * Action when saving the enabled taxonomies order the default save of the
 * form can't save the status of this widget.
 *
 * @param $form
 * @param $form_state
 */
function _obiba_mica_graphic_submit_draggable(&$form, &$form_state, $variable) {
  $color_form = $form_state['values'][$variable];
  variable_set($variable, $color_form);
}

/**
 * Draggable widget form implementation.
 *
 * @param $draggable_form
 * @param $draggable_items
 * @param $variable_key
 * @return mixed
 */
function _obiba_mica_graphic_admin_get_draggable_colors_form($draggable_form, $draggable_items, $variable_key) {
  $default_value = variable_get_value($variable_key);
  $items = $default_value ? $default_value : $draggable_items;
  foreach ($items as $key_color => $color) {
    $draggable_form[$key_color] =
      array(
        'value' => array(
          '#type' => 'hidden',
          '#title_display' => 'invisible',
          '#default_value' => $key_color,
        ),
        'value_name' => array(
          '#type' => 'textfield',
          '#attributes' => array('TYPE' => 'color'),
          '#default_value' => !empty($default_value[$key_color]) ? $default_value[$key_color]['value_name'] : '#000',
        ),
        'description' => array(
          '#markup' => $draggable_items[$key_color],
        ),
        'weight' => array(
          '#type' => 'weight',
          '#default_value' => !empty($default_value[$key_color]) ? $default_value[$key_color]['weight'] : 0,
          '#title_display' => 'invisible',
          '#attributes' => array('class' => array('taxonomies-item-weight')),
        ),
        'enable' => array(
          '#type' => 'checkbox',
          '#default_value' => !empty($default_value[$key_color]) ? $default_value[$key_color]['enable'] : 0,
          '#title_display' => 'invisible',
        )
      );
  }
  uasort($draggable_form, '_obiba_mica_graphic_colors_options_array_sort');
  return $draggable_form;
}

function obiba_mica_graphic_settings_form_display_block(&$form) {
  $form['obiba_mica_graphic']['graphic_display']['blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display in blocks'),
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
  $block_aggregations = obiba_mica_graphic_get_aggregations();
  $info = variable_get_info('graphics_blocks_aggregations');
  $form_obiba_mica_graphics_blocks_aggregations = array(
    '#prefix' => _obiba_mica_admin_search_title_description_draggable_field($info['title'], $info['description']),
    '#tree' => TRUE,
    '#theme' => 'obiba_mica_table_widget_components',
    '#title' => $info['title'],
    '#required' => FALSE,
    '#description' => $info['description'],
  );
  $wrapped_obiba_mica_graphic_blocks_aggregations_form = _obiba_mica_graphic_admin_get_draggable_blocks_form($form_obiba_mica_graphics_blocks_aggregations, $block_aggregations, 'graphics_blocks_aggregations');
  $form['obiba_mica_graphic']['graphic_display']['blocks']['graphics_blocks_aggregations'] = array_merge($form_obiba_mica_graphics_blocks_aggregations, $wrapped_obiba_mica_graphic_blocks_aggregations_form);
}

/**
 * Draggable widget form implementation.
 *
 * @param $draggable_form
 * @param $draggable_items
 * @param $variable_key
 * @return mixed
 */
function _obiba_mica_graphic_admin_get_draggable_blocks_form($draggable_form, $draggable_items, $variable_key) {
  $default_value = variable_get_value($variable_key);
  $items = $default_value ? $default_value : $draggable_items;
  foreach ($items as $key_aggregation => $aggregation) {
    $draggable_form[$key_aggregation] =
      array(
        'value' => array(
          '#type' => 'hidden',
          '#title_display' => 'invisible',
          '#default_value' => $key_aggregation,
        ),
        'value_name' => array(
          '#type' => 'textfield',
          '#title_display' => 'invisible',
          '#default_value' => !empty($default_value[$key_aggregation]['value_name']) ? $default_value[$key_aggregation]['value_name'] : '',
        ),
        'description' => array(
          '#markup' => $draggable_items[$key_aggregation],
        ),
        'enable' => array(
          '#type' => 'checkbox',
          '#default_value' => !empty($default_value[$key_aggregation]['enable']) ? $default_value[$key_aggregation]['enable'] : 0,
          '#title_display' => 'invisible',
        )
      );
  }
  return $draggable_form;
}

function obiba_mica_graphic_settings_form_display_content(&$form) {

  $form['obiba_mica_graphic']['graphic_display']['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display in Networks pages'),
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
  $networks = $resource->getNetworks(NULL, NULL, NULL, 9999, NULL, NULL);
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
    NetworkStatistics::GEO_NBR_STAT => t('Country of residence'),
    NetworkStatistics::METHODS_DESIGNS => t('Study design'),
    NetworkStatistics::NUMBER_PARTICIPANTS => t('Number of Participants'),
    NetworkStatistics::BIO_SAMPLES => t('Biological Samples'),
  );
}

function obiba_mica_graphic_get_nbr_colors() {
  return array(
    'color1' => t('Color 1'),
    'color2' => t('Color 2'),
    'color3' => t('Color 3'),
    'color4' => t('Color 4'),
    'color5' => t('Color 5'),
    'color6' => t('Color 6'),
    'color7' => t('Color 7'),
    'color8' => t('Color 8'),
    'color9' => t('Color 9'),
    'color10' => t('Color 10'),
  );
}