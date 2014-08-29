<?php //dpm($mica_client_dataset);?>

<!--<div id="checkthebox" class="terms_checkbox" term=" --><?php //print $agregation_facet . '-' . $term->key ?><!--">-->
<!---->
<!--  <input type="checkbox" class="color_checkbox_--><?php //print $color; ?><!-- regular-checkbox"-->
<!--         name="--><?php //print $relationship_string . $agregation_facet . '[]'; ?><!--"-->
<!--         value="--><?php //print $agregation_facet . '.' . $term->key; ?><!--"-->
<!--         id="--><?php //print $agregation_facet . '-' . $term->key; ?><!--">-->
<!---->
<!--  <label class="terms_checkbox"-->
<!--         for="--><?php //print  $agregation_facet . '-' . $term->key; ?><!--">-->
<!--  </label>-->
<!--  <span class="terms_stat"></span>-->
<!--  <span class"terms_field">--><?php //print  $term->key; ?><!--</span>-->
<!--  <span class="terms_count">--><?php //print  $term->count; ?><!--</span>-->
<!--</div>-->
<!---->
<!--<div>-->
<!--  <input type="hidden" value="--><?php //print $agregation_facet . '.' . $term->key; ?><!--"-->
<!--         id="--><?php //print $agregation_facet . '-' . $term->key; ?><!--">-->
<!--</div>-->

<li class="facets">
  <span class="" style="width: 50.931677018633536%;"></span>

  <span id="checkthebox"
        class="<?php print $relationship_string . $agregation_facet; ?> unchecked"
        aggregation="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
        value="<?php print $agregation_facet . '.' . $term->key; ?>">
    <i style="color:<?php print $color; ?>" class="glyphicon glyphicon-unchecked"></i>
    <?php print  $term->key; ?>
    </span>

  <span class=""><?php print  $term->count; ?></span>

</li>