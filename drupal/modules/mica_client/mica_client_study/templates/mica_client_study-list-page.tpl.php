<?php //dpm($list_studies->studySummaries); ?>
<?php print render($node_page) ?>
<?php //dpm($list_studies); ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if ($total_items > 0): ?>
        <span id="refrech-count">
        <?php print $total_items . ' ' . ($total_items == 1 ? t('Study') : t('Studies')); ?>
        </span>
      <?php else: ?>
        0  <?php print t('Study'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>

  <div id="refresh-list">
    <?php if (!empty($list_studies)): ?>
      <?php print render($list_studies); ?>
    <?php endif; ?>
  </div>
