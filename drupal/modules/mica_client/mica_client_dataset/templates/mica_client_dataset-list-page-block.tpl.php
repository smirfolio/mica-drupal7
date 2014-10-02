<?php if (!empty($list_dataset) && !empty($list_dataset->datasets)): ?>

  <?php foreach ($list_dataset->datasets as $dataset) :
    $dataset_name = mica_client_commons_get_localized_field($dataset, 'name');
    ?>
    <div class="lg-bottom-margin">
      <h4>
        <?php
        print l(mica_client_commons_get_localized_field($dataset, 'acronym') . ' - ' . $dataset_name,
          'mica/dataset/' . $dataset->id); ?>
      </h4>
    </div>
  <?php endforeach; ?>
<?php endif; ?>