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
* Obiba Mica LIsts variable file
*/

/**
* Implements hook_variable_info().
*/
function obiba_mica_lists_variable_info($options) {
  _obiba_mica_lists_study_config($variable);
  return $variable;
}

/**
 * Implements hook_action_info().
 */
function _obiba_mica_lists_study_config(&$variable) {
  $variable['obiba_mica_lists_display_study_facets'] = array(
    'title' => t('Display the study facets properties'),
    'description' => t('If selected the study facets properties will be displayed on the Studies list page'),
    'type' => 'boolean',
    'default' => 0,
  );
  $variable['obiba_mica_lists_display_network_facets'] = array(
    'title' => t('Display the network facets properties'),
    'description' => t('If selected the network facets properties will be displayed on the Networks list page'),
    'type' => 'boolean',
    'default' => 0,
  );
  $variable['obiba_mica_lists_display_datset_facets'] = array(
    'title' => t('Display the Dataset facets properties'),
    'description' => t('If selected the Dataset facets properties will be displayed on the Datasets list page'),
    'type' => 'boolean',
    'default' => 0,
  );
}

