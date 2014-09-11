<?php
//dpm($network_dto);
?>

<?php if (!empty($network_dto->description)): ?>
  <p><?php print mica_client_commons_get_localized_field($network_dto, 'description'); ?></p>
<?php endif; ?>

<article>
  <section>
    <h3><?php print t('Overview') ?></h3>

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 right-indent">
          <?php if (!empty($network_dto->acronym)): ?>
            <h5><?php print t('Acronym') ?></h5>
            <p><?php print mica_client_commons_get_localized_field($network_dto, 'acronym'); ?></p>
          <?php endif; ?>
        </div>
        <div class="col-xs-6">
          <?php if (!empty($network_dto->attributes)): ?>
            <h5><?php print t('Attributes') ?></h5>
            <p><?php print mica_client_dataset_attributes_tab($network_dto->attributes, 'maelstrom'); ?></p>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </section>

  <section>
    <h3><?php print t('Studies') ?></h3>
    <?php print mica_client_network_study_table($network_dto) ?>
  </section>

</article>