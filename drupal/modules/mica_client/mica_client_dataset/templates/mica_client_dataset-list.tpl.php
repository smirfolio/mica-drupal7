<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php
        $count = empty($total_items) ? 0 : $total_items;
        $caption = $count < 2 ? t('Dataset') : t('Datasets');
      ?>
      <span class="search-count"><span id="refrech-count"><?php print $count ?></span> <span><?php print $caption ?></span></span>
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