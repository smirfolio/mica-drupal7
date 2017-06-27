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
      <a title="<?php print $localize->getTranslation('edit') ?>"
         target="_blank"
         href="<?php print MicaClientPathProvider::dataset_draft_url($dataset_dto) ?>"
         class="btn btn-default">
        <i class="fa fa-pencil-square-o"></i> <?php print $localize->getTranslation('edit')?></a>
    <?php endif; ?>

    <?php if (variable_get_value('dataset_detailed_crosstab') && $draft_view === FALSE) : ?>
      <?php print MicaClientAnchorHelper::datasetCrosstab($dataset_dto, TRUE); ?>
    <?php endif; ?>

    <?php if (variable_get_value('dataset_detail_show_search_button')  && $draft_view === FALSE): ?>
      <?php print MicaClientAnchorHelper::datasetVariables(NULL, $dataset_dto->id, array('class' => 'btn btn-primary')) ?>
    <?php endif; ?>
  </div>

</div>

<div class="clearfix"></div>

<article class="bordered-article">

  <!-- OVERVIEW -->
  <section>
    <h2><?php print $localize->getTranslation('client.label.overview') ?></h2>

    <div class="row">
      <div class="col-lg-6 col-xs-12 lg-right-indent">
        <table class="table table-striped">
          <tbody>

          <?php if (!empty($dataset_dto->acronym)): ?>
            <tr>
              <th><?php print $localize->getTranslation('dataset.acronym') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($dataset_dto, 'acronym'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (variable_get_value('dataset_description_overview_field') && !empty($description)): ?>
            <tr>
              <th><?php print $localize->getTranslation('dataset.description') ?></th>
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
                  echo $localize->getTranslation('harmonization-dataset');
                else:
                  echo $localize->getTranslation('collection-dataset');
                endif;
                ?>
              </p>
            </td>
          </tr>
          <?php if ((!empty($dataset_dto->published) && $dataset_dto->published === TRUE ) || $draft_view === FALSE): ?>
            <tr>
              <th><?php print $localize->getTranslation('client.label.dataset.number-of-variables') ?></th>
              <td>
                <p>
                  <?php print MicaClientAnchorHelper::datasetVariables(empty($variables_dataset->total) ? 0 :
                    obiba_mica_commons_format_number($variables_dataset->total), $dataset_dto->id); ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>
      </div>
      <div class="col-lg-6 col-xs-12">
        <?php if (!empty($dataset_dto->attributes)): ?>
          <h4><?php print $localize->getTranslation('attributes') ?></h4>
          <p><?php print obiba_mica_dataset_attributes_tab($dataset_dto->attributes, 'maelstrom'); ?></p>
        <?php endif; ?>
      </div>
    </div>

  </section>

  <?php if (!empty($file_browser)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print $file_browser; ?>
    </section>
  <?php endif; ?>


  <section>
    <!-- NETWORKS -->
    <?php if (!empty($dataset_type_dto->networkTables)): ?>
      <div>
        <h2><?php print $localize->getTranslation('networks') ?></h2>

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
    <?php if (variable_get_value('dataset_show_studies') && ($dataset_type == "collection-dataset" || !empty($dataset_type_dto->studyTables))): ?>
      <h2>
        <?php
        if (!empty($dataset_type_dto->project)){
          echo $localize->getTranslation('studies');
        }
        elseif(!empty($dataset_type_dto->studyTable)){
          echo $localize->getTranslation('study.label');
        }
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
        <?php if (!empty($dataset_type_dto->studyTable)): ?>
        <div class="row">
          <div class="col-lg-6 col-xs-12">
            <table class="table table-striped">
              <tbody>
                <tr>
                  <th><?php print $localize->getTranslation('study.acronym') ?></th>
                  <td>
                    <p>
                      <?php print MicaClientAnchorHelper::study($dataset_type_dto->studyTable->studySummary); ?>
                    </p>
                  </td>
                </tr>
              <tr>
                <th><?php print $localize->getTranslation('study.name') ?></th>
                <td>
                  <p>
                    <?php print obiba_mica_commons_get_localized_field($dataset_type_dto->studyTable->studySummary, 'name'); ?>
                  </p>
                </td>
              </tr>
              <tr>
                <th><?php print $localize->getTranslation('study.population') ?></th>
                <td>
                  <?php $population_summary = NULL; ?>
                  <?php foreach ($dataset_type_dto->studyTable->studySummary->populationSummaries as $pop_summary):
                    if ($pop_summary->id == $dataset_type_dto->studyTable->populationId):
                      $population_summary = $pop_summary;
                      print !empty($dataset_type_dto->studyTable->studySummary->published)?MicaClientAnchorHelper::studyPopulationModal($pop_summary):
                        obiba_mica_commons_get_localized_field($pop_summary, 'name');
                      break;
                    endif;
                  endforeach; ?>
                </td>
              </tr>
              <tr>
                <th><?php print $localize->getTranslation('study.data-collection-event') ?></th>
                <td>
                  <?php $dce_anchor = NULL; ?>
                  <?php foreach ($population_summary->dataCollectionEventSummaries as $dce_summary):
                    if ($dce_summary->id == $dataset_type_dto->studyTable->dataCollectionEventId):
                      print !empty($dataset_type_dto->studyTable->studySummary->published)?MicaClientAnchorHelper::studyPopulationDceModal(
                        $dataset_type_dto->studyTable->studyId,
                        $dataset_type_dto->studyTable->populationId,
                        $dce_summary
                      ):obiba_mica_commons_get_localized_field($dce_summary, 'name');
                      break;
                    endif;
                  endforeach; ?>
                </td>
              </tr>
              <tr>
                <th><?php print $localize->getTranslation('search.study.design') ?></th>
                <td>
                  <?php print implode(', ',obiba_mica_study_translate_study_design_summary($dataset_type_dto->studyTable->studySummary->designs)); ?>
                </td>
              </tr>
              <tr>
                <th><?php print $localize->getTranslation('numberOfParticipants.participants') ?></th>
                <td>
                  <?php print isset($dataset_type_dto->studyTable->studySummary->targetNumber->noLimit) ? $localize->getTranslation('numberOfParticipants.no-limit') :
                    isset($dataset_type_dto->studyTable->studySummary->targetNumber->number) ?
                      obiba_mica_commons_format_number($dataset_type_dto->studyTable->studySummary->targetNumber->number) : NULL; ?>
                </td>
              </tr>
              <?php if (!empty($dataset_type_dto->studyTable->studySummary->countries)) : ?>
              <tr>
                <th><?php print $localize->getTranslation('client.label.countries') ?></th>
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
    <?php endif ?>
  </section>

  <!-- COVERAGE -->
  <div ng-controller="VariableCoverageChartController">
    <section id="coverage" ng-if="d3Configs && d3Configs.length">
      <h2><?php print $localize->getTranslation('variable-classifications') ?></h2>

      <div ng-repeat="d3Config in d3Configs">
        <obiba-nv-chart chart-config="d3Config"></obiba-nv-chart>
      </div>
    </section>
  </div>

  <!-- VARIABLES -->
  <?php if ($dataset_type != "collection-dataset" && (!isset($draft_view) || $draft_view !== TRUE)): ?>
    <section class="table-variables">
      <h2><?php print $localize->getTranslation('client.label.variable.harmonization') ?></h2>
      <?php print render($harmonization_table_legend); ?>
      <div id="download-btn">
        <a href="" class="btn btn-success pull-right"><i
            class='glyphicon glyphicon-download'></i> <?php print $localize->getTranslation('download') ?>
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
