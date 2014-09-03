<?php //dpm($items['VAR_ONE']);?>
<form id="facet-search_<?php print $formId; ?>">
  <?php foreach ($items as $term => $term_count): ?>
    <label class="span-checkbox">
    <?php print render($term_count); ?>
    </label>
  <?php endforeach; ?>
</form>
