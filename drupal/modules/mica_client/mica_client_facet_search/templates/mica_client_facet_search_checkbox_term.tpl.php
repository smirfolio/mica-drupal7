<?php //dpm($totalCount);?>
<?php // dpm((((($term->count*200)/$totalhits))*100)/200);?>
<li class="facets">
  <div class="stat-container">
    <span class="terms_stat"
          witdh-val=" <?php print  (((($term->count * 100) / $totalCount))) ?>"
          style="width: <?php print  (((($term->count * 100) / $totalCount))) ?>%;">
          </span>
  </div>
  <span id="checkthebox"
        class="terms_field <?php print $relationship_string . $agregation_facet; ?> unchecked"
        aggregation="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
        value="<?php print  $term->key; ?>">
    <i style="color:<?php print $color; ?>" class="glyphicon glyphicon-unchecked"></i>
    <?php print  $term->key; ?>
  </span>

  <span class="terms_count"><?php print  $term->count; ?></span>

</li>
<input
  id="<?php print  $term->key ?>"
  name="<?php print $relationship_string . $agregation_facet . '[]'; ?>"
  type="hidden" value="">