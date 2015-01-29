<?php print render($node_page) ?>

<div class="list-page">

  <div class="row">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? t('Dataset') : t('Datasets');
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
          <li><?php print $dataset_type === 'study_datasets' ? MicaClientAnchorHelper::search_study_datasets(t('Search Datasets')) : MicaClientAnchorHelper::search_harmonization_datasets(t('Search Variables')) ?></li>
          <li><?php print $dataset_type === 'study_datasets' ? MicaClientAnchorHelper::coverage_study_datasets(t('View Coverage')) : MicaClientAnchorHelper::coverage_harmonization_datasets(t('View Coverage')) ?></li>
        </ul>

      </div>
      <div class="hidden-xs inline pull-right">
        <?php print render($form_search); ?>
      </div>

    </div>


  </div>


  <div id="refresh-list">
    <?php if (!empty($list_datasets)): ?>
      <?php print render($list_datasets); ?>
    <?php endif; ?>
  </div>
  <div><?php print $pager_wrap; ?></div>
</div>
