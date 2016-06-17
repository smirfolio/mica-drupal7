<?php print render($node_page); ?>

<div class="list-page">
  <div class="row">
    <?php
      $count = empty($total_items) ? 0 : $total_items;
      $caption = $count < 2 ? t('Project') : t('Projects');
    ?>
    <div class="col-xs-4 col-sm-2 min-height-align search-count">
      <span id="refresh-count"><?php print $count ?></span>
      <span id="refresh-count"><?php print $caption ?></span>
    </div>
    
    <div class="col-xs-8 col-sm-10 min-height-align pull-right">
      <div class="hidden-xs inline pull-right">
        <?php print render($form_search); ?>
      </div>
    </div>
  </div>
  
  <div id="refresh-list">
    <?php if (!empty($list_projects)): ?>
      <?php print render($list_projects); ?>
    <?php endif; ?>
  </div>
  <div class="clearfix"></div>
  <div><?php print $pager_wrap; ?></div>
</div>
