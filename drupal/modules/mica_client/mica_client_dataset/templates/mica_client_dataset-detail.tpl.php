<?php
//dpm($dataset_dto);
//dpm($dataset_type_dto);
//dpm($variables_dataset);
//dpm($dataset_variables_aggs);
?>

<div>
  <?php if (!empty($dataset_dto->description)): ?>
    <p><?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?></p>
  <?php endif; ?>
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

            <tr>
              <td>
                <h5>
                  <?php
                  if (!empty($dataset_type_dto->project)):
                    echo t('Studies');
                  else:
                    echo t('Study');
                  endif;
                  ?>
                </h5>
              </td>
              <td>
                <?php if (!empty($dataset_type_dto->project)): ?>
                  <ul>
                    <?php foreach ($dataset_type_dto->studyTables as $studyTable): ?>
                      <li>
                        <?php print l(mica_client_commons_get_localized_field($studyTable->studySummary, 'name'), 'mica/study/' . $studyTable->studySummary->id . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($studyTable->studySummary, 'name'))); ?>
                      </li>
                    <?php endforeach ?>
                  </ul>
                <?php else: ?>
                  <?php print l(mica_client_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'), 'mica/study/' . $dataset_type_dto->studyTable->studySummary->id . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'))); ?>
                <?php endif ?>
              </td>
            </tr>
            <tr>
              <td><h5><?php print t('Number of variables') ?></h5></td>
              <td>
                <p>
                  <?php print empty($variables_dataset->total) ? 0 : $variables_dataset->total; ?>
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

  <!-- STUDIES -->
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
      <?php print mica_client_dataset_study_tables_table($dataset_type_dto) ?>
    <?php else: ?>
      <div class="container-fluid">
        <div class="row">
          <div class="col-xs-6 lg-right-indent">
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
  <?php if (!empty($coverage_dataset)): ?>
    <section>
      <h3><?php print t('Vocabularies coverage') ?></h3>
      <?php print render($coverage_dataset); ?>
    </section>
  <?php endif; ?>

  <!-- HARMONIZATION -->
  <?php if (!empty($variables_dataset->variables) || !empty($variables_dataset->variableHarmonizations)): ?>
    <?php if (!empty($variables_dataset->harmonization)): ?>
    <section>
      <h3><?php print t('Harmonization') ?></h3>

      <div>
        <?php print render($form_search); ?>
      </div>
      <?php print render($variables_table); ?>
    </section>
  <?php endif; ?>

  <!-- STUDY VARIABLES -->
  <?php if (!empty($variables_dataset->study)): ?>
    <section>
      <h3><?php print t('Study variables') ?></h3>

      <div>
        <?php print render($form_search); ?>
      </div>
      <?php print render($variables_table); ?>
    </section>
  <?php endif; ?>
  <?php endif; ?>
</article>
