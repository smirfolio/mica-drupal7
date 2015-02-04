<?php print render($population_content); ?>

<?php if (!empty($population['dce-tab'])): ?>
  <h5><?php print t('Data Collection Events') ?></h5>
  <div class="scroll-content-tab">
    <?php print $population['dce-tab']; ?>
  </div>
<?php endif; ?>

<?php if (!empty($population['dce-modal'])): ?>
  <div><?php print $population['dce-modal']; ?></div>
<?php endif; ?>
