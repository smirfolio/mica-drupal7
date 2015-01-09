<?php //dpm($aggregation_facet);?>
<?php // dpm((((($term->count*200)/$totalhits))*100)/200);?>
<li class="facets">
  <table>
    <tr>
      <td>
        <?php
        $title = $term->title;
        $tooltip = empty($term->description) ? (strlen($title) < 30 ? '' : $title) : $term->description
        ?>
        <span id="checkthebox"
              class="term-field <?php print $type_string . $aggregation_facet; ?> unchecked"
              aggregation="<?php print $type_string . $aggregation_facet . '[]'; ?>"
              value="<?php print  $title; ?>"
              data-value="<?php print  $term->key; ?>"
              data-toggle="tooltip"
              title="<?php print $tooltip ?>">
          <i class="glyphicon glyphicon-unchecked"></i>
<!--          --><?php //print  truncate_utf8($title, $term->count > 0 ? 25 : 35, TRUE, TRUE); ?>
          <?php print $title ?>
        </span>
      </td>
      <td>
        <?php if ($query_request): ?>
          <?php if (($_SESSION['request-search-response'] == 'no-empty') && $term->count != 0) : ?>
            <span class='term-count'

                  data-toggle="tooltip" data-placement="top" title="Filtered"
              >
                <?php $digits = strlen($term->count);
                print ($digits < 6 ? str_repeat('&nbsp;', 6 - $digits) : '') . ($term->count === 0 ? '&nbsp;' : $term->count); ?>
              </span>
          <?php endif; ?>
        <?php endif; ?>
      </td>
      <td>
        <?php if (!$query_request): ?>
          <span class='term-count' data-toggle="tooltip" data-placement="top"
                title="All"><?php print $term->default; ?></span>
        <?php elseif (($term->count != $term->default) || ($_SESSION['request-search-response'] == 'empty')) : ?>
          <span class='term-default' data-toggle="tooltip" data-placement="top" title="All">
                <?php $digits = strlen($term->default);
                print ($digits < 6 && $term->count > 0 ? str_repeat('&nbsp;', 6 - $digits) : '') . $term->default; ?>
            </span>
        <?php endif; ?>
      </td>
    </tr>
  </table>


</li>
<input
  id="<?php print $type_string . $aggregation_facet . '[]-' . $term->key; ?>"
  name="<?php print $type_string . 'terms:' . $aggregation_facet . '[]'; ?>"
  type="hidden" value="">