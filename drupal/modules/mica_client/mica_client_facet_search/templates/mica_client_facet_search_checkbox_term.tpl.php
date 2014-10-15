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
        class="terms_field <?php print $type_string . $aggregation_facet; ?> unchecked"
        aggregation="<?php print $type_string . $aggregation_facet . '[]'; ?>"
        value="<?php print  $term->key; ?>">
        title="<?php print empty($term->name) || strlen($term->name) < 35 ? '' : $term->name ?>">
    <i class="glyphicon glyphicon-unchecked"></i>
    <?php print  !empty($term->name) ? truncate_utf8($term->name, 35, TRUE, TRUE) : $term->key; ?></span>

  <span class="terms_count"><?php print  $term->count; ?></span>

</li>
<input
  id="<?php print $type_string . $aggregation_facet . '[]-' . $term->key; ?>"
  name="<?php print $type_string . $aggregation_facet . '-terms[]'; ?>"
  type="hidden" value="">