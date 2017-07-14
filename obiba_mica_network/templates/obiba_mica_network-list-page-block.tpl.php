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
      $variables = $counts->variables;
      $vars_caption = $variables < 2 ? $localize->getTranslation('search.variable.facet-label') : $localize->getTranslation('variables');
      $study_vars = $counts->studyVariables;
      $study_vars_caption = $study_vars < 2 ? $localize->getTranslation('client.label.study-variable') : $localize->getTranslation('client.label.study-variables');
      $dataschema_vars = $counts->dataschemaVariables;
      $dataschema_vars_caption = $dataschema_vars < 2 ? $localize->getTranslation('client.label.dataschema-variable') : $localize->getTranslation('client.label.dataschema-variables');
      $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
      $dataset_caption = $datasets < 2 ? $localize->getTranslation('dataset.details') : $localize->getTranslation('datasets');
      $individual_studies = $counts->individualStudies;
      $individual_studies_caption = $individual_studies > 2 ? $localize->getTranslation('individual-studies') : $localize->getTranslation('global.individual-study');
      $harmonization_studies = $counts->harmonizationStudies;
      $harmonization_studies_caption = $harmonization_studies > 2 ? $localize->getTranslation('global.harmonized-studies') : $localize->getTranslation('harmonized-study');
      $studies_with_vars = isset($counts->studiesWithVariables) ? $counts->studiesWithVariables : 0;
      $studies_with_vars_caption = $studies_with_vars < 2 ? $localize->getTranslation('metrics.mica.study-with-variables') : $localize->getTranslation('metrics.mica.studies-with-variables');
      $harmonization_studies_with_vars = isset($counts->harmonizationStudiesWithVariables) ? $counts->harmonizationStudiesWithVariables : 0;
      $harmonization_studies_with_vars_caption = $harmonization_studies_with_vars < 2 ? $localize->getTranslation('metrics.mica.harmonization-study-with-variables') : $localize->getTranslation('metrics.mica.harmonization-studies-with-variables');
      ?>
      <?php if (!empty($individual_studies) && variable_get_value('networks_column_studies')): ?>
        <?php print MicaClientAnchorHelper::networkStudies(t('@count ' . $individual_studies_caption, array('@count' => $individual_studies)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'harmonizationStudyCount'), 'study(in(Mica_study.className,Study))') ?>
      <?php endif ?>

      <?php if ($studies_with_vars > 0): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $studies_with_vars_caption, array('@count' => $studies_with_vars)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'studyWithVariablesCount'), 'variable(in(Mica_variable.variableType,Collected))', "studies") ?>
      <?php endif; ?>

      <?php if (!empty($harmonization_studies) && variable_get_value('networks_column_studies')): ?>
        <?php print MicaClientAnchorHelper::networkStudies(t('@count ' . $harmonization_studies_caption, array('@count' => $harmonization_studies)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'harmonizationStudyCount'), 'study(in(Mica_study.className,HarmonizationStudy))') ?>
      <?php endif ?>

      <?php if ($harmonization_studies_with_vars > 0): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $harmonization_studies_with_vars_caption, array('@count' => $harmonization_studies_with_vars)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'harmonizationStudyWithVariablesCount'), 'variable(in(Mica_variable.variableType,Dataschema))', "studies") ?>
      <?php endif; ?>

      <?php if (!empty($datasets) && (variable_get_value('networks_column_study_datasets') || variable_get_value('networks_column_harmonization_datasets'))): ?>
            <?php print MicaClientAnchorHelper::networkDatasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'datasetCount')) ?>
      <?php endif ?>

      <?php if (!empty($variables) && variable_get_value('networks_column_variables')): ?>
            <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $vars_caption,
              array('@count' => obiba_mica_commons_format_number($variables))), $network->id, array('class' => 'btn-default btn-xxs')) ?>
      <?php endif ?>

      <?php if (!empty($study_vars) && variable_get_value('networks_column_study_variables')): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $study_vars_caption,
            array('@count' => obiba_mica_commons_format_number($study_vars))), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'studyVariableCount'), 'variable(in(Mica_variable.variableType,Collection))') ?>
      <?php endif ?>

      <?php if (!empty($dataschema_vars) && variable_get_value('networks_column_dataschema_variables')): ?>
        <?php print MicaClientAnchorHelper::networkVariables(t('@count ' . $dataschema_vars_caption,
            array('@count' => obiba_mica_commons_format_number($dataschema_vars))), $network->id, array('class' => 'btn-default btn-xxs', 'test-ref' => 'dataschemaVariableCount'), 'variable(in(Mica_variable.variableType,Dataschema))') ?>
      <?php endif ?>
    </div>
  </div>
</div>
