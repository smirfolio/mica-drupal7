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
      <h4>
        <?php
        $acronym = obiba_mica_commons_get_localized_field($network, 'acronym');
        $name = obiba_mica_commons_get_localized_field($network, 'name');
        print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
          MicaClientPathProvider::network($network->id)); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php print empty($network->description) ? '' :
            truncate_utf8(strip_tags(obiba_mica_commons_get_localized_field($network, 'description')), 250, TRUE, TRUE);; ?>
        </small>
      </p>
    </div>
    <ul class="nav nav-pills sm-top-margin">
      <li>
        <?php
        $counts = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
        $studies = $counts->studies;
        $caption = $studies < 2 ? 'study' : 'studies';
        ?>
        <?php if (!empty($studies)): ?>
          <span class="label label-info">
            <?php print MicaClientAnchorHelper::network_studies(t('@count ' . $caption, array('@count' => $studies)), $network->id) ?>
          </span>
        <?php endif ?>
      </li>

  </div>
</div>

