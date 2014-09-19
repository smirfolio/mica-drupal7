<?php //dpm($studies->studySummaries); ?>
<?php print render($node_page) ?>
<?php //dpm($studies); ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if (!empty($studies->total)): ?>
        <span id="refresh-count">
        <?php print $studies->total . ' ' . ($studies->total == 1 ? t('Study') : t('Studies')); ?>
        </span>
      <?php else: print t('No study found'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>

  <div id="refresh-list">
    <?php if (!empty($studies)): ?>
      <?php print render($studies); ?>
    <?php endif; ?>
  </div>
</div>

