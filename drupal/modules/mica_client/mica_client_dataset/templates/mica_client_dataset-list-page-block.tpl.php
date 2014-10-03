<?php //dpm($dataset); ?>
<?php if (!empty($dataset)): ?>
  <div class="row lg-bottom-margin">
    <div class="col-md-2 col-xs-2 text-center">
      <?php if (!empty($logo_url)): ?>
        <img src="<?php print $logo_url ?>"
             class="listImageThumb"/>
      <?php else : ?>
        <h1 class="big-character">
          <span class="t_badge color_light i-obiba-D"></span>
        </h1>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <div class="panel panel-default">
        <div class="panel-heading">
          <?php
          print l(mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . mica_client_commons_get_localized_field($dataset, 'name'),
            'mica/' . mica_client_dataset_type($dataset) . '/' . $dataset->id); ?>
        </div>
        <div class="panel-body">
          <p>
            <?php print empty($dataset->description) ? t('No desription') : truncate_utf8(mica_client_commons_get_localized_field($dataset, 'description'), 300, TRUE, TRUE); ?>
          </p>
        </div>
      </div>
    </div>
  </div>



  <?php
  $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
  ?>
<?php endif; ?>