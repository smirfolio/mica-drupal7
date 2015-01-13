<?php print render($node_page) ?>

<div class="list-page">

  <div class="row">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? t('Network') : t('Networks');
    ?>
    <div class="col-md-2 col-sm-2 col-xs-4 min-height-align search-count">
       <span id="refresh-count">
              <?php print $count ?>
        </span>
        <span id="refresh-count">
        <?php print $caption ?>
        </span>

    </div>

    <div class="col-md-10  col-sm-10 col-xs-8 min-height-align pull-right">
      <div>
        <ul class="search-list-no-style pull-right">
          <li><?php print MicaClientAnchorHelper::search_networks(t('Search Networks')) ?></li>
          <li><?php print MicaClientAnchorHelper::coverage_networks(t('Coverage')) ?></li>
        </ul>

      </div>
      <div class="hidden-xs inline pull-right">
        <?php print render($form_search); ?>
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
