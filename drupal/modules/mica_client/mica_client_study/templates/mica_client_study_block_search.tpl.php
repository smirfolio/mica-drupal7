<?php //dpm($items['VAR_ONE']);?>
<form id="facet-search_<?php print $formId; ?>" method="GET">
  <?php foreach ($items as $term => $term_count): ?>
    <label class="checkbox">
      <?php print render($term_count); ?>
    </label>
  <?php endforeach; ?>
</form>
