<div id="<?php print $context_detail->id ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title">Data Collection Event Detail</h4>
      </div>
      <div class="modal-body container">
        <h3>
          <?php print mica_client_commons_get_localized_field($context_detail, 'name'); ?>
        </h3>
        <?php if (!empty($context_detail->description)): ?>
          <p style="width: 35em">
            <?php print mica_client_commons_get_localized_field($context_detail, 'description'); ?>
          </p>
        <?php endif; ?>
        <div>

          <?php if (!empty($context_detail->startYear)): ?>
            <div>
              <label>Start Year:</label>
              <span>
                <?php print mica_client_commons_format_year($context_detail->startYear, $context_detail->startMonth); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($context_detail->endYear)): ?>
            <div>
              <label>End Year:</label>
              <span>
                <?php print mica_client_commons_format_year($context_detail->endYear, $context_detail->endMonth); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($context_detail->dataSources)): ?>
            <div>
              <label>Data Sources:</label>
              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($context_detail->dataSources as $dataSource): ?>
                    <li>
                      <?php print $dataSource; ?>
                    </li>
                  <?php endforeach; ?>
                  <?php if (!empty($context_detail->otherDataSources)): ?>
                    <li>
                      <?php print mica_client_commons_get_localized_field($context_detail, 'otherDataSources'); ?>
                    </li>
                  <?php endif; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>

          <?php if (!empty($context_detail->administrativeDatabases)): ?>
            <div>
              <label>Administrative Databases:</label>
              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($context_detail->administrativeDatabases as $database): ?>
                    <li>
                      <?php print $database; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>
          <?php if (!empty($context_detail->bioSamples)): ?>
            <div>
              <label>Bio Samples:</label>
              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($context_detail->bioSamples as $samples): ?>
                    <li>
                      <?php print $samples; ?>
                    </li>
                  <?php endforeach; ?>
                  <?php if (!empty($context_detail->otherBioSamples)): ?>
                    <?php print mica_client_commons_get_localized_field($context_detail, 'otherBioSamples'); ?>
                  <?php endif; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>
          <?php if (!empty($context_detail->tissueTypes)): ?>
            <div>
              <label>Tissue Types:</label>
              <span>
                <?php print mica_client_commons_get_localized_field($context_detail, 'tissueTypes'); ?>
              </span>
            </div>
          <?php endif; ?>
          <?php if (!empty($context_detail->attachments)): ?>
            <div>
              <label>Attachments:</label>
              <div class="container">
                <ul class="list-unstyled">
                  <?php foreach ($context_detail->attachments as $attachment): ?>
                    <li>
                      <a href="<?php print mica_client_commons_get_dce_attachment_url($study_id, $attachment) ?>">
                        <? print $attachment->fileName ?>
                      </a>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </div>
            </div>
          <?php endif; ?>
        </div>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>
