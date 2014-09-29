<?php //dpm($list_studies->studySummaries); ?>
<?php //dpm($list_studies); ?>

<?php if (!empty($list_studies->studySummaries)): ?>
  <?php foreach ($list_studies->studySummaries as $study) : ?>
    <div class="row lg-bottom-margin">
      <div class="col-md-2 col-xs-2 text-center">
        <?php if (!empty($study->logo)): ?>

          <?php
          $url = "http://localhost:8082/ws/draft/study/$study->id/file/" . $study->logo->id . "/_download";
          print theme('imagecache_external', array(
            'path' => $url,
            'style_name' => 'thumbnail',
            'alt' => 'Druplicon',
            'attributes' => array('class' => 'listImageThumb')
          ));
          ?>

        <?php else : ?>
          <h1 class="big-character">
            <span class="t_badge color_S t_badge_100"></span>
          </h1>
        <?php endif; ?>
      </div>
      <div class="col-md-10 col-xs-10">
        <h4><a
            href="study/<?php print $study->id ?>">
            <?php print mica_client_commons_get_localized_field($study, 'acronym') . ' - ' . mica_client_commons_get_localized_field($study, 'name'); ?>
          </a>
        </h4>

        <p>
          <?php print truncate_utf8(mica_client_commons_get_localized_field($study, 'objectives'), 300, TRUE, TRUE); ?>
        </p>
      </div>
    </div>

  <?php endforeach; ?>
<?php endif; ?>


