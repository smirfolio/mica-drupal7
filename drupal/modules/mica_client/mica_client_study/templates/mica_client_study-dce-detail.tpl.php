<div id="<?php print $dce->id ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print mica_client_commons_get_localized_field($dce, 'name'); ?></h4>
      </div>
      <div class="modal-body">

        <section>

          <div>

          <?php if (!empty($dce->description)): ?>
            <p>
              <?php print mica_client_commons_get_localized_field($dce, 'description'); ?>
            </p>
          <?php endif; ?>

            <?php if (!empty($dce->startYear)): ?>
              <h5><?php print t('Start Year') ?></h5>
              <p><?php print mica_client_commons_format_year($dce->startYear, $dce->startMonth); ?></p>
            <?php endif; ?>

            <?php if (!empty($dce->endYear)): ?>
              <h5><?php print t('End Year') ?></h5>
              <p><?php print mica_client_commons_format_year($dce->endYear, $dce->endMonth); ?></p>
            <?php endif; ?>

            <?php if (!empty($dce->dataSources)): ?>
              <h5><?php print t('Data Sources') ?></h5>
              <ul>
                <?php foreach ($dce->dataSources as $dataSource): ?>
                  <li>
                    <?php print t($dataSource); ?>
                  </li>
                <?php endforeach; ?>
                <?php if (!empty($dce->otherDataSources)): ?>
                  <li>
                    <?php print mica_client_commons_get_localized_field($dce, 'otherDataSources'); ?>
                  </li>
                <?php endif; ?>
              </ul>
            <?php endif; ?>

            <?php if (!empty($dce->administrativeDatabases)): ?>
              <h5><?php print t('Administrative Databases') ?></h5>
              <ul>
                <?php foreach ($dce->administrativeDatabases as $database): ?>
                  <li>
                    <?php print $database; ?>
                  </li>
                <?php endforeach; ?>
              </ul>
            <?php endif; ?>

            <?php if (!empty($dce->bioSamples)): ?>
              <h5><?php print t('Bio Samples') ?>:</h5>
              <ul>
                <?php foreach ($dce->bioSamples as $samples): ?>
                  <li>
                    <?php print $samples; ?>
                  </li>
                <?php endforeach; ?>
                <?php if (!empty($dce->otherBioSamples)): ?>
                  <li>
                    <?php print mica_client_commons_get_localized_field($dce, 'otherBioSamples'); ?>
                  </li>
                <?php endif; ?>
              </ul>
            <?php endif; ?>

            <?php if (!empty($dce->tissueTypes)): ?>
              <h5><?php print t('Tissue Types') ?></h5>
              <p><?php print mica_client_commons_get_localized_field($dce, 'tissueTypes'); ?></p>
            <?php endif; ?>

            <?php if (!empty($dce->attachments)): ?>
              <?php print mica_client_study_get_attachment_file($study_id, $dce->attachments); ?>
            <?php endif; ?>
          </div>
        </section>
      </div>
    </div>
  </div>
</div>
