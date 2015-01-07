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
        $acronym = mica_client_commons_get_localized_field($study, 'acronym');
        $name = mica_client_commons_get_localized_field($study, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          'mica/study/' . $study->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php print truncate_utf8(strip_tags(mica_client_commons_get_localized_field($study, 'objectives')), 250, TRUE, TRUE); ?>
        </small>
      </p>
    </div>
    <ul class="search-item-list-no-style sm-top-margin help-block">
      <li>
        <?php foreach ($network_digests as $digest) {
          $names = array();
          array_push($names, mica_client_commons_get_localized_field($digest, 'name'));
        }

        if (!empty($names)) {
          print t('Member of ') . implode(', and', $names);
        }
        ?>
      </li>

      <li>
        <?php print empty($study->designs) ? '' : t('Study design') ?>:
        <span><?php print implode(', ', $study->designs) ?></span>
        <?php print empty($study->targetNumber) ? '' : t('; Target number of participants') ?>
        : <span><?php print $study->targetNumber->noLimit
            ? t('No limits') : $study->targetNumber->number ?></span>
      </li>
      <li>
        <?php
        $counts = $study->{'obiba.mica.CountStatsDto.studyCountStats'};
        $vars = $counts->variables;
        $var_caption = $vars < 2 ? "variable" : "variables";
        $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
        $dataset_caption = $datasets < 2 ? "dataset" : "datasets";
        ?>
        <span>
          <?php print ($datasets === 0 ? '' : MicaClientAnchorHelper::study_datasets($datasets, $study->id) . ' ' . $dataset_caption) ?>
          <?php print ($vars === 0 ? '' : ', ' . MicaClientAnchorHelper::study_variables($vars, $study->id) . ' ' . $var_caption) ?>
        </span>
      </li>

  </div>
</div>

