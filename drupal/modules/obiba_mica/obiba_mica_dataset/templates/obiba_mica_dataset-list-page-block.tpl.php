<?php if (!empty($dataset)): ?>
  <div class="row sm-bottom-margin document-item-list flex-row">
    <div class="col-md-2 hidden-xs hidden-sm text-center">
      <?php if (!empty($logo_url)): ?>
        <img src="<?php print $logo_url ?>"
             class="listImageThumb"/>
      <?php else : ?>
        <h1 class="big-character">
          <span
            class="t_badge color_light <?php print empty($dataset->{'obiba.mica.HarmonizationDatasetDto.type'}) ? 'i-obiba-D' : 'i-obiba-D-h' ?>"></span>
        </h1>
      <?php endif; ?>
    </div>
    <div class="col-md-10  col-sm-12 col-xs-12">
      <h4>
        <?php
        $acronym = obiba_mica_commons_get_localized_field($dataset, 'acronym');
        $name = obiba_mica_commons_get_localized_field($dataset, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          'mica/' . obiba_mica_dataset_type($dataset) . '/' . $dataset->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php print empty($dataset->description) ? '' :
            truncate_utf8(strip_tags(obiba_mica_commons_get_localized_field($dataset, 'description')), 250, TRUE, TRUE);; ?>
        </small>
      </p>
      <div>
        <?php
        $counts = $dataset->{'obiba.mica.CountStatsDto.datasetCountStats'};
        $variables = $counts->variables;
        $vars_caption = $variables < 2 ? t('variable') : t('variables');
        $studies = $counts->studies;
        $studies_caption = $studies < 2 ? t('study') : t('studies');
        $networks = $counts->networks;
        $network_caption = $networks < 2 ? "network" : "networks";
        ?>
        <?php if (!empty($networks)): ?>
          <span class="label label-info right-indent">
            <?php print MicaClientAnchorHelper::dataset_networks(t('@count ' . $network_caption, array('@count' => $networks)), $dataset->id) ?>
          </span>
        <?php endif ?>
        <?php if (!empty($studies)): ?>
          <span class="label label-info right-indent">
            <?php print MicaClientAnchorHelper::dataset_studies(t('@count ' . $studies_caption, array('@count' => $studies)), $dataset->id) ?>
          </span>
        <?php endif ?>
        <?php if (!empty($variables)): ?>
          <span class="label label-info">
            <?php print MicaClientAnchorHelper::dataset_variables(t('@count ' . $vars_caption, array('@count' => $variables)), $dataset->id) ?>
          </span>
        <?php endif ?>
      </div>
    </div>
  </div>



  <?php
  $dataset_name = obiba_mica_commons_get_localized_field($dataset, 'name');
  ?>
<?php endif; ?>