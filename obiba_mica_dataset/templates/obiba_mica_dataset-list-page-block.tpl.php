<?php
/**
 * @file
 * Code for the obiba_mica_dataset modules.
 */

?>
  <!--
    ~ Copyright (c) 2015 OBiBa. All rights reserved.
    ~
    ~ This program and the accompanying materials
    ~ are made available under the terms of the GNU Public License v3.0.
    ~
    ~ You should have received a copy of the GNU General Public License
    ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
    -->

<?php if (!empty($dataset)): ?>
  <div class="row sm-bottom-margin document-item-list flex-row">
    <div class="col-md-12  col-sm-12 col-xs-12">
      <h4>
        <?php
        print MicaClientAnchorHelper::datasetListItem($dataset);
        ?>
      </h4>
      <hr class="no-margin">
      <p class="md-top-margin">
        <small>
          <?php
          print MicaClientAnchorHelper::ellipses(
            t('Read more'),
            obiba_mica_commons_get_localized_field($dataset, 'description'),
            'mica/' . obiba_mica_dataset_type($dataset) . '/' . $dataset->id
          );
          ?>
        </small>
      </p>
      <div>
        <?php
        $counts = $dataset->{'obiba.mica.CountStatsDto.datasetCountStats'};
        $variables = $counts->variables;
        $vars_caption = $variables < 2 ? t('variable') : t('variables');
        $studies = $counts->studies;
        $studies_caption = $studies < 2 ? t('study') : t('studies');
        $networks = $counts->networks;
        $network_caption = $networks < 2 ? t('network') : t('networks');
        ?>
        <?php if (!empty($networks) && variable_get_value('datasets_column_networks')): ?>
          <span class="label label-default rounded right-indent">
            <?php print MicaClientAnchorHelper::datasetNetworks(t('@count @networkCaption',
              array('@count' => $networks, '@networkCaption' => $network_caption)), $dataset->id) ?>
          </span>
        <?php endif ?>
        <?php if (!empty($studies) && variable_get_value('datasets_column_studies')): ?>
          <span class="label label-default rounded right-indent">
            <?php print MicaClientAnchorHelper::datasetStudies(t('@count @studiesCaption',
              array('@count' => $studies, '@studiesCaption' => $studies_caption)), $dataset->id) ?>
          </span>
        <?php endif ?>
        <?php if (!empty($variables) && variable_get_value('datasets_column_variables')): ?>
          <span class="label label-default rounded">
            <?php print MicaClientAnchorHelper::datasetVariables(t('@count @vars',
              array('@count' => obiba_mica_commons_format_number($variables), '@vars' => $vars_caption)), $dataset->id) ?>
          </span>
        <?php endif ?>
      </div>
    </div>
  </div>

  <?php
  $dataset_name = obiba_mica_commons_get_localized_field($dataset, 'name');
  ?>
<?php endif; ?>
