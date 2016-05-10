<?php print render($node_page) ?>

<div class="list-page">

  <div class="row">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? t('Study') : t('Studies');
    ?>
    <div class="col-md-2 col-sm-2 col-xs-4 min-height-align search-count">
      <?php if (variable_get_value('studies_list_show_studies_count_caption')): ?>
      <span id="refresh-count">
        <?php print $count ?>
      </span>
      <span id="refresh-count">
        <?php print $caption ?>
      </span>
      <?php endif; ?>
    </div>

    <div class="col-md-10  col-sm-10 col-xs-8 min-height-align pull-right">
      <div class="hidden-xs inline pull-left">
        <?php print render($form_search); ?>
      </div>
      <div class="btn-group pull-right">
        <?php if (variable_get_value('study_list_show_search_button')): ?>
          <?php print MicaClientAnchorHelper::searchStudies(TRUE); ?>
        <?php endif; ?>
      </div>
    </div>


  </div>

  <div id="refresh-list">
    <?php if (!empty($list_studies)): ?>
      <?php print render($list_studies); ?>
    <?php endif; ?>
  </div>
  <div class="clearfix"></div>
  <div><?php print $pager_wrap; ?></div>

</div>


