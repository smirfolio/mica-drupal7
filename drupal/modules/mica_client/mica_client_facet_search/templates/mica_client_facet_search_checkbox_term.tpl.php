<?php //dpm($aggregation_facet);?>
<?php // dpm((((($term->count*200)/$totalhits))*100)/200);?>
<li class="facets">

  <?php
    $title = $term->title;
    $tooltip = empty($term->description) ?  (strlen($title) < 30 ? '' : $title) : $term->description
  ?>
  <span id="checkthebox"
        class="terms_field <?php print $type_string . $aggregation_facet; ?> unchecked"
        aggregation="<?php print $type_string . $aggregation_facet . '[]'; ?>"
        value="<?php print  $title; ?>"
        data-value="<?php print  $term->key; ?>"
        data-toggle="tooltip"
        title="<?php print $tooltip ?>">
    <i class="glyphicon glyphicon-unchecked"></i>
    <?php print  truncate_utf8($title, 30, TRUE, TRUE); ?></span>

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
        <?php if (($_SESSION['request-search-response'] == 'no-empty')) : ?>
          <div class="col-xs-6">
              <span class='term-count'
                <?php if ($term->count != 0) : ?>
                  data-toggle="tooltip" data-placement="top" title="Filtered"
                <?php endif; ?>>
                <?php $digits = strlen($term->count);
                print ($digits < 6 ? str_repeat('&nbsp;', 6 - $digits) : '') . ($term->count === 0 ? '&nbsp;' : $term->count); ?>
              </span>
          </div>
        <?php endif; ?>
        <div class="col-xs-6">
              <span class='term-default' data-toggle="tooltip" data-placement="top" title="All">
   <?php if (($term->count != $term->default) || ($_SESSION['request-search-response'] == 'empty')) : ?>
     <?php $digits = strlen($term->default);
     print ($digits < 6 ? str_repeat('&nbsp;', 6 - $digits) : '') . $term->default; ?>
   <?php endif; ?>
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