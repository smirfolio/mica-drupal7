<?php //dpm($network) ?>

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-md-2 hidden-xs hidden-sm text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
        class="listImageThumb"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-N"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10  col-sm-12 col-xs-12">
    <div>
      <h3>
        <?php
        $acronym = obiba_mica_commons_get_localized_field($network, 'acronym');
        $name = obiba_mica_commons_get_localized_field($network, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          MicaClientPathProvider::network($network->id)); ?>
      </h3>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php
          if (empty($network->description)) {
            print '';
          }
          else {
            $objective = obiba_mica_commons_get_localized_field($network, 'description');;
            if (drupal_strlen($objective) >= 300) {
              print text_summary(strip_tags(obiba_mica_commons_markdown($objective)), 'html', 300)
                . '... ' . l('Read More',
                  'mica/network/' . $network->id);
            }
            else {
              print $objective;
            }
          }
          ?>
        </small>
      </p>
    </div>
    <div class="sm-top-margin">
      <?php
      $counts = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
      $variables = $counts->variables;
      $vars_caption = $variables < 2 ? t('variable') : t('variables');
      $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
      $dataset_caption = $datasets < 2 ? "dataset" : "datasets";
      $studies = $counts->studies;
      $caption = $studies < 2 ? 'study' : 'studies';
      ?>
      <?php if (!empty($studies)): ?>
        <span class="label label-info right-indent">
          <?php print MicaClientAnchorHelper::network_studies(t('@count ' . $caption, array('@count' => $studies)), $network->id) ?>
        </span>
      <?php endif ?>
      <?php if (!empty($datasets)): ?>
        <span class="label label-info right-indent">
            <?php print MicaClientAnchorHelper::network_datasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $network->id) ?>
          </span>
      <?php endif ?>
      <?php if (!empty($variables)): ?>
        <span class="label label-info">
            <?php print MicaClientAnchorHelper::network_variables(t('@count ' . $vars_caption, array('@count' => $variables)), $network->id) ?>
          </span>
      <?php endif ?>
    </div>
  </div>
</div>

