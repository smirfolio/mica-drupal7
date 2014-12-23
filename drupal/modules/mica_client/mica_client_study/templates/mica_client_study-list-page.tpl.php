<?php print render($node_page) ?>

<div class="list-page">

  <div class="row container-fluid">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? t('Study') : t('Studies');
    ?>
    <div class="col-md-2 search-count">
       <span id="refrech-count">
              <?php print $count ?>
        </span>
        <span id="refrech-count">
       <?php print $caption ?>
        </span>

    </div>

    <div class="col-md-10 codocument-listing-search-bar pull-right">
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


