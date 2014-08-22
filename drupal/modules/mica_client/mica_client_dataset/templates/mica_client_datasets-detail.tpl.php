<?php
//dpm($dataset_dto);
//dpm($dataset_type_dto);
//dpm($dataset_variables_aggs);
?>

<section>
  <h3><?php print t('General Information') ?></h3>

  <div>
    <?php if (!empty($dataset_dto->description)): ?>
      <h5><?php print t('Description'); ?></h5>
      <p><?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?></p>
    <?php endif; ?>

    <h5><?php print t('Dataset Type'); ?></h5>

    <p>
      <?php
      if (!empty($dataset_type_dto->project)):
        echo t('Harmonization dataset');
      else:
        echo t('Study dataset');
      endif;
      ?>
    </p>

  </div>
</section>

<section>
  <h3><?php print t('Variables') ?></h3>

  <div>

    <h5><?php print t('Number of variables') ?></h5>
    <p>
      <?php
      print $dataset_variables_aggs['totalHits'];
      ?>
    </p>

    <!-- Variable aggregations can be reported here -->

    <?php
    print l(t('Search Variables'), 'mica/variables_search/dataset',
      array(
        'query' => array('child:datasetId[]' => 'datasetId.' . $dataset_dto->id),
        'attributes' => array('class' => 'btn btn-primary')
      ));
    ?>
  </div>
</section>