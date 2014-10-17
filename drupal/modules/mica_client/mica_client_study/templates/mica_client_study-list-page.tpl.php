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
            <li><?php print MicaClientAnchorHelper::search_studies(t('Search Studies')) ?></li>
            <li><?php print MicaClientAnchorHelper::coverage_studies(t('Coverage')) ?></li>
          </ul>
        </div>
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
