<?php //dpm($list_studies->studySummaries); ?>
<?php //dpm($network_digests); ?>

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-md-2 col-xs-2 text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
           class="listImageThumb"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-S"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10 col-xs-10">
    <div>
      <h4>
      <a
        href="study/<?php print $study->id ?>">
        <?php print mica_client_commons_get_localized_field($study, 'acronym') . ' - ' . mica_client_commons_get_localized_field($study, 'name'); ?>
      </a>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin help-block">
        <?php print truncate_utf8(mica_client_commons_get_localized_field($study, 'objectives'), 250, TRUE, TRUE); ?>
      </p>
    </div>
    <ul class="search-item-list-no-style sm-top-margin help-block">
      <li>
        <?php foreach($network_digests as $digest) {
          $names = array();
          array_push($names, mica_client_commons_get_localized_field($digest, 'name'));
        }

        if (!empty($names)) {
          print t('Member of ') . implode(', and', $names);
        }
        ?>
      </li>

      <li>
        <?php print empty($study->designs) ? '' : t('Study design')?>: <span><?php print implode(', ', $study->designs)?></span>
        <?php print empty($study->targetNumber) ? '' : t('; Target number of participants')?>: <span><?php print $study->targetNumber->noLimit
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
          <a class="" href=''><?php print $datasets ?></a> <?php print $dataset_caption ?>,
          <a class="" href=''><?php print $vars?></a> <?php print $var_caption?>
        </span>
      </li>

    </div>
  </div>
</div>
