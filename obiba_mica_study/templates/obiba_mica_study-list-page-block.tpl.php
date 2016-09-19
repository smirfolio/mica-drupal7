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

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-md-2 hidden-xs hidden-sm text-center">
    <?php if (!empty($logo_url)): ?>
      <img src="<?php print $logo_url ?>"
        class="img-responsive"/>
    <?php else : ?>
      <h1 class="big-character">
        <span class="t_badge color_light i-obiba-S"></span>
      </h1>
    <?php endif; ?>
  </div>
  <div class="col-md-10  col-sm-12 col-xs-12">
    <div>
      <h4>
        <?php print MicaClientAnchorHelper::studyListItem($study); ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php if (variable_get_value('studies_list_show_trimmed_description_study')): ?>
            <?php  print MicaClientAnchorHelper::ellipses(
              t('Read more'),
              obiba_mica_commons_get_localized_field($study, 'objectives'),
              MicaClientPathProvider::study($study->id)
            ); ?>
          <?php else: ?>
            <div class="objectives-studies">

              <?php $first_paragraph = explode('</p>', obiba_mica_commons_get_localized_field($study, 'objectives')); ?>
              <div><?php print $first_paragraph['0'] ?></div>
              <div class="objectives-trimed collapse"
                id="objectives-<?php print $study->id; ?>">
                <?php if (!empty($first_paragraph['1'])): ?>
                  <?php print $first_paragraph['1'] ?>
                <?php else: ?>
                  <?php print obiba_mica_commons_get_localized_field($study, 'objectives'); ?>
                <?php endif; ?>
              </div>
              <?php if (count($first_paragraph) > 2): ?>
                <button class="btn btn-primary btn-xs 5-top-margin trim-studies" type="button" data-toggle="collapse"
                  data-target="#objectives-<?php print $study->id; ?>" aria-expanded="false"
                  aria-controls="collapseExample" id="btn-objectives-<?php print $study->id; ?>">
                  <?php print t('Read more'); ?>
                </button>
              <?php endif; ?>

            </div>
          <?php  endif; ?>
        </small>
      </p>
    </div>
    <?php if (variable_get_value('studies_list_show_study_sup_info')): ?>
    <blockquote-small class="help-block">
          <?php foreach ($network_digests as $digest) {
            $names = array();
            array_push($names, obiba_mica_commons_get_localized_field($digest, 'name'));
          }

          if (!empty($names)) {
            print t('Member of ') . implode(', and', $names);
          }
          ?>
        <?php if (!empty($study->designs) || !empty($study->targetNumber)) : ?>

            <?php if (!empty($study->designs)): print t('Study design') ?>:
              <span><?php print implode(', ', obiba_mica_commons_clean_string($study->designs)) ?></span>
            <?php endif; ?>
            <?php
            if (!empty($study->targetNumber)):
              print (empty($study->designs) ? '' : '; ') . variable_get_value('study_target_number_participant_label');
              ?>:
              <span>
              <?php print $study->targetNumber->noLimit === TRUE
                ? t('No limits')
                : (empty($study->targetNumber->number) ? t('n/a') : obiba_mica_commons_format_number($study->targetNumber->number))
              ?>
            </span>
            <?php endif; ?>
      </blockquote-small>
        <?php endif; ?>
      <div class="sm-top-margin">
        <?php
        $counts = $study->{'obiba.mica.CountStatsDto.studyCountStats'};
        $vars = $counts->variables;
        $var_caption = $vars < 2 ? t('variable') : t('variables');
        $study_vars = !empty($counts->studyVariables)?$counts->studyVariables:NULL;
        $study_var_caption = $study_vars < 2 ? t('study variable') : t('study variables');
        $dataschema_vars = !empty($counts->dataschemaVariables)?$counts->dataschemaVariables:NULL;
        $dataschema_var_caption = $dataschema_vars < 2 ? t('dataschema variable') : t('dataschema variables');
        $datasets = $counts->studyDatasets + $counts->harmonizationDatasets;
        $dataset_caption = $datasets < 2 ? t('dataset') : t('datasets');
        $networks = !empty($counts->networks)?$counts->networks:NULL;
        $network_caption = $networks < 2 ? t('network') : t('networks');
        ?>
        <?php if (!empty($networks) && variable_get_value('studies_column_networks')): ?>
            <?php print MicaClientAnchorHelper::studyNetworks(t('@count ' . $network_caption, array('@count' => $networks)), $study->id, 'btn-default btn-xxs') ?>
        <?php endif ?>
        <?php if (!empty($datasets) && (variable_get_value('studies_column_study_datasets') || variable_get_value('studies_column_harmonization_datasets'))): ?>
            <?php print MicaClientAnchorHelper::studyDatasets(t('@count ' . $dataset_caption, array('@count' => $datasets)), $study->id, 'btn-default btn-xxs') ?>
        <?php endif ?>
        <?php if (!empty($vars) && variable_get_value('studies_column_variables')): ?>
            <?php print MicaClientAnchorHelper::studyVariables(t('@count ' . $var_caption, array('@count' => obiba_mica_commons_format_number($vars))), $study->id, TRUE, NULL, 'btn-default btn-xxs') ?>
        <?php endif ?>
        <?php if (!empty($study_vars) && variable_get_value('studies_column_study_variables')): ?>
          <?php print MicaClientAnchorHelper::studyVariables(t('@count ' . $study_var_caption, array('@count' => obiba_mica_commons_format_number($study_vars))), $study->id, TRUE, 'variable(in(Mica_variable.variableType,Study))', 'btn-default btn-xxs') ?>
        <?php endif ?>
        <?php if (!empty($dataschema_vars) && variable_get_value('studies_column_dataschema_variables')): ?>
          <?php print MicaClientAnchorHelper::studyVariables(t('@count ' . $dataschema_var_caption, array('@count' => obiba_mica_commons_format_number($dataschema_vars))), $study->id, TRUE, 'variable(in(Mica_variable.variableType,Dataschema))', 'btn-default btn-xxs') ?>
        <?php endif ?>
      </div>
    <?php endif; ?>
  </div>
</div>

