<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if ($total_items > 0): ?>
        <span id="refrech-count">
        <?php print $total_items . ' ' . ($total_items == 1 ? t('Dataset') : t('Datasets')); ?>
        </span>
      <?php else: ?>
        0  <?php print t('Dataset'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>
  <div id="refresh-list">
    <?php if (!empty($list_datasets)): ?>
      <?php print render($list_datasets); ?>
    <?php endif; ?>
  </div>
  <div><?php print $pager_wrap; ?></div>
</div>
