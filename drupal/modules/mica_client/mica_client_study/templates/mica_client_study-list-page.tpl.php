<?php //dpm($list_studies->studySummaries); ?>
<?php print render($node_page) ?>
<?php //dpm($list_studies); ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin text-center">
      <?php
        $count = empty($total_items) ? 0 : $total_items;
        $caption = $count < 2 ? t('Study') : t('Studies');
      ?>
      <span class="search-count"><span id="refrech-count"><?php print $count ?></span> <span><?php print $caption ?></span></span>
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
  <div><?php print $pager_wrap; ?></div>
