<?php
/**
 * @file
 * Obiba Mica Module.
 *
 * Copyright (c) 2016 OBiBa. All rights reserved.
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<div id="range" class="facet_terms_range form-inline" term="<?php print $aggregation_facet . '-range'; ?>">
  <label for="edit-range-from"><?php print  t('From'); ?> </label>
  <input type="text" id="range-auto-fill"
    termselect="<?php print $aggregation_facet; ?>"
    term="<?php print $aggregation_facet . '-min'; ?>"
    value="<?php //print  $fields_terms['min']; ?>"
    placeholder="<?php print  $fields_terms['default']['min']; ?>"
    maxlength="75" class="form-control form-item-range-from">

  <label for="edit-range-to" class="control-label"><?php print  t('to'); ?> </label>
  <input type="text" id="range-auto-fill"
    termselect="<?php print $aggregation_facet; ?>"
    term="<?php print $aggregation_facet . '-max'; ?>"
    value="<?php //print  $fields_terms['max']; ?>"
    placeholder="<?php print $fields_terms['default']['max']; ?>"
    maxlength="75" class="form-control form-item-range-from">

  <input type="hidden"
    id="<?php print $aggregation_facet; ?>"
    name="<?php print $type_string . 'range:' . $aggregation_facet . '[]'; ?>"
    value="" maxlength="75" class="form-control form-item-range-from">

  <div class="btn btn-primary btn-xs" id="checkthebox" aggregation="<?php print $aggregation_facet ?>">Go</div>
  <span class="remove-icon-content"></span>
</div>