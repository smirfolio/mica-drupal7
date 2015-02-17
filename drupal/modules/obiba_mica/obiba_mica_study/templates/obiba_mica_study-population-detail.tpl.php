<?php print render($population_content); ?>

<?php if (!empty($population['dce-tab'])): ?>
  <h4><?php print t('Data Collection Events') ?></h4>
  <div class="scroll-content-tab">
    <?php print $population['dce-tab']; ?>
  </div>
<?php endif; ?>

<?php if (!empty($population['dce-modal'])): ?>
  <div><?php print $population['dce-modal']; ?></div>
<?php endif; ?>
