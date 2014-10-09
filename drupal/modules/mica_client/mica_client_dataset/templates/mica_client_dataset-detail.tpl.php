<?php
//dpm($dataset_dto);
//dpm($dataset_type_dto);
//dpm($dataset_harmonizations_dto);
//dpm($dataset_variables_aggs);
?>

<div>
  <?php if (!empty($dataset_dto->description)): ?>
    <p><?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?></p>
  <?php endif; ?>
  <div class="pull-right md-bottom-margin">
    <?php
    print l(t('Search'), 'mica/search',
      array(
        'query' => array(
          'type' => 'variables',
          'query' => '{"variables":{"terms":{"datasetId":["' . $dataset_dto->id . '"]}}}'
        ),
        'attributes' => array('class' => 'btn btn-primary')
      ));
    ?>
    <?php
    print l(t('Coverage'), 'mica/coverage',
      array(
        'query' => array(
          'type' => 'variables',
          'query' => '{"variables":{"terms":{"datasetId":["' . $dataset_dto->id . '"]}}}'
        ),
        'attributes' => array('class' => 'btn btn-primary indent')
      ));
    ?>
  </div>
</div>


<article class="pull-left">
  <!-- OVERVIEW -->
  <section>
    <h3><?php print t('Overview') ?></h3>

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 lg-right-indent">
          <table class="table table-striped">
            <tbody>
            <?php if (!empty($dataset_dto->acronym)): ?>
              <tr>
                <td><h5><?php print t('Acronym') ?></h5></td>
                <td><p><?php print mica_client_commons_get_localized_field($dataset_dto, 'acronym'); ?></p></td>
              </tr>
            <?php endif; ?>

            <tr>
              <td><h5><?php print t('Entity Type'); ?></h5></td>
              <td><p><?php print t($dataset_dto->entityType); ?></p></td>
            </tr>

            <tr>
              <td><h5><?php print t('Dataset Type'); ?></h5></td>
              <td>
                <p>
                  <?php
                  if (!empty($dataset_type_dto->project)):
                    echo t('Harmonization dataset');
                  else:
                    echo t('Study dataset');
                  endif;
                  ?>
                </p>
              </td>
            </tr>
            </tbody>
          </table>
        </div>
        <div class="col-xs-6">
          <?php if (!empty($dataset_dto->attributes)): ?>
            <h5><?php print t('Attributes') ?></h5>
            <p><?php print mica_client_dataset_attributes_tab($dataset_dto->attributes, 'maelstrom'); ?></p>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </section>

  <!-- VARIABLES -->
  <section>
    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 lg-right-indent">
          <h3><?php print t('Variables') ?></h3>
          <table class="table table-striped">
            <tbody>
            <tr>
              <td><h5><?php print t('Number of variables') ?></h5></td>
              <td>
                <p>
                  <?php print empty($dataset_variables_aggs['totalHits']) ? 0 : $dataset_variables_aggs['totalHits']; ?>
                </p>
              </td>
            </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  </section>

  <!-- STUDIES -->
  <section>
    <h3><?php print t('Studies') ?></h3>
    <?php print mica_client_dataset_study_tables_table($dataset_type_dto) ?>
  </section>

  <!-- HARMONIZATION -->
  <?php if (!empty($dataset_harmonizations_dto)): ?>
    <section>
      <h3><?php print t('Harmonization') ?></h3>
      <?php print mica_client_dataset_harmonizations_table($dataset_type_dto, $dataset_harmonizations_dto) ?>
    </section>
  <?php endif; ?>
</article>