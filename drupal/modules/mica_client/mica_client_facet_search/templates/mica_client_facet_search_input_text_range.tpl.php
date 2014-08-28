<?php //dpm($mica_client_dataset);?>
<div id="range" class="facet_terms_range form-inline" term="<?php print $agregation_facet . '-range'; ?>">
  ranges from <?php print  $fields_terms['min']; ?> to <?php print  $fields_terms['max']; ?>
  <br/>
  <label for="edit-range-from">From </label>
  <input type="text" id="range-auto-fill"
         termselect="<?php print $agregation_facet; ?>"
         term="<?php print $agregation_facet . '-min'; ?>"
         value="<?php print  $fields_terms['min']; ?>"
         maxlength="75" class="form-control form-item-range-from">

  <label for="edit-range-to" class="control-label">To </label>
  <input type="text" id="range-auto-fill"
         termselect="<?php print $agregation_facet; ?>"
         term="<?php print $agregation_facet . '-max'; ?>"
         value="<?php print  $fields_terms['max']; ?>"
         maxlength="75" class="form-control form-item-range-from">

  <input type="hidden"
         id="<?php print $agregation_facet; ?>"
         name="<?php print $relationship_string . $agregation_facet . '-range[]'; ?>"
         value="" maxlength="75" class="form-control form-item-range-from">

  <div class="btn btn-primary btn-xs" id="checkthebox">Go</div>
</div>