<?php if (!empty($network) && !empty($network)): ?>

  <div class="row lg-bottom-margin">
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
      <h4><a
          href="network/<?php print $network->id ?>">
          <?php print mica_client_commons_get_localized_field($network, 'acronym') . ' - ' . mica_client_commons_get_localized_field($network, 'name'); ?>
        </a>
      </h4>

      <p>
        <?php // print truncate_utf8(mica_client_commons_get_localized_field($network, 'objectives'), 300, TRUE, TRUE); ?>
      </p>
    </div>
  </div>

<?php endif; ?>