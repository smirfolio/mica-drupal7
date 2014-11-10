<?php print render($node_page) ?>

<div class="list-page">
  <div class="row sm-bottom-margin">
    <div class="col-md-10 col-xs-10 col-md-offset-2 col-xs-offset-2">
      <div class="search-count">
        <?php
        $count = empty($total_items) ? 0 : $total_items;
        $caption = $count < 2 ? t('Dataset') : t('Datasets');
        ?>
        <span>
          <span id="refrech-count"><?php print $count ?></span> <span><?php print $caption ?></span>
        </span>
      </div>
      <div class="document-listing-search-bar pull-right">
        <div>
          <?php print render($form_search); ?>
        </div>
        <div>
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