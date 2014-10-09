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
      <h4>
        <?php
        print l(mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . mica_client_commons_get_localized_field($dataset, 'name'),
          'mica/' . mica_client_dataset_type($dataset) . '/' . $dataset->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin help-block">
        <?php print empty($dataset->description) ? '' : truncate_utf8(mica_client_commons_get_localized_field($dataset, 'description'), 250, TRUE, TRUE);; ?>
      </p>
      <ul class="search-item-list-no-style sm-top-margin help-block">
        <li>
          <?php
          $counts = $dataset->{'obiba.mica.CountStatsDto.datasetCountStats'};
          $variabes = $counts->variables;
          $vars_caption = $variabes < 2 ? t('variable') : t('variables');
          $studies = $counts->studies;
          $studies_caption = $studies < 2 ? t('study') : t('studies');
          ?>
          <span>
          <?php print t('Includes') ?> <a class=""
                                          href=''><?php print $variabes ?></a> <?php print $vars_caption . t(' used in ') ?>
            <a href=''><?php print $studies ?></a> <?php print $studies_caption ?>
        </span>
        </li>

    </div>
  </div>



  <?php
  $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
  ?>
<?php endif; ?>