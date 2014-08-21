<?php
//dpm($dataset_dto);
//dpm($dataset_type);
?>

<h3><?php print t('General Information') ?></h3>

<?php if (!empty($dataset_dto->description)): ?>
  <h5><?php print t('Description'); ?></h5>
  <p><?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?></p>
<?php endif; ?>

<h5><?php print t('Dataset Type'); ?></h5>
<p>
  <?php
  if (!empty($dataset_type->project)):
    echo t('Harmonization dataset');
  else:
    echo t('Study dataset');
  endif;
  ?>
</p>
