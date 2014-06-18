<div id="<? print $dce->id ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><? print t('Data Collection Event Detail') ?></h4>
      </div>
      <div class="modal-body">
        <h4>
          <? print mica_client_commons_get_localized_field($dce, 'name'); ?>
        </h4>
        <? if (!empty($dce->description)): ?>
          <p>
            <? print mica_client_commons_get_localized_field($dce, 'description'); ?>
          </p>
        <? endif; ?>
        <br/>

        <div>
          <? if (!empty($dce->startYear)): ?>
            <div>
              <label><? print t('Start Year') ?>:</label>
              <span>
                <? print mica_client_commons_format_year($dce->startYear, $dce->startMonth); ?>
              </span>
            </div>
          <? endif; ?>
          <? if (!empty($dce->endYear)): ?>
            <div>
              <label><? print t('End Year') ?>:</label>
              <span>
                <? print mica_client_commons_format_year($dce->endYear, $dce->endMonth); ?>
              </span>
            </div>
          <? endif; ?>
          <? if (!empty($dce->dataSources)): ?>
            <div>
              <label><? print t('Data Sources') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <? foreach ($dce->dataSources as $dataSource): ?>
                    <li>
                      <? print $dataSource; ?>
                    </li>
                  <? endforeach; ?>
                  <? if (!empty($dce->otherDataSources)): ?>
                    <li>
                      <? print mica_client_commons_get_localized_field($dce, 'otherDataSources'); ?>
                    </li>
                  <? endif; ?>
                </ul>
              </div>
            </div>
          <? endif; ?>

          <? if (!empty($dce->administrativeDatabases)): ?>
            <div>
              <label><? print t('Administrative Databases') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <? foreach ($dce->administrativeDatabases as $database): ?>
                    <li>
                      <? print $database; ?>
                    </li>
                  <? endforeach; ?>
                </ul>
              </div>
            </div>
          <? endif; ?>
          <? if (!empty($dce->bioSamples)): ?>
            <div>
              <label><? print t('Bio Samples') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <? foreach ($dce->bioSamples as $samples): ?>
                    <li>
                      <? print $samples; ?>
                    </li>
                  <? endforeach; ?>
                  <? if (!empty($dce->otherBioSamples)): ?>
                    <? print mica_client_commons_get_localized_field($dce, 'otherBioSamples'); ?>
                  <? endif; ?>
                </ul>
              </div>
            </div>
          <? endif; ?>
          <? if (!empty($dce->tissueTypes)): ?>
            <div>
              <label><? print t('Tissue Types') ?>:</label>
              <span>
                <? print mica_client_commons_get_localized_field($dce, 'tissueTypes'); ?>
              </span>
            </div>
          <? endif; ?>
          <? if (!empty($dce->attachments)): ?>
            <div>
              <label><? print t('Attachments') ?>:</label>

              <div class="container">
                <ul class="list-unstyled">
                  <? foreach ($dce->attachments as $attachment): ?>
                    <li>
                      <? print l($attachment->fileName, mica_client_study_get_dce_attachment_url($study_id, $attachment)); ?>
                    </li>
                  <? endforeach; ?>
                </ul>
              </div>
            </div>
          <? endif; ?>
        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><? print t('Close') ?></button>
      </div>
    </div>
  </div>
</div>
