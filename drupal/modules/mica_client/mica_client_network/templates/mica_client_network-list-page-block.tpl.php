<?php //dpm($network) ?>

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-md-2 col-xs-2 text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
           class="listImageThumb"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-N"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10 col-xs-10">
    <div>
      <h4>
          <?php
          $acronym = mica_client_commons_get_localized_field($network, 'acronym');
          $name = mica_client_commons_get_localized_field($network, 'name');
          print l($acronym == $name ? $acronym : $acronym . ' - ' . $name,
            'mica/network/' . $network->id); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php print empty($network->description) ? '' : truncate_utf8(mica_client_commons_get_localized_field($network, 'description'), 250, TRUE, TRUE);; ?>
        </small>
      </p>
    </div>
    <ul class="search-item-list-no-style sm-top-margin help-block">
      <li>
        <?php
        $counts = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
        $studies = $counts->studies;
        $caption = $studies < 2 ? t('study') : t('studies');
        ?>
        <span>
          <?php print t('Includes') ?> <a class="" href=''><?php print $studies ?></a> <?php print $caption ?>
        </span>
      </li>

  </div>
</div>

