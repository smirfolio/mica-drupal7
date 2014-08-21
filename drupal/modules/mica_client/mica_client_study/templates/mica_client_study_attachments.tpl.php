<?php if (!empty($documents)): ?>

  <h5><?php print t('Documents') ?></h5>
  <ul>
    <?php foreach ($documents as $document) : ?>
      <li>
        <a
          href="<?php print mica_client_study_get_attachment_url($study_id, $document) ?>"
          type="<?php print $document->type; ?>; length=<?php print $document->size; ?>"
          title="<?php print $document->fileName; ?>">
          <?php print $document->fileName; ?></a>
      </li>
    <?php endforeach; ?>
  </ul>
<?php endif; ?>