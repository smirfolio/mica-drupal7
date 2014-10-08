<?php
//dpm($vocabulary_coverage);
?>

<?php if (!empty($vocabulary_coverage->hits)) : ?>
  <?php print render($chart); ?>
<?php endif ?>