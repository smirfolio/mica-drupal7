<?php

/**
 * @file
 * template.php
 */

/*
 * Hook to override default theme pages
 *  copy '<modules>/obiba_mica_study/templates/'   files in current theme 'templates/' path
 * you can modify default display of listed page by rearrange block field
 *don't forget to clear the theme registry.
 *
 */
function obiba_bootstrap_theme($existing, $type, $theme, $path) {
  $theme_array = array();

  $destination_path = file_exists($path . '/templates/obiba_mica_study-list-page.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_list-page'] = array(
      'template' => 'obiba_mica_study-list-page',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study-list-page-block.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study-list-page-block'] = array(
      'template' => 'obiba_mica_study-list-page-block',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_search'] = array(
      'template' => 'obiba_mica_study_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study_detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_detail'] = array(
      'template' => 'obiba_mica_study_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/mica_population_detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_population_detail'] = array(
      'template' => 'mica_population_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study-dce-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_dce_detail'] = array(
      'template' => 'mica_dce_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study-contact-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['mica_contact_detail'] = array(
      'template' => 'mica_contact_detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study_attachments.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_attachments'] = array(
      'template' => 'obiba_mica_study_attachments',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study_block_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_block_search'] = array(
      'template' => 'obiba_mica_study_block_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_dataset-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_dataset-detail'] = array(
      'template' => 'obiba_mica_dataset-detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_dataset-tables.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_dataset-tables'] = array(
      'template' => 'obiba_mica_dataset-tables',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_dataset-harmonization-table-legend.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_dataset-harmonization-table-legend'] = array(
      'template' => 'obiba_mica_dataset-harmonization-table-legend',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/block--obiba_mica_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['block__obiba_mica_search'] = array(
      'variables' => array('block' => array()),
      'template' => 'block--obiba_mica_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_search.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_search'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_search',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_coverage.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_coverage'] = array(
      'template' => 'obiba_mica_search_coverage',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_coverage_taxonomy.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_coverage_taxonomy'] = array(
      'template' => 'obiba_mica_search_coverage_taxonomy',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_vocabulary_coverage.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_vocabulary_coverage'] = array(
      'template' => 'obiba_mica_search_vocabulary_coverage',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_input_text_range.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_input_text_range'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_input_text_range',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_checkbox_term.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_checkbox_term'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_checkbox_term',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_tab_block.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_tab_block'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_tab_block',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_charts.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_charts'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_charts',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_vocabulary_charts.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_vocabulary_charts'] = array(
      'template' => 'obiba_mica_search_vocabulary_charts',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_network-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_network-detail'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_network-detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_network-list-page-block.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_network-list-page-block'] = array(
      'template' => 'obiba_mica_network-list-page-block',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_network-list.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_network-list'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_network-list',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_fixed_sidebar.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_fixed_sidebar'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_fixed_sidebar',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_study_fixed_sidebar.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_study_fixed_sidebar'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_study_fixed_sidebar',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_variable_harmonization_algorithm.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_variable_harmonization_algorithm'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_variable_harmonization_algorithm',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_variable-detail.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_variable-detail'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_variable-detail',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_cloned_block.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_cloned_block'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_cloned_block',
      'path' => $path . '/templates'
    );
  }

  $destination_path = file_exists($path . '/templates/obiba_mica_search_aggregation_group.tpl.php');
  if (!empty($destination_path)) {
    $theme_array['obiba_mica_search_aggregation_group'] = array(
      'variables' => array('block' => array()),
      'template' => 'obiba_mica_search_aggregation_group',
      'path' => $path . '/templates'
    );
  }

  return $theme_array;

}

/**
 * Implements hook_bootstrap_based_theme().
 */
function obiba_bootstrap_bootstrap_based_theme() {
  return array('obiba_bootstrap' => TRUE);
}

/**
 * Implements hook_preprocess_html().
 */
function obiba_bootstrap_preprocess_html(&$variables) {
  drupal_add_css('https://fonts.googleapis.com/css?family=Open+Sans:400italic,400,300,700,700italic', array('type' => 'external'));
}

function obiba_bootstrap_letters_badge_title() {
  $current_item = explode('/', current_path());
  if (!empty($current_item[0]) && $current_item[0] != 'mica') {
    return NULL;
  }

  if (!empty($current_item[1])) {
    if ((!empty($current_item[2]) && strstr($current_item[2], 'study-')) || strstr($current_item[1], 'study-')) {
      return 'D';
    }
    if ((!empty($current_item[2]) && strstr($current_item[2], 'harmonization-')) ||
      strstr($current_item[1], 'harmonization-')
    ) {
      return 'D-h';
    }
    if (strstr($current_item[1], 'datasets')) {
      return 'D';
    }
    if (strstr($current_item[1], 'coverage')) {
      return 'taxonomy';
    }

    elseif (strstr($current_item[1], 'search')) {
      return 'search-icon';
    }
    else {
      return drupal_strtoupper(drupal_substr($current_item[1], 0, 1));
    }
  }
  else {
    return NULL;
  }
}

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function obiba_bootstrap_preprocess_page(&$variables) {
  //add badge letter
  $first_letter_title = obiba_bootstrap_letters_badge_title();
  if (!empty($first_letter_title)) {
    $variables['classes_array']['title_page'] = $first_letter_title;
  }
  drupal_add_js('misc/jquery.cookie.js', 'file');
  // Add information about the number of sidebars.
  if (!empty($variables['page']['facets']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['facets']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-8 col-lg-9"';
  }
  // Add information about the number of sidebars.
  elseif (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-8 col-lg-9"';
  }

  else {
    $variables['content_column_class'] = ' class="col-sm-12"';
  }
}

/**
 * Overrides theme_menu_local_action().
 */
function obiba_bootstrap_menu_local_action($variables) {
  $link = $variables['element']['#link'];

  $options = isset($link['localized_options']) ? $link['localized_options'] : array();

  // If the title is not HTML, sanitize it.
  if (empty($options['html'])) {
    $link['title'] = check_plain($link['title']);
  }

  $icon = _bootstrap_iconize_button($link['title']);

  // Format the action link.
  $output = '<li>';
  if (isset($link['href'])) {
    // Turn link into a mini-button and colorize based on title.
    if ($class = _bootstrap_colorize_button($link['title'])) {
      if (!isset($options['attributes']['class'])) {
        $options['attributes']['class'] = array();
      }
      $string = is_string($options['attributes']['class']);
      if ($string) {
        $options['attributes']['class'] = explode(' ', $options['attributes']['class']);
      }
      $options['attributes']['class'][] = 'btn';
      //$options['attributes']['class'][] = 'btn-xs';
      $options['attributes']['class'][] = $class;
      if ($string) {
        $options['attributes']['class'] = implode(' ', $options['attributes']['class']);
      }
    }
    // Force HTML so we can add the icon rendering element.
    $options['html'] = TRUE;
    $output .= l($icon . $link['title'], $link['href'], $options);
  }
  else {
    $output .= $icon . $link['title'];
  }
  $output .= "</li>\n";

  return $output;
}

