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
      <?php if ($query_request && ($_SESSION['request-search-response'] == 'no-empty') && $term->count != 0) : ?>
        <td class='term-count'>
          <span data-toggle="tooltip" data-placement="top" title="Filtered">
            <?php print $term->count; ?>
          </span>
        </td>
      <?php endif; ?>
      <?php if (!$query_request): ?>
        <td class='term-count'>
          <span data-toggle="tooltip" data-placement="top"
            title="All"><?php print $term->default; ?></span>
        </td>
      <?php elseif (($term->count != $term->default) || ($_SESSION['request-search-response'] == 'empty')) : ?>
        <td class='term-default'>
          <span data-toggle="tooltip" data-placement="top" title="All">
            <?php print $term->default; ?>
          </span>
        </td>
      <?php endif; ?>
    </tr>
  </table>
</li>
<input
  id="<?php print $type_string . $aggregation_facet . '[]-' . $term->key; ?>"
  name="<?php print $type_string . 'terms:' . $aggregation_facet . '[]'; ?>"
  type="hidden" value="">