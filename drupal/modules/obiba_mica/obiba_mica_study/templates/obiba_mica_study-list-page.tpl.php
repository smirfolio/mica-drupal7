<?php print render($node_page) ?>

<div class="list-page">

  <div class="row">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? t('Study') : t('Studies');
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
          <li><?php print MicaClientAnchorHelper::search_studies(t('Search Studies')) ?></li>
          <li><?php print MicaClientAnchorHelper::coverage_studies(t('Coverage')) ?></li>
        </ul>

      </div>
      <div class="hidden-xs inline pull-right">
        <?php print render($form_search); ?>
      </div>

    </div>


  </div>

  <div id="refresh-list">
    <?php if (!empty($list_studies)): ?>
      <?php print render($list_studies); ?>
    <?php endif; ?>
  </div>
  <div><?php print $pager_wrap; ?></div>

</div>


