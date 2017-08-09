<?php
/**
 * Copyright (c) 2017 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Obiba Mica client module settings UI.
 */

/**
 * Provides settings pages.
 */
function obiba_mica_lists_admin_settings() {
  $form['obiba_mica_lists'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('list Page'),
    '#collapsible' => FALSE,
  );
  _obiba_mica_lists_studies_admin($form);
  _obiba_mica_lists_networks_admin($form);
  return system_settings_form($form);
}

function _obiba_mica_lists_studies_admin(&$form){
  $form['obiba_mica_lists']['obiba_mica_lists_studies'] = array(
    '#type' => 'fieldset',
    '#title' => t('Studies list Page'),
    '#collapsible' => FALSE,
  );
  $form['obiba_mica_lists']['obiba_mica_lists_studies']['obiba_mica_lists_studies_criteria'] = array(
    '#type' => 'fieldset',
    '#title' => t('Studies list Page criteria'),
    '#collapsible' => FALSE,
  );

  $facets = variable_get_info('obiba_mica_lists_display_study_facets');
  $form['obiba_mica_lists']['obiba_mica_lists_studies']['obiba_mica_lists_studies_criteria']['obiba_mica_lists_display_study_facets'] = array(
    '#type' => 'checkbox',
    '#title' => $facets['title'],
    '#default_value' => variable_get_value('obiba_mica_lists_display_study_facets'),
    '#description' => $facets['description'],
  );

//  $form['obiba_mica_lists_studies']['obiba_mica_lists_studies_display'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Studies list Page criteria'),
//    '#collapsible' => FALSE,
//  );
//
//  $facets = variable_get_info('display_study_list_block_display');
//  $form['obiba_mica_lists_studies']['obiba_mica_lists_studies_display']['display_study_list_block_display'] = array(
//    '#type' => 'checkbox',
//    '#title' => $facets['title'],
//    '#default_value' => variable_get_value('display_study_list_block_display'),
//    '#description' => $facets['description'],
//  );

}

function _obiba_mica_lists_networks_admin(&$form){
  $form['obiba_mica_lists']['obiba_mica_lists_networks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Networks list Page'),
    '#collapsible' => FALSE,
  );
  $form['obiba_mica_lists']['obiba_mica_lists_networks']['obiba_mica_lists_networks_criteria'] = array(
    '#type' => 'fieldset',
    '#title' => t('Networks list Page criteria'),
    '#collapsible' => FALSE,
  );
  $facets = variable_get_info('obiba_mica_lists_display_network_facets');
  $form['obiba_mica_lists']['obiba_mica_lists_networks']['obiba_mica_lists_networks_criteria']['obiba_mica_lists_display_network_facets'] = array(
    '#type' => 'checkbox',
    '#title' => $facets['title'],
    '#default_value' => variable_get_value('obiba_mica_lists_display_network_facets'),
    '#description' => $facets['description'],
  );
}