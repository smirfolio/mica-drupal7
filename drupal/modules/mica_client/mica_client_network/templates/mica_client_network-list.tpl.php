<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin text-center">
      <?php
      $count = empty($total_items) ? 0 : $total_items;
      $caption = $count < 2 ? t('Network') : t('Networks');
      ?>
      <span class="search-count"><span
          id="refrech-count"><?php print $count ?></span> <span><?php print $caption ?></span></span>
    </div>
    <div class="col-md-10 col-xs-10">
      <div class="row">
        <div class="col-md-7 col-xs-7">
          <?php print render($form_search); ?>
        </div>
        <div class="col-md-5 col-xs-5 pull-right">
          <ul class="search-list-no-style pull-right">
            <li><?php print MicaClientAnchorHelper::search_networks(t('Search Networks')) ?></li>
            <li><?php print MicaClientAnchorHelper::coverage_networks(t('Coverage')) ?></li>
          </ul>
        </div>
      </div>
    </div>
  </div>
  <div id="refresh-list">
    <?php if (!empty($list_networks)): ?>
      <?php print render($list_networks); ?>
    <?php endif; ?>
  </div>
  <div><?php print $pager_wrap; ?></div>
</div>