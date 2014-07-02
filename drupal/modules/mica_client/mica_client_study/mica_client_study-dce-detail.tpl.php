<div id="<?php print $dce->id ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print t('Data Collection Event Detail') ?></h4>
      </div>
      <div class="modal-body">
        <h4>
          <?php print mica_client_commons_get_localized_field($dce, 'name'); ?>
        </h4>
        <?php if (!empty($dce->description)): ?>
          <p>
            <?php print mica_client_commons_get_localized_field($dce, 'description'); ?>
          </p>
        <?php endif; ?>
        <br/>

        <div>
          <?php if (!empty($dce->startYear)): ?>
            <div>
              <label><?php print t('Start Year') ?>:</label>
              <span>
                <?php print mica_client_commons_format_year($dce->startYear, $dce->startMonth); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($dce->endYear)): ?>
            <div>
              <label><?php print t('End Year') ?>:</label>
              <span>
                <?php print mica_client_commons_format_year($dce->endYear, $dce->endMonth); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($dce->dataSources)): ?>
            <div>
              <label><?php print t('Data Sources') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($dce->dataSources as $dataSource): ?>
                    <li>
                      <?php print $dataSource; ?>
                    </li>
                  <?php endforeach; ?>
                  <?php if (!empty($dce->otherDataSources)): ?>
                    <li>
                      <?php print mica_client_commons_get_localized_field($dce, 'otherDataSources'); ?>
                    </li>
                  <?php endif; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>

          <?php if (!empty($dce->administrativeDatabases)): ?>
            <div>
              <label><?php print t('Administrative Databases') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($dce->administrativeDatabases as $database): ?>
                    <li>
                      <?php print $database; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>
          <?php if (!empty($dce->bioSamples)): ?>
            <div>
              <label><?php print t('Bio Samples') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($dce->bioSamples as $samples): ?>
                    <li>
                      <?php print $samples; ?>
                    </li>
                  <?php endforeach; ?>
                  <?php if (!empty($dce->otherBioSamples)): ?>
                    <?php print mica_client_commons_get_localized_field($dce, 'otherBioSamples'); ?>
                  <?php endif; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>
          <?php if (!empty($dce->tissueTypes)): ?>
            <div>
              <label><?php print t('Tissue Types') ?>:</label>
              <span>
                <?php print mica_client_commons_get_localized_field($dce, 'tissueTypes'); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($dce->attachments)): ?>
            <div>
              <?php print mica_client_study_get_attachment_file($study_id, $dce->attachments); ?>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </div>
</div>
