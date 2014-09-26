<?php if (!empty($list_networks) && !empty($list_networks->networks)): ?>
  
  <?php foreach ($list_networks->networks as $network) :
    $network_name = mica_client_commons_get_localized_field($network, 'name');
    ?>
    <div class="lg-bottom-margin">
      <h4>
        <?php
        print l(mica_client_commons_get_localized_field($network, 'acronym') . ' - ' . $network_name,
          'mica/network/' . $network->id); ?>
      </h4>
<!--      --><?php //if (!empty($network->description)): ?>
<!--        <p>-->
<!--          --><?php //print truncate_utf8(mica_client_commons_get_localized_field($network, 'description'), 300, TRUE, TRUE); ?>
<!--        </p>-->
<!--      --><?php //else: ?>
<!--        <i><small>--><?php //print t('No description'); ?><!--</small></i>-->
<!--      --><?php //endif; ?>
    </div>
  <?php endforeach; ?>
<?php endif; ?>