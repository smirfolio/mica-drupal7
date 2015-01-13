<?php

/**
 *
 */
class VariableStatistics {

  private $variable;

  private $variable_stat;

  function __construct($variable, $variable_stat) {
    $this->variable = $variable;
    $this->variable_stat = $variable_stat;
  }

  /**
   * Table of descriptive statistics or frequencies.
   * @return string
   */
  public function as_table() {
    if (!empty($this->variable_stat->statistics)) {
      return $this->as_descriptive_table();
    }
    if (!empty($this->variable_stat->frequencies)) {
      return $this->as_frequencies_table();
    }
    return '<div class="alert alert-info">No statistics found for this variable (nature is "' . strtolower($this->variable_stat->nature) . '").</div>';
  }

  /**
   * Chart of frequencies only.
   * @return bool|string
   */
  public function as_chart() {
    if (!empty($this->variable_stat->statistics)) {
      return FALSE;
      //return $this->as_stacked_bar_chart();
    }
    return $this->as_pie_chart();
  }

  private function as_stacked_bar_chart() {
    if (!empty($this->variable_stat->frequencies)) {
      $aggregations = $this->get_aggregations();

      $labels = array();
      $data = array();
      // add category frequencies first
      if (!empty($this->variable->categories)) {
        foreach ($this->variable->categories as $category) {
          $labels[] = $this->get_category_label($category);
          foreach ($aggregations as $aggregation) {
            if (!empty($aggregation->frequencies)) {
              $header = $this->get_study_table_label($aggregation);
              foreach ($aggregation->frequencies as $frequency) {
                if ($frequency->value == $category->name) {
                  $data[$header][] = $frequency->count;
                  break;
                }
              }
            }
          }
        }
      }
      // look for values that are not categories
      // observed that are missings
      $observed_values = $this->get_observed_values($aggregations, TRUE);
      foreach ($observed_values as $observed) {
        $labels[] = $observed;
        foreach ($aggregations as $aggregation) {
          if (!empty($aggregation->frequencies)) {
            $header = $this->get_study_table_label($aggregation);
            $count = 0;
            foreach ($aggregation->frequencies as $frequency) {
              if ($frequency->value == $observed) {
                $count = $frequency->count;
                break;
              }
            }
            $data[$header][] = $count;
          }
        }
      }
      // observed that are valid, merged into one
      if (!empty($this->variable_stat->statistics)) {
        $labels[] = 'N (' . t('Valid values') . ')';
        foreach ($aggregations as $aggregation) {
          $header = $this->get_study_table_label($aggregation);
          $data[$header][] = empty($aggregation->n) ? 0 : $aggregation->n;
        }
      }

      if (!empty($data)) {
        $to_render = obiba_mica_facet_search_stacked_column_chart($labels, $data, t('Valid and other values frequencies'), NULL, 400, 'none');
        return render($to_render);
      }
      else {
        return FALSE;
      }
    }
    return FALSE;
  }

  /**
   * Combined pie chart.
   * @return bool
   */
  private function as_pie_chart() {
    $aggregation = $this->variable_stat;
    if (empty($aggregation->frequencies)) {
      return FALSE;
    }
    if (empty($aggregation->n)) {
      return FALSE;
    }

    $labels = array();
    $data = array();
    foreach ($aggregation->frequencies as $frequency) {
      // do not include missings and observed (non-categorical) values
      if (!$frequency->missing && $this->is_category($frequency->value)) {
        $labels[] = $this->get_label_from_category_name($frequency->value, FALSE);
        $data[] = $frequency->count;
      }
    }

    if (!empty($data)) {
      $to_render = obiba_mica_facet_search_pie_chart($labels, $data, t('Valid values frequencies'), NULL, 400, 'right');
      return render($to_render);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Mix category name and localized label in one string.
   * @param $category
   * @return null|string|the
   */
  private function get_category_label($category) {
    $label = _obiba_mica_variable_attributes_detail($category, 'label');
    if (empty($label)) {
      $label = $category->name;
    }
    else {
      $label = $category->name . ' (' . $label . ')';
    }
    return $label;
  }

  /**
   * From a value, search for a corresponding category and get its label.
   * @param $value
   * @return null|string|the
   */
  private function get_label_from_category_name($value, $html = TRUE) {
    if ($value == NULL || $value == '' || empty($this->variable->categories)) {
      return $value;
    }

    foreach ($this->variable->categories as $category) {
      if ($value == $category->name) {
        $label = _obiba_mica_variable_attributes_detail($category, 'label');
        return $html ? '<span title="' . $label . '">' . $value . '</span>' : $value . ' (' . $label . ')';
      }
    }
    return $value;
  }

  /**
   * Mix study localized acronym with study table localized name if any in one string.
   * @param $aggregation
   * @return mixed|string
   */
  private function get_study_table_label($aggregation) {
    $study_id = $aggregation->studyTable->studyId;
    $header = _obiba_mica_variable_study_acronym($this->variable, $study_id);
    if (!empty($aggregation->studyTable->name)) {
      $header = $header . '(' . obiba_mica_commons_get_localized_field($aggregation->studyTable, 'name') . ')';
    }
    return $header;
  }

  /**
   * Get the variable statistics as an aggregation list.
   * @return array
   */
  private function get_aggregations() {
    $aggregations = array();
    if (!empty($this->variable_stat->aggregations)) {
      $aggregations = $this->variable_stat->aggregations;
    }
    else {
      array_push($aggregations, $this->variable_stat);
    }
    return $aggregations;
  }

  /**
   * Look for occurrences of values that are not categories.
   * @param $aggregations
   * @param $missing
   * @return array
   */
  private function get_observed_values($aggregations, $missing = NULL) {
    $observed_values = array();
    foreach ($aggregations as $aggregation) {
      if (!empty($aggregation->frequencies)) {
        foreach ($aggregation->frequencies as $frequency) {
          if (!in_array($frequency->value, $observed_values) && !$this->is_category($frequency->value)) {
            if (empty($missing) || $frequency->missing == $missing) {
              $observed_values[] = $frequency->value;
            }
          }
        }
      }
    }
    return $observed_values;
  }

  /**
   * Check if value is a category name of the current variable.
   * @param $value
   * @return bool
   */
  private function is_category($value) {
    if ($value == NULL || $value == '') {
      return FALSE;
    }
    if (empty($this->variable->categories)) {
      return FALSE;
    }

    foreach ($this->variable->categories as $category) {
      if ($value == $category->name) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Table of descriptive statistics.
   * @return string
   */
  private function as_descriptive_table() {
    $rows = array();
    $aggregations = array();

    if ($this->variable->variableType == 'Dataschema') {
      if (!empty($this->variable_stat->aggregations)) {
        $aggregations = $this->variable_stat->aggregations;
      }
    }
    else {
      array_push($aggregations, $this->variable_stat);
    }

    // frequencies of missings
    $missings = array();
    if (!empty($this->variable_stat->frequencies)) {
      foreach ($this->variable_stat->frequencies as $frequency) {
        if ($frequency->value != 'NOT_NULL') {
          array_push($missings, $frequency->value);
        }
      }
    }

    // statistics
    foreach ($aggregations as $aggregation) {
      $row = array();
      if ($this->variable->variableType == 'Dataschema') {
        $study_id = $aggregation->studyTable->studyId;
        $header = l(_obiba_mica_variable_study_acronym($this->variable, $study_id), 'mica/study/' . $study_id);
        if (!empty($aggregation->studyTable->name)) {
          $header = $header . ' ' . obiba_mica_commons_get_localized_field($aggregation->studyTable, 'name');
        }
        $row[] = $header;
      }
      $row = array_merge($row, $this->statistics_to_row($aggregation));
      foreach ($missings as $missing) {
        $count = 0;
        if (!empty($aggregation->frequencies)) {
          foreach ($aggregation->frequencies as $frequency) {
            if ($frequency->value == $missing) {
              $count = $frequency->count;
              $pct = empty($aggregation->total) ? 0 : round(($count / $aggregation->total) * 100, 1);
              $count .= '<p class="help-inline" title="Percentage over total count">' . $pct . '%</p>';
              break;
            }
          }
        }
        $row[] = $count;
      }
      $row[] = empty($aggregation->total) ? '-' : $aggregation->total;
      $rows[] = $row;
    }

    // combined statistics
    if ($this->variable->variableType == 'Dataschema') {
      $row = array(
        array(
          'data' => '<strong>' . t('All') . '</strong>',
        )
      );
      $row = array_merge($row, $this->statistics_to_row($this->variable_stat));
      $aggregation = $this->variable_stat;
      foreach ($missings as $missing) {
        $count = 0;
        if (!empty($aggregation->frequencies)) {
          foreach ($aggregation->frequencies as $frequency) {
            if ($frequency->value == $missing) {
              $count = $frequency->count;
              $pct = empty($aggregation->total) ? NULL : round(($count / $aggregation->total) * 100, 1);
              $count = empty($pct) ? '0' : $count . '<p class="help-inline" title="Percentage over total count">' . $pct . '%</p>';
              break;
            }
          }
        }
        $row[] = $count;
      }
      $row[] = empty($aggregation->total) ? '-' : $aggregation->total;
      $rows[] = $row;
    }

    // headers
    $headers = array();
    if ($this->variable->variableType == 'Dataschema') {
      $headers = array(t('Study'));
    }
    array_push($headers, t('Min'), t('Max'), t('Mean'), t('Std. Dev'), t('N'));
    foreach ($missings as $missing) {
      $label = $this->get_label_from_category_name($missing);
      $label = $label == 'N/A' ? t('Missing') : $label;
      array_push($headers, $label);
    }
    array_push($headers, t('Total'));

    return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No statistics available')));
  }

  /**
   * Table of value frequencies.
   * @return string
   */
  private function as_frequencies_table() {
    $headers = array('Value');
    $rows = array();
    $missing_rows = array();
    $aggregations = array();

    // headers
    if ($this->variable->variableType == 'Dataschema') {
      if (!empty($this->variable_stat->aggregations)) {
        $aggregations = $this->variable_stat->aggregations;
        foreach ($aggregations as $aggregation) {
          $study_id = $aggregation->studyTable->studyId;
          $header = l(_obiba_mica_variable_study_acronym($this->variable, $study_id), 'mica/study/' . $study_id);
          if (!empty($aggregation->studyTable->name)) {
            $header = $header . ' ' . obiba_mica_commons_get_localized_field($aggregation->studyTable, 'name');
          }
          $headers[] = $header;
        }
        if (count($aggregations) > 1) {
          $headers[] = t('All');
          array_push($aggregations, $this->variable_stat);
        }
      }
    }
    else {
      array_push($headers, t('Frequency'));
      array_push($aggregations, $this->variable_stat);
    }

    // counts per valid/missing values
    $colspan = count($aggregations) + 1;
    $rows[] = array(
      array(
        'data' => '<strong>' . t('Valid Values') . '</strong>',
        'colspan' => $colspan
      )
    );
    $missing_rows[] = array(
      array(
        'data' => '<strong>' . t('Other Values') . '</strong>',
        'colspan' => $colspan
      )
    );

    // categories first
    if (!empty($this->variable->categories)) {
      foreach ($this->variable->categories as $category) {
        $category_name = $category->name;
        $category_label = _obiba_mica_variable_attributes_detail($category, 'label');
        $missing = $category->missing;
        $row = array(
          array(
            'data' => $category->name . '<p class="help-inline">' . $category_label . '</p>',
            'title' => $category_label,
          )
        );
        $value = $category_name;
        foreach ($aggregations as $aggregation) {
          $count = 0;
          if (!empty($aggregation->frequencies)) {
            foreach ($aggregation->frequencies as $frequency) {
              if ($frequency->value == $value) {
                $count = $frequency->count;
                if ($frequency->missing) {
                  $count = $this->count_markup($count, $aggregation->total, $aggregation->total - $aggregation->n, 'Percentage over other values count');
                }
                else {
                  $count = $this->count_markup($count, $aggregation->total, $aggregation->n, 'Percentage over valid values count');
                }
                break;
              }
            }
          }
          $row[] = $count;
        }
        if (!$missing) {
          $rows[] = $row;
        }
        else {
          $missing_rows[] = $row;
        }
      }
    }

    // observed values
    $observed_values = $this->get_observed_values($aggregations);
    foreach ($observed_values as $observed_value) {
      $label = $observed_value == 'NOT_NULL' ? t('Valid values') : $observed_value;
      $label = $observed_value == 'N/A' ? t('Missing') : $label;
      $row = array($label);
      $missing = TRUE;
      foreach ($aggregations as $aggregation) {
        $count = 0;
        if (!empty($aggregation->frequencies)) {
          foreach ($aggregation->frequencies as $frequency) {
            if ($frequency->value == $observed_value) {
              $missing = $frequency->missing; # expected to be the same through the aggregations
              $count = $frequency->count;
              if ($frequency->missing) {
                $count = $this->count_markup($count, $aggregation->total, $aggregation->total - $aggregation->n, 'Percentage over other values count');
              }
              else {
                $count = $this->count_markup($count, $aggregation->total, $aggregation->n, 'Percentage over valid values count');
              }
              break;
            }
          }
        }
        $row[] = $count;
      }
      if (!$missing) {
        // do not include those non-categorical details
        //$rows[] = $row;
      }
      else {
        $missing_rows[] = $row;
      }
    }

    // subtotal valid values
    $row = array('<i>' . t('Subtotal') . '</i>');
    foreach ($aggregations as $aggregation) {
      $row[] = $this->count_markup($aggregation->n, $aggregation->total);
    }
    $rows[] = $row;

    // subtotal missing values
    if (count($missing_rows) > 1) {
      // total missing
      $row = array('<i>' . t('Subtotal') . '</i>');
      foreach ($aggregations as $aggregation) {
        $row[] = $this->count_markup($aggregation->total - $aggregation->n, $aggregation->total);
      }
      $missing_rows[] = $row;

      $rows = array_merge($rows, $missing_rows);
    }

    // grand total
    $row = array(
      array(
        'data' => '<strong>' . t('Total') . '</strong>',
        'class' => array('active')
      )
    );

    foreach ($aggregations as $aggregation) {
      $row[] = array(
        'data' => $aggregation->total,
        'class' => array('active')
      );
    }
    $rows[] = $row;

    return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No statistics available')));
  }

  private function count_markup($count, $total = 0, $subtotal = 0, $title = NULL) {
    $percent_total = $total > 0 ? round(($count / ($total)) * 100, 1) : 0;
    $percent = $subtotal > 0 ? round(($count / $subtotal) * 100, 1) : 0;
    $total_title = t('Percentage over total count');
    if (!empty($title)) {
      return $count . '<div class="help-inline" title="' . $total_title . '">' . $percent_total . '%</div><div class="help-inline" title="' . t($title) . '"><i>(' . $percent . '%)</i></div>';
    }
    return $count . '<p class="help-inline" title="' . $total_title . '">' . $percent_total . '%</p>';
  }

  private function statistics_to_row($aggregation) {
    if (!empty($aggregation->statistics)) {
      $statistics = $aggregation->statistics;
      $pct = empty($aggregation->total) ? 0 : round(($aggregation->n / $aggregation->total) * 100, 1);
      $n = $aggregation->n . '<p class="help-inline" title="Percentage over total count">' . $pct . '%</p>';
      return array(
        property_exists($statistics, 'min') ? round($statistics->min, 1) : '-',
        property_exists($statistics, 'max') ? round($statistics->max, 1) : '-',
        property_exists($statistics, 'mean') && property_exists($statistics, 'stdDeviation') ? round($statistics->mean, 1) : '-',
        property_exists($statistics, 'stdDeviation') ? round($statistics->stdDeviation, 1) : '-',
        $n
      );
    }
    else {
      return array(
        '-',
        '-',
        '-',
        '-',
        '-'
      );
    }
  }

}