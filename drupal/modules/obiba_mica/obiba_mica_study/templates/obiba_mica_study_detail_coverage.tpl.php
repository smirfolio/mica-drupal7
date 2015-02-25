<h2 id="coverage"><?php print t('Variable Classification') ?></h2>
<?php foreach ($coverage as $taxonomy_coverage): ?>
  <h3><?php print obiba_mica_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'titles'); ?></h3>

  <p class="help-block">
    <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'descriptions'); ?>
  </p>

  <div class="scroll-content-tab">
    <?php print render($taxonomy_coverage['chart']); ?>
  </div>
<?php endforeach ?>
