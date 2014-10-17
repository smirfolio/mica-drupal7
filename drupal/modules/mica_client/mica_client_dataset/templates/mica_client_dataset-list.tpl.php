<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php
      $count = empty($total_items) ? 0 : $total_items;
      $caption = $count < 2 ? t('Dataset') : t('Datasets');
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
            <li><?php print $dataset_type === 'study_datasets' ? MicaClientAnchorHelper::search_study_datasets(t('Search Datasets')) : MicaClientAnchorHelper::search_harmonization_datasets(t('Search Variables')) ?></li>
            <li><?php print $dataset_type === 'study_datasets' ? MicaClientAnchorHelper::coverage_study_datasets(t('Coverage')) : MicaClientAnchorHelper::coverage_harmonization_datasets(t('Coverage')) ?></li>
          </ul>
        </div>
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