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
 * Obiba Mica variable file
 */

/**
 * Implements hook_variable_info().
 */
function obiba_mica_study_variable_info($options) {
  _obiba_mica_study_content($variable);
  _obiba_mica_harmonization_study_content($variable);
  return $variable;
}

/**
 * Setting Variable content page study.
 */
function _obiba_mica_study_content(&$variable) {
  $variable['study_title_acronym_display'] = array(
    'title' => t('Show acronym/title study order display'),
    'description' => t('Select the order of acronym,  title that will be displayed in the title study page'),
    'type' => 'string',
    'default' => TRUE,
  );
  $variable['study_list_name_acronym_sort'] = array(
    'title' => t('Set the study result sort order'),
    'description' => t('Select the sort type for the study list'),
    'type' => 'string',
    'default' => 'name'
  );

  $variable['study_list_default_order_sort'] = array(
    'title' => t('Set the Study result order'),
    'description' => t('Select the sorted order for the Study list'),
    'type' => 'string',
    'default' => ''
  );

  $variable['study_show_networks'] = array(
    'title' => t('Show networks'),
    'description' => t('If selected the Networks section will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['study_show_datasets'] = array(
    'title' => t('Show datasets'),
    'description' => t('If selected the Datasets section will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['study_show_coverage_graphs'] = array(
    'title' => t('Show classification graphics'),
    'description' => t('If selected the variable classification graphics will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_list_show_search_form'] = array(
    'title' => t('Show the rapid search/sort form in the study list page'),
    'description' => t('If selected the rapid search/sort form will be displayed in the study list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_list_show_studies_count_caption'] = array(
    'title' => t('Show the studies count caption in the study list page'),
    'description' => t('If selected the studies count caption will be displayed in the study list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['study_list_show_search_button'] = array(
    'title' => t('Show the search studies button in the study list page'),
    'description' => t('If selected the search studies button will be displayed in the study list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );

  $variable['study_detail_show_search_button'] = array(
    'title' => t('Show the search variables button in the study page'),
    'description' => t('If selected the search variables button will be displayed in the study page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_list_show_study_sup_info'] = array(
    'title' => t('Show supplementary details study in the study list page'),
    'description' => t('If selected the supplementary details study badges will be displayed in the study list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['studies_list_show_trimmed_description_study'] = array(
    'title' => t("Show trimmed description details study, with 'Read more' link in the study list page"),
    'description' => t("If selected the description details study will be displayed in the study list page with a 'Read more' link"),
    'type' => 'boolean',
    'default' => TRUE,
  );

}

/**
 * Setting Variable content page study.
 */
function _obiba_mica_harmonization_study_content(&$variable) {
  $variable['harmo_study_title_acronym_display'] = array(
    'title' => t('Show acronym/title study order display'),
    'description' => t('Select the order of acronym,  title that will be displayed in the title study page'),
    'type' => 'string',
    'default' => TRUE,
  );
  $variable['harmo_study_show_networks'] = array(
    'title' => t('Show networks'),
    'description' => t('If selected the Networks section will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['harmo_study_show_datasets'] = array(
    'title' => t('Show datasets'),
    'description' => t('If selected the Datasets section will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['harmo_study_show_coverage_graphs'] = array(
    'title' => t('Show classification graphics'),
    'description' => t('If selected the variable classification graphics will be displayed'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['harmo_study_target_number_participant_label'] = array(
    'title' => t('Target Number of Participants label'),
    'description' => t('Set the label for target number of participants'),
    'type' => 'string',
    'default' => t('Target Number of Participants')
  );
  $variable['harmo_study_detail_show_search_button'] = array(
    'title' => t('Show the search variables button in the study page'),
    'description' => t('If selected the search variables button will be displayed in the study page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['harmo_studies_list_show_study_sup_info'] = array(
    'title' => t('Show supplementary details study in the study list page'),
    'description' => t('If selected the supplementary details study badges will be displayed in the study list page'),
    'type' => 'boolean',
    'default' => TRUE,
  );
  $variable['harmo_studies_list_show_trimmed_description_study'] = array(
    'title' => t("Show trimmed description details study, with 'Read more' link in the study list page"),
    'description' => t("If selected the description details study will be displayed in the study list page with a 'Read more' link"),
    'type' => 'boolean',
    'default' => TRUE,
  );

}