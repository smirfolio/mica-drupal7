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

<?php
$dce_name = obiba_mica_commons_get_localized_field($dce, 'name');
?>

<div id="dce-<?php print $dce_id_target ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h3 class="modal-title"><?php print $dce_name ?></h3>
      </div>
      <div class="modal-body">
        <section>
          <div test-ref="modal-dce-description">
            <?php if (!empty($dce->description)): ?>
              <p>
                <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($dce, 'description')); ?>
              </p>
            <?php endif; ?>
          </div>

          <div class="clearfix"></div>

          <table class="table table-striped">
            <tbody>
            <?php if (!empty($dce->startYear)): ?>
              <tr>
                <th><?php print $localize->getTranslation('data-collection-event.start-year') ?></th>
                <td test-ref="modal-dce-startYear"><p><?php print obiba_mica_commons_format_year($dce->startYear, !empty($dce->startMonth) ? $dce->startMonth : NULL); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->endYear)): ?>
              <tr>
                <th><?php print $localize->getTranslation('data-collection-event.end-year') ?></th>
                <td test-ref="modal-dce-endYear"><p><?php print obiba_mica_commons_format_year($dce->endYear, !empty($dce->endMonth) ? $dce->endMonth : NULL); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->model->dataSources)): ?>
              <tr>
                <th><?php print $localize->getTranslation('data-collection-event.data-sources') ?></th>
                <td>
                  <ul>
                    <?php foreach ($dce->model->dataSources as $dataSource): ?>
                      <li test-ref="modal-dce-dataSource">
                        <?php print  $localize->getTranslation('study_taxonomy.vocabulary.populations-dataCollectionEvents-dataSources.term.' . $dataSource . '.title'); ?>
                        <?php if ($dataSource == 'others'): ?>
                          : <?php print obiba_mica_commons_get_localized_field($dce->model, 'otherDataSources'); ?>
                        <?php endif; ?>
                      </li>
                    <?php endforeach; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->model->administrativeDatabases)): ?>
              <tr>
                <th><?php print $localize->getTranslation('data-collection-event.admin-databases') ?></th>
                <td>
                  <ul>
                    <?php foreach ($dce->model->administrativeDatabases as $database): ?>
                      <li>
                        <?php print   $localize->getTranslation('study_taxonomy.vocabulary.populations-dataCollectionEvents-administrativeDatabases.term.' . $database . '.title'); ?>
                      </li>
                    <?php endforeach; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>
            <?php if (!empty($dce->model->tissueTypes)): ?>
             <?php $tissue_types =  obiba_mica_commons_get_localized_field($dce->model, 'tissueTypes'); ?>
            <?php endif; ?>
            <?php if (!empty($dce->model->otherBioSamples)): ?>
              <?php $other_bio_samples =  obiba_mica_commons_get_localized_field($dce->model, 'otherBioSamples'); ?>
            <?php endif; ?>
            <?php if (!empty($dce->model->bioSamples)): ?>
              <tr>
                <th><?php print $localize->getTranslation('data-collection-event.bio-samples') ?></th>
                <td>
                  <ul>
                    <?php foreach ($dce->model->bioSamples as $samples): ?>
                      <li test-ref="modal-dce-biosample">
                        <?php print  $localize->getTranslation('study_taxonomy.vocabulary.populations-dataCollectionEvents-bioSamples.term.' . $samples . '.title'); ?>
                          <?php if ($samples == "tissues" && !empty($tissue_types)): ?>
                            : <?php print  $tissue_types; ?>
                          <?php endif; ?>
                        <?php if ($samples == "others" && !empty($other_bio_samples)): ?>
                          : <?php print  $other_bio_samples; ?>
                        <?php endif; ?>
                      </li>
                    <?php endforeach; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>
            </tbody>
          </table>
        </section>
        <?php if (!empty($file_browser)): ?>
              <h4><?php print variable_get_value('files_documents_label'); ?></h4>
          <?php print $file_browser; ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
</div>
