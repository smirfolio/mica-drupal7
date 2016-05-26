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

<article class="bordered-article">
  <section>
    <div class="row">
      <div class="col-lg-6 col-xs-12 ">
        <h2><?php print t('Overview') ?></h2>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($variable_dto->label)): ?>
            <tr>
              <th><?php print t('Label') ?></th>
              <td><?php print $variable_dto->label; ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($variable_dto->description)): ?>
            <tr>
              <th><?php print t('Description') ?></th>
              <td><p><?php print $variable_dto->description; ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (variable_get_value('variable_show_studies') && !empty($variable_dto->studySummaries)): ?>
            <tr>
              <th>
                <?php if ($variable_dto->variableType == 'Dataschema') :
                  print t('Studies');
                else :
                  print t('Study');
                endif;
                ?>
              </th>
              <td>
                <?php if ($variable_dto->variableType == 'Dataschema'): ?>
                  <ul class="list-unstyled">
                    <?php foreach ($variable_dto->studySummaries as $study_summary): ?>
                      <li><?php print MicaClientAnchorHelper::study($study_summary); ?></li>
                    <?php endforeach ?>
                  </ul>
                <?php elseif (!empty($variable_dto->studySummaries)): ?>
                  <?php print MicaClientAnchorHelper::study($variable_dto->studySummaries[0]); ?>
                <?php endif ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($variable_dto->datasetId)): ?>
            <tr>
              <th><?php print t('Dataset'); ?></th>
              <td>
                <p>
                  <?php print MicaClientAnchorHelper::variableDataset($variable_dto); ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <tr>
            <th><?php print t('Value Type'); ?></th>
            <td>
              <p><?php print t('@valueType', array('@valueType' => $variable_dto->valueType)); ?></p>
            </td>
          </tr>

          <?php if (!empty($variable_dto->unit)): ?>
            <tr>
              <th><?php print t('Unit'); ?></th>
              <td>
                <p><?php print t('@varUnit', array('@varUnit' => $variable_dto->unit)); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <tr>
            <th><?php print t('Variable Type'); ?></th>
            <td>
              <p>
                <?php print t('@type Variable', array('@type' =>
                  $variable_dto->variableType)); ?>
                <?php if ($variable_dto->variableType == 'Harmonized'): ?>
                  <?php print '(' . MicaClientAnchorHelper::variableHarmonized($variable_dto) . ')'; ?>
                <?php endif; ?>
              </p>
            </td>
          </tr>

          <?php if (!empty($variable_dto->comment)): ?>
            <tr>
              <th><?php print t('Comment'); ?></th>
              <td><p><?php print $variable_dto->comment; ?></p></td>
            </tr>
          <?php endif; ?>


          </tbody>
        </table>
      </div>
      <div class="col-lg-6 col-xs-12">
        <!-- Taxonomy terms -->
        <?php if (!empty($variable_dto->termAttributes)): ?>
          <h2><?php print t('Classification') ?></h2>
          <table class="table table-striped">
            <tbody>
            <?php foreach ($variable_dto->termAttributes as $term_attributes) : ?>
              <tr>
                <td colspan="2" data-toggle="tooltip"
                  title="<?php print obiba_mica_commons_get_localized_field($term_attributes->taxonomy, 'descriptions'); ?>">
                  <p class="help-block">
                    <?php print obiba_mica_commons_get_localized_field($term_attributes->taxonomy, 'titles'); ?>
                  </p>
                </td>
              </tr>
              <?php foreach ($term_attributes->vocabularyTerms as $term_attribute) : ?>
                <tr>

                  <th data-toggle="tooltip"
                    title="<?php print obiba_mica_commons_get_localized_field($term_attribute->vocabulary, 'descriptions'); ?>">
                    <?php print obiba_mica_commons_get_localized_field($term_attribute->vocabulary, 'titles'); ?>
                  </th>
                  <td>
                    <?php if (count($term_attribute->terms == 1)): ?>
                      <p data-toggle="tooltip"
                        title="<?php print obiba_mica_commons_get_localized_field($term_attribute->terms[0], 'descriptions'); ?>">
                        <?php print obiba_mica_commons_get_localized_field($term_attribute->terms[0], 'titles'); ?>
                      </p>
                    <?php else: ?>
                      <ul class="list-unstyled">
                        <?php foreach ($term_attribute->terms as $term) : ?>
                          <li data-toggle="tooltip"
                            title="<?php print obiba_mica_commons_get_localized_field($term, 'descriptions'); ?>">
                            <?php print obiba_mica_commons_get_localized_field($term, 'titles'); ?>
                          </li>
                        <?php endforeach; ?>
                      </ul>
                    <?php endif; ?>
                  </td>
                </tr>
              <?php endforeach; ?>
            <?php endforeach; ?>

            </tbody>
          </table>
        <?php endif; ?>

      </div>
    </div>

  </section>

  <!-- CATEGORIES -->
  <?php if (!empty($variable_dto->categories)): ?>
    <section>
      <h2><?php print t('Categories') ?></h2>

      <div class="row">
        <div class="col-md-6 col-sm-12">
          <?php print obiba_mica_dataset_variable_get_categories($variable_dto->categories); ?>
        </div>
      </div>
    </section>
  <?php endif; ?>

  <!-- STATISTICS -->
  <?php if (variable_get_value('mica_statistics')): ?>
    <section id="section-statistics">
      <h2>
        <?php print t('Statistics') ?>
        <?php if (strcasecmp($variable_dto->nature, 'CATEGORICAL') === 0 && $variable_dto->variableType !== 'Harmonized'): ?>
          <span class="pull-right">
        <?php if (variable_get_value('mica_statistics')) :
          print MicaClientAnchorHelper::variableCrosstab($variable_dto, TRUE);
        endif;
        ?>
      </span>
        <?php endif; ?>
      </h2>
      <?php
      $column_for_detail_statistics = 6;
      if (!variable_get_value('dataset_detailed_var_stats') && $variable_dto->variableType == 'Dataschema') : ?>
        <p><?php print t('Cumulative Summary of all Studies:') ?></p>
      <?php endif; ?>
      <?php if ($variable_dto->variableType == 'Dataschema' && variable_get_value('dataset_detailed_var_stats')): ?>
        <div class="scroll-content-tab">
          <div class="table-statistic-var">
            <div id="param-statistics"
              var-id="<?php print $variable_dto->id; ?>"
              <?php if (!variable_get_value('dataset_detailed_var_stats')) : ?> class="statistic-tab"<?php endif; ?> >
              <div id="toempty">
                <img
                  src="<?php print base_path() . drupal_get_path('theme', obiba_mica_commons_get_current_theme()) ?>/img/spin.gif">
              </div>
            </div>
          </div>
        </div>
        <div id="param-statistics-chart"
          var-id="<?php print $variable_dto->id; ?>">
          <div id="toemptychart">
          </div>
        </div>
      <?php else: ?>
        <div class="row">
          <div
            class="col-md-6 col-sm-12">
            <div id="param-statistics"
              var-id="<?php print $variable_dto->id; ?>"
              <?php if (!variable_get_value('dataset_detailed_var_stats')) : ?> class="statistic-tab"<?php endif; ?> >
              <div id="toempty">
                <img
                  src="<?php print base_path() . drupal_get_path('theme', obiba_mica_commons_get_current_theme()) ?>/img/spin.gif">
              </div>
            </div>
          </div>
          <div class="col-md-6 col-sm-12">
            <div id="param-statistics-chart"
              var-id="<?php print $variable_dto->id; ?>">
              <div id="toemptychart">
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>
    </section>
  <?php endif; ?>

  <?php if ($variable_dto->variableType != 'Study'): ?>
    <section>
      <h2><?php print t('Harmonization') ?></h2>
      <?php print render($harmonization_table_legend); ?>
      <?php if ($variable_dto->variableType == 'Dataschema'): ?>

        <div id="variable-harmonization-table">
          <div class="row">
            <div class="col-lg-12 col-xs-12">
              <table class="table table-striped"
                id="table-variable-harmonization"></table>
            </div>
          </div>
        </div>

        <div class="scroll-content-tab">
          <?php obiba_mica_dataset_variable_get_harmonizations($variable_dto); ?>
        </div>
        <?php if (!empty($variable_harmonization_algorithms)): ?>

          <button id="harmo-algo"
            data-loading-text="<?php print t('Loading...') ?>"
            type="button"
            class="btn btn-success md-bottom-margin margin-top-20"
            data-toggle="collapse"
            data-target="#harmo-algo"
            aria-expanded="true"
            aria-controls="harmo-algo"
            var-id="<?php print $variable_dto->id; ?>"
            title-button-var="<?php print t('Harmonization Algorithms'); ?>"
            >

            <?php print t('Show Harmonization Algorithms') ?>
          </button>
          <div id="harmo-algo" class="collapse">

          </div>
        <?php endif; ?>
      <?php else: ?>
        <div class="row">
          <div class="col-md-6 col-xs-12 ">

            <table class="table table-striped">
              <tbody>
              <tr>
                <th><?php print t('Status'); ?></th>
                <td>
                  <?php if (empty($variable_harmonization['status'])): ?>
                    <span
                      class="glyphicon glyphicon-question-sign alert-warning"
                      title="<?php print t('No status') ?>"></span>
                  <?php elseif ($variable_harmonization['status'] == 'complete'): ?>
                    <span class="glyphicon glyphicon-ok alert-success"
                      title="<?php print t('Complete') ?>"></span>
                    <?php
                  elseif ($variable_harmonization['status'] == 'impossible'): ?>
                    <span
                      class="glyphicon <?php print ObibaDatasetConstants::getIcon(); ?>"
                      title="<?php print variable_get_value('dataset_harmonization_impossible_label') ?>"></span>
                    <?php
                  elseif ($variable_harmonization['status'] == 'undetermined'): ?>
                    <span
                      class="glyphicon glyphicon-question-sign alert-warning"
                      title="<?php print t('Undetermined') ?>"></span>
                  <?php endif ?>
                </td>
              </tr>
              <tr>
                <th><?php print t('Comment'); ?></th>
                <td>
                  <p><?php print empty($variable_harmonization['comment']) ? '<i>None</i>' : $variable_harmonization['comment']; ?></p>
                </td>
              </tr>
              </tbody>
            </table>

          </div>
        </div>

        <?php if ($variable_harmonization['status'] == 'complete'): ?>
          <?php if (!empty($variable_harmonization['algorithm'])): ?>
            <h2><?php print t('Algorithm') ?></h2>
            <div class="row">
              <div class="col-md-6 col-sm-12">
                <?php print $variable_harmonization['algorithm']; ?>
              </div>
            </div>
          <?php else: ?>
            <h4><?php print t('Script'); ?></h4>
            <pre class="prettyprint lang-js">
            <?php print $variable_harmonization['script']; ?>
          </pre>
          <?php endif; ?>
        <?php endif; ?>

      <?php endif; ?>
    </section>
  <?php endif; ?>
</article>
