<?php //dpm($study); ?>
<?php //dpm($network_digests); ?>

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-md-2 hidden-xs hidden-sm text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
        class="listImageThumb img-responsive"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-S"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10  col-sm-12 col-xs-12">
    <div>
      <h4>
        <?php
        $acronym = obiba_mica_commons_get_localized_field($study, 'acronym');
        $name = obiba_mica_commons_get_localized_field($study, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          'mica/study/' . $study->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php
          $objective = obiba_mica_commons_get_localized_field($study, 'objectives');

          if (drupal_strlen($objective) >= 300) {
            print text_summary(strip_tags(obiba_mica_commons_markdown($objective)), 'html', 300)
              . '... ' . l('Read More',
                'mica/study/' . $study->id);
          }
          else {
            print $objective;
          }
          ?>
        </small>
      </p>
    </div>
    <ul class="search-item-list-no-style sm-top-margin help-block">
      <li>
        <?php foreach ($network_digests as $digest) {
          $names = array();
          array_push($names, obiba_mica_commons_get_localized_field($digest, 'name'));
        }

        if (!empty($names)) {
          print t('Member of ') . implode(', and', $names);
        }
        ?>
      </li>

      <li>
        <?php print empty($study->designs) ? '' : t('Study design') ?>:
        <span><?php print implode(', ', obiba_mica_commons_clean_string($study->designs)) ?></span>
        <?php print empty($study->targetNumber) ? '' : t('; Target number of participants') ?>:
        <span><?php print $study->targetNumber->noLimit ? t('No limits') : $study->targetNumber->number ?></span>
      </li>
    </ul>
    <div class="sm-top-margin">
      <?php
      $counts = $study->{'obiba.mica.CountStatsDto.studyCountStats'};
      $vars = $counts->variables;
      $var_caption = $vars < 2 ? "variable" : "variables";
      $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
      $dataset_caption = $datasets < 2 ? "dataset" : "datasets";
      $networks = $counts->networks;
      $network_caption = $networks < 2 ? "network" : "networks";
      ?>
      <?php if (!empty($networks)): ?>
        <span class="label label-info right-indent">
            <?php print MicaClientAnchorHelper::study_networks(t('@count ' . $network_caption, array('@count' => $networks)), $study->id) ?>
          </span>
      <?php endif ?>
      <?php if (!empty($datasets)): ?>
        <span class="label label-info right-indent">
            <?php print MicaClientAnchorHelper::study_datasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $study->id) ?>
          </span>
      <?php endif ?>
      <?php if (!empty($vars)): ?>
        <span class="label label-info">
            <?php print MicaClientAnchorHelper::study_variables(t('@count ' . $var_caption, array('@count' => $vars)), $study->id) ?>
          </span>
      <?php endif ?>
    </div>
  </div>
</div>

