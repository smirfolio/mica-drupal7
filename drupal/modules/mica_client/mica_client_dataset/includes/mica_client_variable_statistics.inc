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
            foreach ($aggregation->frequencies as $frequency) {
              if ($frequency->value == $observed) {
                $data[$header][] = $frequency->count;
                break;
              }
            }
          }
        }
      }
      // observed that are valid, merged into one
      $labels[] = 'N (' . t('Valid values') . ')';
      foreach ($aggregations as $aggregation) {
        $header = $this->get_study_table_label($aggregation);
        $data[$header][] = empty($aggregation->n) ? 0 : $aggregation->n;
      }

      if (!empty($data)) {
        $to_render = mica_client_facet_search_stacked_column_chart($labels, $data, NULL, NULL, 400, 'none');
        return render($to_render);
      }
      else {
        return FALSE;
      }
    }
    return FALSE;
  }

  /**
   * Mix category name and localized label in one string.
   * @param $category
   * @return null|string|the
   */
  private function get_category_label($category) {
    $label = _mica_client_variable_attributes_detail($category, 'label');
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
  private function get_label_from_category_name($value) {
    if ($value == NULL || $value == '' || empty($this->variable->categories)) {
      return $value;
    }

    foreach ($this->variable->categories as $category) {
      if ($value == $category->name) {
        $label = _mica_client_variable_attributes_detail($category, 'label');
        return '<span title="' . $label . '">' . $value . '</span>';
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
    $header = _mica_client_variable_study_acronym($this->variable, $study_id);
    if (!empty($aggregation->studyTable->name)) {
      $header = $header . '(' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name') . ')';
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
        $header = l(_mica_client_variable_study_acronym($this->variable, $study_id), 'mica/study/' . $study_id);
        if (!empty($aggregation->studyTable->name)) {
          $header = $header . ' ' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name');
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
              $pct = empty($aggregation->total) ? NULL : round(($count / $aggregation->total) * 100, 1);
              $count = empty($pct) ? '0' : $count . '<p class="help-inline" title="Percentage over total count">(' . $pct . '%)</p>';
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
              $count = empty($pct) ? '0' : $count . '<p class="help-inline" title="Percentage over total count">(' . $pct . '%)</p>';
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
    $aggregations = array();

    // headers
    if ($this->variable->variableType == 'Dataschema') {
      if (!empty($this->variable_stat->aggregations)) {
        $aggregations = $this->variable_stat->aggregations;
        foreach ($aggregations as $aggregation) {
          $study_id = $aggregation->studyTable->studyId;
          $header = l(_mica_client_variable_study_acronym($this->variable, $study_id), 'mica/study/' . $study_id);
          if (!empty($aggregation->studyTable->name)) {
            $header = $header . ' ' . mica_client_commons_get_localized_field($aggregation->studyTable, 'name');
          }
          $headers[] = $header;
        }
        if (count($aggregations) > 1) {
          $headers[] = t('All');
        }
      }
    }
    else {
      array_push($headers, t('Frequency'));
      array_push($aggregations, $this->variable_stat);
    }

    $colspan = count($aggregations) + 1 + (count($aggregations) > 1 ? 1 : 0);

    // count of missing and non-missing values
    $total_non_missings = array();
    $total_missings = array();
    foreach ($aggregations as $aggregation) {
      $total_non_missings[] = empty($aggregation->n) ? : $aggregation->n;
      $total_missings[] = empty($aggregation->total) ? 0 : empty($aggregation->n) ? $aggregation->total : $aggregation->total - $aggregation->n;
    }

    // counts per category
    $rows[] = array(
      array(
        'data' => '<strong>' . t('Valid Values') . '</strong>',
        'colspan' => $colspan
      )
    );
    $missing_rows = array();
    $missing_rows[] = array(
      array(
        'data' => '<strong>' . t('Missing Values') . '</strong>',
        'colspan' => $colspan
      )
    );

    // categories first
    if (!empty($this->variable->categories)) {
      foreach ($this->variable->categories as $category) {
        $category_name = $category->name;
        $category_label = _mica_client_variable_attributes_detail($category, 'label');
        $missing = $category->missing;
        $row = array(
          array(
            'data' => $category->name . '<p class="help-inline">' . $category_label . '</p>',
            'title' => $category_label,
          )
        );
        $value = $category_name;
        $count_all = 0;
        $total_non_missing_all = 0;
        $total_missing_all = 0;
        for ($i = 0; $i < count($aggregations); $i++) {
          $aggregation = $aggregations[$i];
          $total_non_missing = $total_non_missings[$i];
          $total_missing = $total_missings[$i];
          $count = 0;
          if (!empty($aggregation->frequencies)) {
            foreach ($aggregation->frequencies as $frequency) {
              if ($frequency->value == $value) {
                $count = $frequency->count;
                $count_all += $count;
                if ($frequency->missing) {
                  $total_missing_all += $total_missing;
                  $percent = $total_missing > 0 ? round(($count / $total_missing) * 100, 1) : 0;
                  $count .= '<p class="help-inline" title="Percentage over missing values count">(' . $percent . '%)</p>';
                }
                else {
                  $total_non_missing_all += $total_non_missing;
                  $percent = $total_non_missing > 0 ? round(($count / $total_non_missing) * 100, 1) : 0;
                  $count .= '<p class="help-inline" title="Percentage over valid values count">(' . $percent . '%)</p>';
                }
                break;
              }
            }
          }
          $row[] = $count;
        }
        if (!$missing) {
          if (count($aggregations) > 1) {
            $percent = $total_non_missing_all > 0 ? round(($count_all / $total_non_missing_all) * 100, 1) : 0;
            $count_all .= '<p class="help-inline" title="Percentage over valid values count">(' . $percent . '%)</p>';
            $row[] = $count_all;
          }
          $rows[] = $row;
        }
        else {
          if (count($aggregations) > 1) {
            $percent = $total_missing_all > 0 ? round(($count_all / $total_missing_all) * 100, 1) : 0;
            $count_all .= '<p class="help-inline" title="Percentage over missing values count">(' . $percent . '%)</p>';
            $row[] = $count_all;
          }
          $missing_rows[] = $row;
        }
      }
    }

    // observed values
    $observed_values = $this->get_observed_values($aggregations);
    foreach ($observed_values as $observed_value) {
      $label = $observed_value == 'NOT_NULL' ? t('Valid values') : $observed_value;
      $row = array($label);
      $count_all = 0;
      $total_non_missing_all = 0;
      $total_missing_all = 0;
      $missing = TRUE;
      for ($i = 0; $i < count($aggregations); $i++) {
        $aggregation = $aggregations[$i];
        $total_non_missing = $total_non_missings[$i];
        $total_missing = $total_missings[$i];
        $count = 0;
        if (!empty($aggregation->frequencies)) {
          foreach ($aggregation->frequencies as $frequency) {
            if ($frequency->value == $observed_value) {
              $missing = $frequency->missing; # expected to be the same through the aggregations
              $count = $frequency->count;
              $count_all += $count;
              if ($frequency->missing) {
                $total_missing_all += $total_missing;
                $percent = $total_missing > 0 ? round(($count / $total_missing) * 100, 1) : 0;
                $count .= '<p class="help-inline" title="Percentage over missing values count">(' . $percent . '%)</p>';
              }
              else {
                $total_non_missing_all += $total_non_missing;
                $percent = $total_non_missing > 0 ? round(($count / $total_non_missing) * 100, 1) : 0;
                $count .= '<p class="help-inline" title="Percentage over valid values count">(' . $percent . '%)</p>';
              }
              break;
            }
          }
        }
        $row[] = $count;
      }
      if (count($aggregations) > 1) {
        $percent = $total_missing_all > 0 ? round(($count_all / $total_missing_all) * 100, 1) : 0;
        $count_all .= '<p class="help-inline" title="Percentage over missing values count">(' . $percent . '%)</p>';
        $row[] = $count_all;
      }
      if (!$missing) {
        #$rows[] = $row;
      }
      else {
        $missing_rows[] = $row;
      }
    }

    // total non missing
    $row = array('<i>' . t('Subtotal') . '</i>');
    $total_non_missing_all = 0;
    $total_all = 0;
    for ($i = 0; $i < count($aggregations); $i++) {
      $aggregation = $aggregations[$i];
      $total_non_missing = $total_non_missings[$i];
      $total_non_missing_all += $total_non_missing;
      $total_all += $aggregation->total;
      $percent = $aggregation->total > 0 ? round(($total_non_missing / $aggregation->total) * 100, 1) : 0;
      $total_non_missing .= '<p class="help-inline" title="Percentage over total count">(' . $percent . '%)</p>';
      $row[] = $total_non_missing;
    }
    if (count($aggregations) > 1) {
      $percent = $total_all > 0 ? round(($total_non_missing_all / $total_all) * 100, 1) : 0;
      $total_non_missing_all .= '<p class="help-inline" title="Percentage over total count">(' . $percent . '%)</p>';
      $row[] = $total_non_missing_all;
    }
    $rows[] = $row;

    // missing values
    if (count($missing_rows) > 1) {
      // total missing
      $row = array('<i>' . t('Subtotal') . '</i>');
      $total_missing_all = 0;
      $total_all = 0;
      for ($i = 0; $i < count($aggregations); $i++) {
        $aggregation = $aggregations[$i];
        $total_missing = $total_missings[$i];
        $total_missing_all += $total_missing;
        $total_all += $aggregation->total;
        $percent = $aggregation->total > 0 ? round(($total_missing / $aggregation->total) * 100, 1) : 0;
        $total_missing .= '<p class="help-inline" title="Percentage over total count">(' . $percent . '%)</p>';
        $row[] = $total_missing;
      }
      if (count($aggregations) > 1) {
        $percent = $total_all > 0 ? round(($total_missing_all / $total_all) * 100, 1) : 0;
        $total_missing_all .= '<p class="help-inline" title="Percentage over total count">(' . $percent . '%)</p>';
        $row[] = $total_missing_all;
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
    $total_all = 0;
    foreach ($aggregations as $aggregation) {
      $row[] = array(
        'data' => $aggregation->total,
        'class' => array('active')
      );
      $total_all += $aggregation->total;
    }
    if (count($aggregations) > 1) {
      $row[] = array(
        'data' => $total_all,
        'class' => array('active')
      );
    }
    $rows[] = $row;

    return theme('table', array('header' => $headers, 'rows' => $rows, 'empty' => t('No statistics available')));
  }

  private function statistics_to_row($aggregation) {
    if (!empty($aggregation->statistics)) {
      $statistics = $aggregation->statistics;
      $pct = empty($aggregation->total) ? NULL : round(($aggregation->n / $aggregation->total) * 100, 1);
      $n = empty($pct) ? '0' : $aggregation->n . '<p class="help-inline" title="Percentage over total count">(' . $pct . '%)</p>';
      return array(
        property_exists($statistics, 'min') ? round($statistics->min, 3) : '-',
        property_exists($statistics, 'max') ? round($statistics->max, 3) : '-',
        property_exists($statistics, 'mean') && property_exists($statistics, 'stdDeviation') ? round($statistics->mean, 3) : '-',
        property_exists($statistics, 'stdDeviation') ? round($statistics->stdDeviation, 3) : '-',
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