<?php //dpm($datasets); ?>
<?php print render($node_page) ?>
<hr>
<div class="clearfix">
  <div class="alert alert-info col-md-7" role="alert"><strong>TODO</strong>search form here
  </div>
  <div class="col-md-5 ">
    <div class="advanced-search-link-center">
      <?php print t('Open IN'); ?> : <a href="search?type=studies"><?php print t('Advanced search'); ?></a>
      <!--      |      <a href="">--><?php //print t('Domain Coverage'); ?><!-- </a>-->
    </div>
  </div>
  <div class="clearfix"></div>

  <div class="list-page">
    <?php foreach ($datasets as $dataset) :
      $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
      ?>
      <h4>
        <?php //print drupal_substr(mica_client_commons_get_localized_field($dataset, 'name'), 0, 1); ?>
        </span>
        <a href="../<?php print $type ?>/<?php print $dataset->id ?>/<?php print $dataset_name ?>">
          <?php print mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . $dataset_name; ?>
        </a>
      </h4>
      <?php if (!empty($dataset)): ?>
      <p>
        <?php print truncate_utf8(mica_client_commons_get_localized_field($dataset, 'description'), 300, TRUE, TRUE); ?>
      </p>
    <?php endif; ?>

      <div class="clearfix"></div>
    <?php endforeach; ?>
  </div>