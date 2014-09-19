<?php //dpm($networks); ?>
<?php print render($node_page) ?>

<div class="list-page">
  <div class="row">
    <div class="col-md-2 col-xs-2 md-top-margin">
      <?php if (!empty($networks->total)): ?>
        <?php print $networks->total . ' ' . ($networks->total == 1 ? t('Network') : t('Networks')); ?>
      <?php else: print t('No network found'); ?>
      <?php endif; ?>
    </div>
    <div class="col-md-10 col-xs-10">
      <?php print render($form_search); ?>
    </div>
  </div>

  <?php if (!empty($networks->networks)): ?>
    <?php foreach ($networks->networks as $network) :
      $network_name = mica_client_commons_get_localized_field($network, 'name');
      ?>
      <div class="lg-bottom-margin">
        <h4>
          <?php
          print l(mica_client_commons_get_localized_field($network, 'acronym') . ' - ' . $network_name,
            'mica/network/' . $network->id); ?>
        </h4>
        <?php if (!empty($network->description)): ?>
          <p>
            <?php print truncate_utf8(mica_client_commons_get_localized_field($network, 'description'), 300, TRUE, TRUE); ?>
          </p>
        <?php else: ?>
          <i><small><?php print t('No description'); ?></small></i>
        <?php endif; ?>
      </div>
    <?php endforeach; ?>
    <div><?php print $pager_wrap; ?></div>
  <?php endif; ?>
</div>