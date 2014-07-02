<?php if (!empty($documents)): ?>
  <h2 class="block-title"><?php print t('Documents') ?></h2>

  <div class="block-content">
    <div class="field field-name-field-documents field-type-file">
      <div class="field-items">
        <?php foreach ($documents as $document) : ?>
        <div class="field-item even">
          <span class="file">
            <a
              href="<?php print mica_client_study_get_attachment_url($study_id, $document) ?>"
              type="<?php print $document->type; ?>; length=<?php print $document->size; ?>"
              title="<?php print $document->fileName; ?>">
              <?php print $document->fileName; ?></a>
          </span>
        </div>
      </div>
      <?php endforeach; ?>
    </div>
  </div>

<?php endif; ?>