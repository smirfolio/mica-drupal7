<?php ////dpm($items['VAR_ONE']);?>
<!--<ul>-->
<!--  --><?php //foreach ($items as $term => $term_count): ?>
<!--    <li>-->
<!--      <input type="checkbox">  --><?php //print render($term_count); ?>
<!--    </li>-->
<!--  --><?php //endforeach; ?>
<!--</ul>-->

<?php //dpm($items['VAR_ONE']);?>
<form id="search_<?php print $formId; ?>" method="GET">
  <?php foreach ($items as $term => $term_count): ?>
    <label class="checkbox">
      <?php print render($term_count); ?>
    </label>
  <?php endforeach; ?>
</form>