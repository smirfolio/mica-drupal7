<?php //dpm($datasets); ?>
<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if (!empty($datasets->total)): ?>
        <?php print $datasets->total . ' ' . ($datasets->total == 1 ? t('Dataset') : t('Datasets')); ?>
      <?php else: print t('No dataset found'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>

  <?php if (!empty($datasets->datasets)): ?>
    <?php foreach ($datasets->datasets as $dataset) :
      $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
      ?>
      <div class="lg-bottom-margin">
        <h4>
          <?php
          print l(mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . $dataset_name,
            'mica/' . mica_client_dataset_type($dataset) . '/' . $dataset->id); ?>
        </h4>
        <?php if (!empty($dataset->description)): ?>
          <p>
            <?php print truncate_utf8(mica_client_commons_get_localized_field($dataset, 'description'), 300, TRUE, TRUE); ?>
          </p>
        <?php else: ?>
          <i><small><?php print t('No description'); ?></small></i>
        <?php endif; ?>
      </div>
    <?php endforeach; ?>
    <div><?php print $pager_wrap; ?></div>
  <?php endif; ?>
</div>