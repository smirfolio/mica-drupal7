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
        <?php print MicaClientAnchorHelper::study_list_item($study); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php
          print MicaClientAnchorHelper::ellipses(
            t('Read more'),
            obiba_mica_commons_get_localized_field($study, 'objectives'),
            MicaClientPathProvider::study($study->id)
          );
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
      <?php if (!empty($study->designs) || !empty($study->targetNumber)) : ?>
        <li>
          <?php if (!empty($study->designs)): print t('Study design') ?>:
            <span><?php print implode(', ', obiba_mica_commons_clean_string($study->designs)) ?></span>
          <?php endif; ?>
          <?php if (!empty($study->targetNumber)):  print t('; Target number of participants') ?>:
            <span><?php print $study->targetNumber->noLimit ? t('No limits') : $study->targetNumber->number ?></span>
          <?php endif; ?>
        </li>
      <?php endif; ?>
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
      <?php if (!empty($networks) && variable_get_value('studies_column_networks')): ?>
        <span class="label label-default rounded right-indent">
            <?php print MicaClientAnchorHelper::study_networks(t('@count ' . $network_caption, array('@count' => $networks)), $study->id) ?>
          </span>
      <?php endif ?>
      <?php if (!empty($datasets) && (variable_get_value('studies_column_study_datasets') || variable_get_value('studies_column_harmonization_datasets'))): ?>
        <span class="label label-default rounded right-indent">
            <?php print MicaClientAnchorHelper::study_datasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $study->id) ?>
          </span>
      <?php endif ?>
      <?php if (!empty($vars) && variable_get_value('studies_column_variables')): ?>
        <span class="label label-default rounded">
            <?php print MicaClientAnchorHelper::study_variables(t('@count ' . $var_caption, array('@count' => $vars)), $study->id) ?>
          </span>
      <?php endif ?>
    </div>
  </div>
</div>

