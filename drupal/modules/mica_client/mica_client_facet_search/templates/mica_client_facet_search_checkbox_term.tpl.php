<?php //dpm($totalhits);?>
<?php // dpm((((($term->count*200)/$totalhits))*100)/200);?>
<li class="facets">
  <span class="terms_stat" style="background-color:<?php print $color; ?>;
    width: <?php print  (((($term->count * 100) / $totalhits))) ?>%;"></span>
  <span id="checkthebox"
        class="terms_field <?php print $relationship_string . $agregation_facet; ?> unchecked"
        aggregation="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
        value="<?php print $agregation_facet . '.' . $term->key; ?>">
    <i style="color:<?php print $color; ?>" class="glyphicon glyphicon-unchecked"></i>
    <?php print  $term->key; ?>
    <input
      id="<?php print $agregation_facet . '.' . $term->key ?>"
      name="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
      type="hidden" value="">
  </span>

  <span class="terms_count"><?php print  $term->count; ?></span>

</li>