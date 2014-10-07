<?php //dpm($mica_client_dataset);?>
<div id="range" class="facet_terms_range form-inline" term="<?php print $aggregation_facet . '-range'; ?>">
  <label for="edit-range-from">From </label>
  <input type="text" id="range-auto-fill"
         termselect="<?php print $aggregation_facet; ?>"
         term="<?php print $aggregation_facet . '-min'; ?>"
         value="<?php print  $fields_terms['min']; ?>"
         placeholder="<?php print  $fields_terms['min']; ?>"
         maxlength="75" class="form-control form-item-range-from">

  <label for="edit-range-to" class="control-label">To </label>
  <input type="text" id="range-auto-fill"
         termselect="<?php print $aggregation_facet; ?>"
         term="<?php print $aggregation_facet . '-max'; ?>"
         value="<?php print  $fields_terms['max']; ?>"
         placeholder="<?php print  $fields_terms['max']; ?>"
         maxlength="75" class="form-control form-item-range-from">

  <input type="hidden"
         id="<?php print $aggregation_facet; ?>"
         name="<?php print $type_string . $aggregation_facet . '-range[]'; ?>"
         value="" maxlength="75" class="form-control form-item-range-from">

  <div class="btn btn-primary btn-xs" id="checkthebox">Go</div>
</div>