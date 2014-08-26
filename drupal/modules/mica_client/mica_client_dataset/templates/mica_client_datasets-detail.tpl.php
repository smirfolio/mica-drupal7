<?php
//dpm($dataset_dto);
//dpm($dataset_type_dto);
//dpm($dataset_variables_aggs);
//dpm($dataset_studies_tab);
?>

<article>
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

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-3 right-indent">
          <h5><?php print t('Number of variables') ?></h5>

          <p>
            <?php print $dataset_variables_aggs['totalHits']; ?>
          </p>

          <?php
          print l(t('Search Variables'), 'mica/variables_search/dataset',
            array(
              'query' => array('child:datasetId[]' => 'datasetId.' . $dataset_dto->id),
              'attributes' => array('class' => 'btn btn-primary')
            ));
          ?>
        </div>
        <div class="col-xs-9">
          <!-- Variable aggregations can be reported here -->
          <div class="alert alert-info" role="alert"><strong>TODO</strong> charts here</div>
        </div>
      </div>
    </div>
  </section>

  <section>
    <h3><?php print t('Studies') ?></h3>
    <?php print $dataset_studies_tab ?>
  </section>
</article>