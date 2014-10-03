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
      <div class="panel panel-default">
        <div class="panel-heading">
          <a
            href="network/<?php print $network->id ?>">
            <?php print mica_client_commons_get_localized_field($network, 'acronym') . ' - ' . mica_client_commons_get_localized_field($network, 'name'); ?>
          </a>
        </div>
        <div class="panel-body">
          <p>

            <?php print empty($network->description) ? '' : truncate_utf8(mica_client_commons_get_localized_field($network, 'description'), 300, TRUE, TRUE);; ?>
          </p>

          <p class="lg-top-margin">
            <?php
            $count = empty($network->studyIds) ? 0 : count($network->studyIds);
            $caption = $count < 2 ? "study" : "studies";
            $href = "<a href='studies'>$count $caption</a>";
            ?>
            <?php print t("Includes $href") ?>
          </p>
        </div>
      </div>
    </div>
  </div>

<?php endif; ?>