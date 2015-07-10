<?php print render($population_content); ?>

<?php if (!empty($population['dce-tab'])): ?>
  <h4><?php print t('Data Collection Events') ?></h4>
  <div class="scroll-content-tab">
    <?php print $population['dce-tab']; ?>
  </div>
<?php endif; ?>
