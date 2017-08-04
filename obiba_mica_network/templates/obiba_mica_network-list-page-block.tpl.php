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
?>

<div class="row sm-bottom-margin document-item-list flex-row" test-ref="network">
  <div class="col-md-2 hidden-xs hidden-sm text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
        class="img-responsive"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-N"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10 col-sm-12 col-xs-12">
    <div>
      <h4>
        <?php print MicaClientAnchorHelper::networkListItem($network); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php
          print MicaClientAnchorHelper::ellipses(
            t('Read more'),
            obiba_mica_commons_get_localized_field($network, 'description'),
            MicaClientPathProvider::NETWORK($network->id)
          );
          ?>
        </small>
      </p>
    </div>
    <div class="sm-top-margin">
      <?php
      $counts = $network->{'obiba.mica.CountStatsDto.networkCountStats'};
      $study_vars = $counts->studyVariables;
      $study_vars_caption = $study_vars < 2 ? $localize->getTranslation('metrics.mica.study-variable') : $localize->getTranslation('metrics.mica.study-variables');
      $individual_studies = $counts->individualStudies;
      $individual_studies_caption = $individual_studies < 2 ? $localize->getTranslation('global.individual-study') : $localize->getTranslation('global.individual-studies');
      $harmonization_studies = $counts->harmonizationStudies;
      $harmonization_studies_caption = $harmonization_studies < 2 ? $localize->getTranslation('global.harmonization-study') : $localize->getTranslation('harmonization-studies');
      $studies_with_vars = isset($counts->studiesWithVariables) ? $counts->studiesWithVariables : 0;
      $studies_with_vars_caption = $studies_with_vars < 2 ? $localize->getTranslation('metrics.mica.study-with-variables') : $localize->getTranslation('metrics.mica.studies-with-variables');
      $harmonization_studies_vars = isset($counts->dataschemaVariables) ? $counts->dataschemaVariables : 0;
      $harmonization_studies_vars_caption = $counts->dataschemaVariables < 2 ? $localize->getTranslation('metrics.mica.harmonization-study-variable') : $localize->getTranslation('metrics.mica.harmonization-study-variables');
      $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
      $dataset_caption = $datasets < 2 ? $localize->getTranslation('dataset.details') : $localize->getTranslation('datasets');
      ?>
      <?php if (!empty($individual_studies) && variable_get_value('networks_column_studies')): ?>
        <?php print MicaClientAnchorHelper::networkStudies(t('@count ' . $individual_studies_caption, array('@count' => $individual_studies)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'individualStudyCount'), 'study(in(Mica_study.className,Study))') ?>
      <?php endif ?>

      <?php if ($studies_with_vars > 0): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $studies_with_vars_caption, array('@count' => $studies_with_vars)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'studyWithVariablesCount'), 'variable(in(Mica_variable.variableType,Collected))', "studies") ?>
      <?php endif; ?>

      <?php if (!empty($study_vars) && variable_get_value('networks_column_study_variables')): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $study_vars_caption,
            array('@count' => obiba_mica_commons_format_number($study_vars))), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'studyVariableCount'), 'variable(in(Mica_variable.variableType,Collected))') ?>
      <?php endif ?>

      <?php if (!empty($harmonization_studies) && variable_get_value('networks_column_studies')): ?>
        <?php print MicaClientAnchorHelper::networkStudies(t('@count ' . $harmonization_studies_caption, array('@count' => $harmonization_studies)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'harmonizationStudyCount'), 'study(in(Mica_study.className,HarmonizationStudy))') ?>
      <?php endif ?>

      <?php if ($harmonization_studies_vars > 0): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $harmonization_studies_vars_caption, array('@count' => $harmonization_studies_vars)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'harmonizationStudyWithVariablesCount'), 'variable(in(Mica_variable.variableType,Dataschema))', "variables") ?>
      <?php endif; ?>

      <?php if (!empty($datasets) && (variable_get_value('networks_column_study_datasets') || variable_get_value('networks_column_harmonization_datasets'))): ?>
        <?php print MicaClientAnchorHelper::networkDatasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'datasetCount')) ?>
      <?php endif ?>

    </div>
  </div>
</div>
