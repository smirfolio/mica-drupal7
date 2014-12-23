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
        $acronym = mica_client_commons_get_localized_field($dataset, 'acronym');
        $name = mica_client_commons_get_localized_field($dataset, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          'mica/' . mica_client_dataset_type($dataset) . '/' . $dataset->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php print empty($dataset->description) ? '' :
            truncate_utf8(strip_tags(mica_client_commons_get_localized_field($dataset, 'description')), 250, TRUE, TRUE);; ?>
        </small>
      </p>
      <ul class="search-item-list-no-style sm-top-margin help-block">
        <li>
          <?php
          $counts = $dataset->{'obiba.mica.CountStatsDto.datasetCountStats'};
          $variables = $counts->variables;
          $vars_caption = $variables < 2 ? t('variable') : t('variables');
          $studies = $counts->studies;
          $studies_caption = $studies < 2 ? t('study') : t('studies');
          ?>
        </li>
      </ul>
          <span>
            <?php print ($variables === 0 ? '' : t('Includes ') . MicaClientAnchorHelper::dataset_variables($variables, $dataset->id) . ' ' . $vars_caption) ?>
            <?php print ($studies === 0 ? '' : t(' used in ') . MicaClientAnchorHelper::dataset_studies($studies, $dataset->id) . ' ' . $studies_caption) ?>
        </span>


    </div>
  </div>



  <?php
  $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
  ?>
<?php endif; ?>