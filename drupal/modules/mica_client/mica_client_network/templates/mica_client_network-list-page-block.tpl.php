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
    </div>
  <?php endforeach; ?>
<?php endif; ?>