<?php //dpm($type_dataset); ?>
<?php if (!empty($dataset)): ?>
  <?php
  $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
  ?>
  <div class="lg-bottom-margin">
    <h4>
      <?php
      print l(mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . $dataset_name,
        'mica/' . mica_client_dataset_type($dataset) . '/' . $dataset->id); ?>
    </h4>
  </div>
<?php endif; ?>