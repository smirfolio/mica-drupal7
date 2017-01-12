<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Code for the obiba_mica_dataset modules.
 */

?>

<?php
$description = empty($dataset_dto->description) ? NULL : obiba_mica_commons_get_localized_field($dataset_dto, 'description');
?>

<div>
  <?php if (!variable_get_value('dataset_description_overview_field') && !empty($description)): ?>
    <p class="md-top-margin">
      <?php print obiba_mica_commons_markdown($description); ?>
    </p>
  <?php endif; ?>

  <div class="pull-right md-bottom-margin">
    <?php if ($can_edit_draf_document): ?>
      <a title="<?php print t('Edit') ?>"
         target="_blank"
         href="<?php print MicaClientPathProvider::dataset_draft_url($dataset_dto) ?>"
         class="btn btn-default">
        <i class="fa fa-pencil-square-o"></i> <?php print t('Edit')?></a>
    <?php endif; ?>

    <?php if (variable_get_value('dataset_detailed_crosstab')) : ?>
      <?php print MicaClientAnchorHelper::datasetCrosstab($dataset_dto, TRUE); ?>
    <?php endif; ?>

    <?php if (variable_get_value('dataset_detail_show_search_button')): ?>
      <?php print MicaClientAnchorHelper::datasetVariables(NULL, $dataset_dto->id, array('class' => 'btn btn-primary')) ?>
    <?php endif; ?>
  </div>

</div>

<div class="clearfix"></div>

<article class="bordered-article">

  <!-- OVERVIEW -->
  <section>
    <h2><?php print t('Overview') ?></h2>

    <div class="row">
      <div class="col-lg-6 col-xs-12 lg-right-indent">
        <table class="table table-striped">
          <tbody>

          <?php if (!empty($dataset_dto->acronym)): ?>
            <tr>
              <th><?php print t('Acronym') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($dataset_dto, 'acronym'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (variable_get_value('dataset_description_overview_field') && !empty($description)): ?>
            <tr>
              <th><?php print t('Description') ?></th>
              <td>
                <p><?php print obiba_mica_commons_markdown($description); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <tr>
            <th><?php print $localize->getTranslation('client.label.dataset.dataset-type'); ?></th>
            <td>
              <p>
                <?php
                if (!empty($dataset_type_dto->project)):
                  echo t('Harmonization Dataset');
                else:
                  echo t('Study Dataset');
                endif;
                ?>
              </p>
            </td>
          </tr>
          <tr>
            <th><?php print $localize->getTranslation('client.label.dataset.number-of-variables') ?></th>
            <td>
              <p>
                <?php print MicaClientAnchorHelper::datasetVariables(empty($variables_dataset->total) ? 0 :
                  obiba_mica_commons_format_number($variables_dataset->total), $dataset_dto->id); ?>
              </p>
            </td>
          </tr>
          </tbody>
        </table>
      </div>
      <div class="col-lg-6 col-xs-12">
        <?php if (!empty($dataset_dto->attributes)): ?>
          <h4><?php print t('Attributes') ?></h4>
          <p><?php print obiba_mica_dataset_attributes_tab($dataset_dto->attributes, 'maelstrom'); ?></p>
        <?php endif; ?>
      </div>
    </div>

  </section>

  <?php if (!empty($attachments)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print (!empty($file_browser) ? $file_browser : $attachments); ?>
    </section>
  <?php endif; ?>


  <section>
    <!-- NETWORKS -->
    <?php if (!empty($dataset_type_dto->networkTables)): ?>
      <div>
        <h2><?php print variable_get_value('networks_section_label') ?></h2>

        <div id="networks-table">
          <div class="row">
            <div class="col-lg-12 col-xs-12">
              <table class="table table-striped" id="table-networks"></table>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <!-- STUDIES -->
    <?php if (variable_get_value('dataset_show_studies') && ($dataset_type == "study-dataset" || !empty($dataset_type_dto->studyTables))): ?>
      <h2>
        <?php
        if (!empty($dataset_type_dto->project)):
          echo t('Studies');
        else:
          echo t('Study');
        endif;
        ?>
      </h2>
      <?php if (!empty($dataset_type_dto->project)): ?>
        <div id="studies-table">
          <div class="row">
            <div class="col-lg-12 col-xs-12">
              <table class="table table-striped" id="table-studies"></table>
            </div>
          </div>
        </div>
      <?php else: ?>
        <div class="row">
          <div class="col-lg-6 col-xs-12">
            <table class="table table-striped">
              <tbody>
              <tr>
                <th><?php print t('Acronym') ?></th>
                <td>
                  <p>
                    <?php print MicaClientAnchorHelper::study($dataset_type_dto->studyTable->studySummary); ?>
                  </p>
                </td>
              </tr>
              <tr>
                <th><?php print t('Name') ?></th>
                <td>
                  <p>
                    <?php print obiba_mica_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'); ?>
                  </p>
                </td>
              </tr>
              <tr>
                <th><?php print t('Population') ?></th>
                <td>
                  <?php $population_summary = NULL; ?>
                  <?php foreach ($dataset_type_dto->studyTable->studySummary->populationSummaries as $pop_summary):
                    if ($pop_summary->id == $dataset_type_dto->studyTable->populationId):
                      $population_summary = $pop_summary;
                      print MicaClientAnchorHelper::studyPopulationModal($pop_summary);
                      break;
                    endif;
                  endforeach; ?>
                </td>
              </tr>
              <tr>
                <th><?php print t('Data Collection Event') ?></th>
                <td>
                  <?php $dce_anchor = NULL; ?>
                  <?php foreach ($population_summary->dataCollectionEventSummaries as $dce_summary):
                    if ($dce_summary->id == $dataset_type_dto->studyTable->dataCollectionEventId):
                      print MicaClientAnchorHelper::studyPopulationDceModal(
                        $dataset_type_dto->studyTable->studyId,
                        $dataset_type_dto->studyTable->populationId,
                        $dce_summary
                      );
                      break;
                    endif;
                  endforeach; ?>
                </td>
              </tr>
              <tr>
                <th><?php print t('Study Design') ?></th>
                <td>
                  <?php print implode(', ', obiba_mica_commons_clean_string($dataset_type_dto->studyTable->studySummary->designs)); ?>
                </td>
              </tr>
              <tr>
                <th><?php print variable_get_value('study_target_number_participant_label') ?></th>
                <td>
                  <?php print isset($dataset_type_dto->studyTable->studySummary->targetNumber->noLimit) ? t('No Limit') :
                    isset($dataset_type_dto->studyTable->studySummary->targetNumber->number) ?
                      obiba_mica_commons_format_number($dataset_type_dto->studyTable->studySummary->targetNumber->number) : NULL; ?>
                </td>
              </tr>
              <?php if (!empty($dataset_type_dto->studyTable->studySummary->countries)) : ?>
              <tr>
                <th><?php print t('Countries') ?></th>
                <td>
                  <?php print obiba_mica_commons_countries($dataset_type_dto->studyTable->studySummary->countries); ?>
                </td>
              </tr>
              <?php endif; ?>
              </tbody>
            </table>
          </div>
        </div>
      <?php endif ?>
    <?php endif ?>
  </section>

  <!-- COVERAGE -->
  <div ng-controller="VariableCoverageChartController">
    <section id="coverage" ng-if="d3Configs && d3Configs.length">
      <h2><?php print t('Variables Classification') ?></h2>

      <div ng-repeat="d3Config in d3Configs">
        <obiba-nv-chart chart-config="d3Config"></obiba-nv-chart>
      </div>
    </section>
  </div>

  <!-- VARIABLES -->
  <?php if ($dataset_type != "study-dataset"): ?>
    <section class="table-variables">
      <h2><?php print $localize->getTranslation('client.label.variable.harmonization') ?></h2>
      <?php print render($harmonization_table_legend); ?>
      <div id="download-btn">
        <a href="" class="btn btn-success pull-right"><i
            class='glyphicon glyphicon-download'></i> <?php print t('Download') ?>
        </a>
      </div>
      <div class="clearfix">
      </div>
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
<?php if (!empty($modals)): ?>
  <?php if (!empty($modals['population'])): ?>
    <?php print render($modals['population'][0]); ?>
  <?php endif; ?>
  <?php if (!empty($modals['dce'])): ?>
    <?php print render($modals['dce']); ?>
  <?php endif; ?>
<?php endif; ?>
