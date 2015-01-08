<?php
//dpm($dataset_dto);
//dpm($dataset_type_dto);
//dpm($variables_dataset);
//dpm($dataset_variables_aggs);
?>

<div>
  <div class="pull-right md-bottom-margin">
    <?php
    $query_array = array("variables" => array("terms" => array("datasetId" => $dataset_dto->id)));
    $query = MicaClient::create_query_dto_as_string($query_array);

    print l(t('Search Variables'), 'mica/search',

      array(
        'query' => array(
          'type' => 'variables',
          'query' => $query
        ),
        'attributes' => array('class' => 'btn btn-primary')
      ));
    ?>
    <?php
    print l(t('Coverage'), 'mica/coverage',
      array(
        'query' => array(
          'type' => 'variables',
          'query' => $query
        ),
        'attributes' => array('class' => 'btn btn-primary indent')
      ));
    ?>
  </div>
</div>

<div class="clearfix"></div>

<article>
  <!-- OVERVIEW -->
  <section>
    <h3><?php print t('Overview') ?></h3>

    <div class="row">
      <div class="col-lg-6 col-xs-12 lg-right-indent">
        <table class="table table-striped">
          <tbody>
          <?php if (!empty($dataset_dto->description)): ?>
            <tr>
              <td><h5><?php print t('Description') ?></h5></td>
              <td><p><?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?></p></td>
            </tr>
          <?php endif; ?>
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
          <tr>
            <td><h5><?php print t('Number of variables') ?></h5></td>
            <td>
              <p>
                <?php print MicaClientAnchorHelper::dataset_variables(empty($variables_dataset->total) ? 0 : $variables_dataset->total, $dataset_dto->id); ?>
              </p>
            </td>
          </tr>
          </tbody>
        </table>
      </div>
      <div class="col-lg-6 col-xs-12">
        <?php if (!empty($dataset_dto->attributes)): ?>
          <h5><?php print t('Attributes') ?></h5>
          <p><?php print mica_client_dataset_attributes_tab($dataset_dto->attributes, 'maelstrom'); ?></p>
        <?php endif; ?>
      </div>
    </div>

  </section>

  <!-- STUDIES -->
  <?php if ($dataset_type == "study-dataset" || !empty($dataset_type_dto->studyTables)): ?>
    <section>
      <h3>
        <?php
        if (!empty($dataset_type_dto->project)):
          echo t('Studies');
        else:
          echo t('Study');
        endif;
        ?>
      </h3>
      <?php if (!empty($dataset_type_dto->project)): ?>
        <div class="row">
          <div class="col-lg-12 col-xs-12">
            <div class="scroll-content-tab">
              <?php print mica_client_dataset_study_tables_table($dataset_type_dto) ?>
            </div>
          </div>
        </div>
      <?php else: ?>
        <div class="container-fluid">
          <div class="row">
            <div class="col-lg-6 col-xs-12">
            <table class="table table-striped">
                <tbody>
                <tr>
                  <td><h5><?php print t('Name') ?></h5></td>
                  <td>
                    <p>
                      <?php print l(mica_client_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'acronym') . ' - ' . mica_client_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'), 'mica/study/' . $dataset_type_dto->studyTable->studySummary->id . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'))); ?>
                    </p>
                  </td>
                </tr>
                <tr>
                  <td><h5><?php print t('Population') ?></h5></td>
                  <td>
                    <?php $population_summary = NULL; ?>
                    <?php foreach ($dataset_type_dto->studyTable->studySummary->populationSummaries as $pop_summary) {
                      if ($pop_summary->id == $dataset_type_dto->studyTable->populationId) {
                        $population_summary = $pop_summary;
                        break;
                      }
                    }
                    ?>
                    <?php print mica_client_commons_get_localized_field($population_summary, 'name'); ?>
                  </td>
                </tr>
                <tr>
                  <td><h5><?php print t('Data Collection Event') ?></h5></td>
                  <td>
                    <?php foreach ($population_summary->dataCollectionEventSummaries as $dce_summary) {
                      if ($dce_summary->id == $dataset_type_dto->studyTable->dataCollectionEventId) {
                        print mica_client_commons_get_localized_field($dce_summary, 'name');
                        break;
                      }
                    }
                    ?>
                  </td>
                </tr>
                <tr>
                  <td><h5><?php print t('Study Designs') ?></h5></td>
                  <td>
                    <?php print implode(', ', $dataset_type_dto->studyTable->studySummary->designs); ?>
                  </td>
                </tr>
                <tr>
                  <td><h5><?php print t('Target Number') ?></h5></td>
                  <td>
                    <?php print isset($dataset_type_dto->studyTable->studySummary->targetNumber->noLimit) ? t('No Limit') :
                      isset($dataset_type_dto->studyTable->studySummary->targetNumber->number) ? $dataset_type_dto->studyTable->studySummary->targetNumber->number : NULL; ?>
                  </td>
                </tr>
                <tr>
                  <td><h5><?php print t('Countries') ?></h5></td>
                  <td>
                    <?php print implode(', ', $dataset_type_dto->studyTable->studySummary->countries); ?>
                  </td>
                </tr>
                </tbody>
              </table>
            </div>
          </div>
        </div>
      <?php endif ?>
    </section>
  <?php endif ?>

  <!-- COVERAGE -->
  <?php if (!empty($coverage)): ?>
    <section>
      <h3><?php print t('Classifications Coverage') ?></h3>
      <?php foreach ($coverage as $taxonomy_coverage): ?>
        <h4><?php print mica_client_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'titles'); ?></h4>
        <p class="help-block">
          <?php print mica_client_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'descriptions'); ?>
        </p>
        <div class="scroll-content-tab">
          <?php print render($taxonomy_coverage['chart']); ?>
        </div>
      <?php endforeach ?>
    </section>
  <?php endif; ?>

  <!-- VARIABLES -->
  <?php if ($dataset_type == "study-dataset" || !empty($dataset_type_dto->studyTables)): ?>
    <section class="table-variables">
      <?php if ($dataset_type != "study-dataset"): ?>
        <h3><?php print t('Harmonization') ?></h3>
        <?php print render($harmonization_table_legend); ?>
        <div class="download-table">
          <a id="download-harmo-table" href="" class="btn btn-success pull-right sm-bottom-margin"><i
              class='glyphicon glyphicon-download'></i> <?php print t('Download') ?></a>
        </div>
        <div class="clearfix">
        </div>
      <?php else: ?>
        <h3><?php print t('Study variables') ?></h3>
      <?php endif; ?>
      <div id="variables-table"
        type-dataset="<?php print $dataset_type; ?>"
        id-dataset="<?php print $dataset_dto->id; ?>">

        <div class="row">
          <div class="col-lg-12 col-xs-12">
          <table class="table table-striped" id="table-variables"></table>
            </div>
          </div>
        </div>

      <div class="clearfix"></div>
    </section>
  <?php endif; ?>

</article>
