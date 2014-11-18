<?php //dpm($aggregation_facet);?>
<?php // dpm((((($term->count*200)/$totalhits))*100)/200);?>
<li class="facets">
  <span id="checkthebox"
        class="terms_field <?php print $type_string . $aggregation_facet; ?> unchecked"
        aggregation="<?php print $type_string . $aggregation_facet . '[]'; ?>"
        value="<?php print  $term->key; ?>"
        title="<?php print empty($term->name) || strlen($term->name) < 20 ? '' : $term->name ?>">
    <i class="glyphicon glyphicon-unchecked"></i>
    <?php print  !empty($term->name) ? truncate_utf8($term->name, 20, TRUE, TRUE) : truncate_utf8($term->key, 30, TRUE, TRUE); ?></span>

  <span class="terms_count">

    <?php if (!$query_request): ?>
      <div class="row">
        <div class="col-xs-6">
        <span class='term-count'>

            </span>
        </div>
        <div class="col-xs-6">
        <span class='term-count' data-toggle="tooltip" data-placement="top" title="All">
          <?php print $term->default; ?>
            </span>
        </div>
      </div>

    <?php else : ?>
      <div class="row">
        <div class="col-xs-6">
        <span class='term-count'
          <?php if ($term->count != 0) : ?>
            data-toggle="tooltip" data-placement="top" title="Filtered"
          <?php endif; ?>
          >
          <?php $digits = strlen($term->count);
          print ($digits < 6 ? str_repeat('&nbsp;', 6 - $digits) : '') . ($term->count === 0 ? '&nbsp;' : $term->count); ?>
            </span>
        </div>
        <div class="col-xs-6">
        <span class='term-default' data-toggle="tooltip" data-placement="top" title="All">
          <?php $digits = strlen($term->default);
          print ($digits < 6 ? str_repeat('&nbsp;', 6 - $digits) : '') . $term->default; ?>
            </span>
        </div>
      </div>
    <?php endif; ?>
  </span>

</li>
<input
  id="<?php print $type_string . $aggregation_facet . '[]-' . $term->key; ?>"
  name="<?php print $type_string . 'terms:' . $aggregation_facet . '[]'; ?>"
  type="hidden" value="">