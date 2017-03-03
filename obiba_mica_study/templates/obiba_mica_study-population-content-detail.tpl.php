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

<h3 class="no-top-margin">
  <?php if (empty($hide_title)) print obiba_mica_commons_get_localized_field($population, 'name') ?>
</h3>

<?php if (!empty($population->description)): ?>
  <p>
    <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($population, 'description')); ?>
  </p>
<?php endif; ?>

<?php if (!empty($population->model->recruitment->generalPopulationSources)
  || !empty($population->model->recruitment->studies)
  || !empty($population->model->recruitment->specificPopulationSources)
  || !empty($population->model->recruitment->otherSpecificPopulationSource)
  || !empty($population->model->recruitment->otherSource)
  || !empty($population->model->recruitment->info)
): ?>
  <h4><?php print $localize->getTranslation('study.recruitment-sources.label') ?></h4>

  <div class="scroll-content-tab">
    <table class="table table-striped">
      <tbody>
      <?php if (!empty($population->model->recruitment->generalPopulationSources)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.recruitment-sources.general-population') ?></th>
          <td>
            <ul class="list-unstyled">
              <?php  foreach ($population->model->recruitment->generalPopulationSources as $term): ?>
                <li>
                  <?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-recruitment-generalPopulationSources.term.' . $term . '.title'); ?>
                </li>
              <?php endforeach; ?>
            </ul>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->recruitment->specificPopulationSources)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.recruitment-sources.specific-population') ?></th>
          <td>
            <ul class="list-unstyled">
              <?php  foreach ($population->model->recruitment->specificPopulationSources as $term): ?>
                <li>
                  <?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-recruitment-specificPopulationSources.term.' . $term . '.title'); ?>
                  <?php if (stristr($term, 'other') && !empty($population->model->recruitment->otherSpecificPopulationSource)): ?>
                    : <?php print obiba_mica_commons_get_localized_field($population->model->recruitment, 'otherSpecificPopulationSource'); ?>
                  <?php endif; ?>
                </li>
              <?php endforeach; ?>
            </ul>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->recruitment->otherSource)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.recruitment-sources.other') ?></th>
          <td><?php print obiba_mica_commons_get_localized_field($population->model->recruitment, 'otherSource'); ?></td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->recruitment->studies) && !empty(array_filter($population->model->recruitment->studies, 'obiba_mica_commons_array_empty_test'))): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.recruitment-sources.studies') ?></th>
          <td>
            <?php  $studies = obiba_mica_commons_get_localized_dtos_field($population->model->recruitment, 'studies'); ?>
            <?php print implode(', ', $studies); ?>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->recruitment->info)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.recruitment-sources.info') ?></th>
          <td><?php print obiba_mica_commons_get_localized_field($population->model->recruitment, 'info'); ?></td>
        </tr>
      <?php endif; ?>
      </tbody>
    </table>
  </div>
<?php endif; ?>

<?php if (
  (isset($population->model->selectionCriteria->gender) && (obiba_mica_study_get_gender($population->model->selectionCriteria->gender) !== NULL))
  || !empty($population->model->selectionCriteria->ageMin)
  || !empty($population->model->selectionCriteria->ageMax)
  || !empty($population->model->selectionCriteria->countriesIso)
  || !empty($population->model->selectionCriteria->pregnantWomen)
  || !empty($population->model->selectionCriteria->newborn)
  || !empty($population->model->selectionCriteria->twins)
  || !empty($population->model->selectionCriteria->territory)
  || !empty($population->model->selectionCriteria->ethnicOrigin)
  || !empty($population->model->selectionCriteria->healthStatus)
  || !empty($population->model->selectionCriteria->otherCriteria)
  || !empty($population->model->selectionCriteria->info)
): ?>
  <h4><?php print $localize->getTranslation('study.selection-criteria.label') ?></h4>
  <div class="scroll-content-tab">
    <table class="table table-striped">
      <tbody>
      <?php if (!empty($population->model->selectionCriteria->gender) && obiba_mica_study_get_gender($population->model->selectionCriteria->gender) !== NULL): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.gender.label') ?></th>
          <td><?php print  obiba_mica_study_get_gender($population->model->selectionCriteria->gender); ?></td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->ageMin) || !empty($population->model->selectionCriteria->ageMax)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.age') ?></th>
          <td>
            <?php !empty($population->model->selectionCriteria->ageMin) ? print $localize->getTranslation('population.ageMin') . ' '
              .$population->model->selectionCriteria->ageMin
              . ((!empty($population->model->selectionCriteria->ageMax))? ', ':'' ): NULL;?>
            <?php !empty($population->model->selectionCriteria->ageMax) ? print $localize->getTranslation('population.ageMax') . ' '
              . $population->model->selectionCriteria->ageMax : NULL; ?>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->pregnantWomen)): ?>
        <t>
          <th><?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-selectionCriteria-pregnantWomen.title') ?></th>
          <td>
            <ul class="list-unstyled">
              <?php  foreach ($population->model->selectionCriteria->pregnantWomen as $term): ?>
                <li>
                  <?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-selectionCriteria-pregnantWomen.term.' . $term . '.title'); ?>
                </li>
              <?php endforeach; ?>
            </ul>
          </td>
        </t>
      <?php endif ?>

      <?php if (!empty($population->model->selectionCriteria->newborn)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-selectionCriteria-newborn.title') ?></th>
          <td>
              <span class="glyphicon glyphicon-ok"></span>
          </td>
        </tr>
      <?php endif ?>

      <?php if (!empty($population->model->selectionCriteria->twins)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study_taxonomy.vocabulary.populations-selectionCriteria-twins.title') ?></th>
          <td>
            <span class="glyphicon glyphicon-ok"></span>
          </td>
        </tr>
      <?php endif ?>

      <?php if (!empty($population->model->selectionCriteria->countriesIso)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.country'); ?></th>
          <td>
            <?php print obiba_mica_commons_countries($population->model->selectionCriteria->countriesIso); ?>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->territory)): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.territory') ?></th>
          <td>
            <?php print obiba_mica_commons_get_localized_field($population->model->selectionCriteria, 'territory'); ?>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->ethnicOrigin) && !empty(array_filter($population->model->selectionCriteria->ethnicOrigin, 'obiba_mica_commons_array_empty_test'))): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.ethnic-origin') ?></th>
          <td>
            <?php $ethnic_origins = obiba_mica_commons_get_localized_dtos_field($population->model->selectionCriteria, 'ethnicOrigin'); ?>
            <?php print implode(', ', $ethnic_origins); ?>
          </td>

        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->healthStatus)  && !empty(array_filter($population->model->selectionCriteria->healthStatus, 'obiba_mica_commons_array_empty_test'))): ?>
        <tr>
          <th><?php print $localize->getTranslation('study.selection-criteria.health-status') ?></th>
          <td>
            <?php $health_status = obiba_mica_commons_get_localized_dtos_field($population->model->selectionCriteria, 'healthStatus'); ?>
            <?php print implode(', ', $health_status); ?>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->otherCriteria)): ?>
        <tr>
          <th><?php print $localize->getTranslation('other') ?></th>
          <td><?php print obiba_mica_commons_get_localized_field($population->model->selectionCriteria, 'otherCriteria'); ?></td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->selectionCriteria->info)): ?>
        <tr>
          <th><?php print $localize->getTranslation('suppl-info') ?></th>
          <td><?php print obiba_mica_commons_get_localized_field($population->model->selectionCriteria, 'info'); ?></td>
        </tr>
      <?php endif; ?>
      </tbody>
    </table>
  </div>
<?php endif; ?>

<?php if (!empty($population->model->numberOfParticipants->participant->number) || !empty($population->model->numberOfParticipants->participant->noLimit)
  || !empty($population->model->numberOfParticipants->sample->number) || !empty($population->model->numberOfParticipants->sample->noLimit)
  || !empty($population->model->info)
  || !empty($population->model->numberOfParticipants->info)
): ?>
  <h4><?php print $localize->getTranslation('client.label.study.sample-size') ?></h4>

  <div class="scroll-content-tab">
    <table class="table table-striped">
      <tbody>

      <?php if (!empty($population->model->numberOfParticipants->participant->number) || !empty($population->model->numberOfParticipants->participant->noLimit)): ?>
        <tr>
          <th><?php print $localize->getTranslation('numberOfParticipants.label') ?></th>
          <td>
            <p>
              <?php if (!empty($population->model->numberOfParticipants->participant->number)): ?>
                <?php print obiba_mica_commons_format_number($population->model->numberOfParticipants->participant->number) ?>
              <?php endif; ?>
              <?php if (!empty($population->model->numberOfParticipants->participant->noLimit)): ?>
                (<?php print $localize->getTranslation('numberOfParticipants.no-limit'); ?>)
              <?php endif; ?>
            </p>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->numberOfParticipants->sample->number) || $population->model->numberOfParticipants->sample->noLimit): ?>
        <tr>
          <th><?php print $localize->getTranslation('numberOfParticipants.sample')
            ?></th>
          <td>
            <p>
              <?php if (!empty($population->model->numberOfParticipants->sample->number)): ?>
                <?php print obiba_mica_commons_format_number($population->model->numberOfParticipants->sample->number) ?>
              <?php endif; ?>
              <?php if (!empty($population->model->numberOfParticipants->sample->noLimit)): ?>
                (<?php print $localize->getTranslation('numberOfParticipants.no-limit'); ?>)
              <?php endif; ?>
            </p>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty(obiba_mica_commons_get_localized_field($population->model->numberOfParticipants, 'info'))): ?>
        <tr>
          <th><?php print $localize->getTranslation('numberOfParticipants.suppl-info') ?></th>
          <td>
              <p><?php print obiba_mica_commons_get_localized_field($population->model->numberOfParticipants, 'info'); ?></p>
          </td>
        </tr>
      <?php endif; ?>

      <?php if (!empty($population->model->info)): ?>
        <tr>
          <th><?php print $localize->getTranslation('suppl-info') ?></th>
          <td><p> <?php print obiba_mica_commons_get_localized_field($population->model, 'info'); ?></p></td>
        </tr>
      <?php endif; ?>

      </tbody>
    </table>
  </div>
<?php endif; ?>

<?php if (!empty($file_browser)): ?>
      <h4><?php print variable_get_value('files_documents_label'); ?></h4>
  <?php print $file_browser; ?>
<?php endif; ?>
