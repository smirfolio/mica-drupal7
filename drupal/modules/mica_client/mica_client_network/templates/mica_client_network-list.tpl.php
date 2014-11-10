<?php print render($node_page) ?>

<div class="list-page">
  <div class="row sm-bottom-margin">
    <div class="col-md-10 col-xs-10 col-md-offset-2 col-xs-offset-2">
      <div class="search-count">
        <?php
        $count = empty($total_items) ? 0 : $total_items;
        $caption = $count < 2 ? t('Network') : t('Networks');
        ?>
        <span class="search-count"><span
            id="refrech-count"><?php print $count ?></span> <span><?php print $caption ?></span></span>
      </div>
      <div class="document-listing-search-bar pull-right">
        <div>
          <?php print render($form_search); ?>
        </div>
        <div>
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