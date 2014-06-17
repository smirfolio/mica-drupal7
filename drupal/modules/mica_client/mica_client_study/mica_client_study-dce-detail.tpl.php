<div id="<?php print $context_detail->id ?>" class="modal fade">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title">Data Collection Event Detail</h4>
      </div>
      <div class="modal-body">
        <div class="field field-label field-label-inline">
          <div class="field-label">Name: </div>
          <div class="field-item">
            <?php print mica_client_commons_get_localized_field($context_detail, 'name'); ?>
          </div>
        </div>
        <?php if (!empty($context_detail->description)): ?>
          <div class="field field-label field-label-inline">
            <div class="field-label">Description: </div>
            <div class="field-item">
              <?php print mica_client_commons_get_localized_field($context_detail, 'description'); ?>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->startYear)): ?>
          <div class="field field-label field-label-inline">
            <div class="field-label">Start Year: </div>
            <div class="field-item">
              <?php print mica_client_commons_format_year($context_detail->startYear, $context_detail->startMonth); ?>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->endYear)): ?>
          <div class="field field-label field-label-inline">
            <div class="field-label">End Year:</div>
            <div class="field-item">
              <?php print mica_client_commons_format_year($context_detail->endYear, $context_detail->endMonth); ?>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->dataSources)): ?>
          <div class="field field-label">
            <div class="field-label">Data Sources:</div>
            <?php foreach ($context_detail->dataSources as $dataSource): ?>
              <div class="field-items">
                <div class="field-item">
                  <?php print $dataSource; ?>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->otherDataSources)): ?>
          <div class="field field-label">
            <div class="field-label">Other Data Sources:</div>
            <div class="field-items">
              <div class="field-item">
                <?php print mica_client_commons_get_localized_field($context_detail, 'otherDataSources'); ?>
              </div>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->administrativeDatabases)): ?>
          <div class="field field-label">
            <div class="field-label">Administrative Databases:</div>
            <?php foreach ($context_detail->administrativeDatabases as $database): ?>
              <div class="field-items">
                <div class="field-item">
                  <?php print $database; ?>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->bioSamples)): ?>
          <div class="field field-label">
            <div class="field-label">Bio Samples:</div>
            <?php foreach ($context_detail->bioSamples as $samples): ?>
              <div class="field-items">
                <div class="field-item">
                  <?php print $samples; ?>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->otherBioSamples)): ?>
          <div class="field field-label">
            <div class="field-label">Other Bio Samples:</div>
            <div class="field-items">
              <div class="field-item">
                <?php print mica_client_commons_get_localized_field($context_detail, 'otherBioSamples'); ?>
              </div>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->tissueTypes)): ?>
          <div class="field field-label">
            <div class="field-label">Tissue Types:</div>
            <div class="field-items">
              <div class="field-item">
                <?php print mica_client_commons_get_localized_field($context_detail, 'tissueTypes'); ?>
              </div>
            </div>
          </div>
        <?php endif; ?>
        <?php if (!empty($context_detail->attachments)): ?>
          <div class="field field-label">
            <div class="field-label">Attachments:</div>
            <?php foreach ($context_detail->attachments as $attachment): ?>
              <div class="field-items">
                <div class="field-item">
                  <a href="<?php print mica_client_commons_get_dce_attachment_url($study_id, $attachment) ?>">
                    <? print $attachment->fileName ?>
                  </a>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
        <?php endif; ?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>
