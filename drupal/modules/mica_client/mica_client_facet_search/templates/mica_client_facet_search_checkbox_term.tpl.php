<?php //dpm($mica_client_dataset);?>

<div id="checkthebox" class="terms_checkbox" term=" <?php print $agregation_facet . '-' . $term->key ?>">

  <input type="checkbox" class="color_checkbox_<?php print $color; ?> regular-checkbox"
         name="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
         value="<?php print $agregation_facet . '.' . $term->key; ?>"
         id="<?php print $agregation_facet . '-' . $term->key; ?>">

  <label class="terms_checkbox"
         for="<?php print  $agregation_facet . '-' . $term->key; ?>">
  </label>
  <span class="terms_stat"></span>
  <span class"terms_field"><?php print  $term->key; ?></span>
  <span class="terms_count"><?php print  $term->count; ?></span>
</div>

<div>
  <input type="hidden" value="<?php print $agregation_facet . '.' . $term->key; ?>"
         id="<?php print $agregation_facet . '-' . $term->key; ?>">
</div>

<!--<li class="" >-->
<!--  <span class="" style="width: 50.931677018633536%;"></span>-->
<!-- ngIf: !defined -->
<!--  <span id="checkthebox" class="">-->
<!--    <i style="color:#CE6503" class="icon-check-empty t_impact_blood"></i>-->
<!--     --><?php //print  $term->key ; ?>
<!--    </span>-->
<!-- end ngIf: !defined -->
<!-- ngIf: defined -->
<!--  <span class="">164</span>-->
<!-- ngIf: hideCount -->
<!--</li>-->