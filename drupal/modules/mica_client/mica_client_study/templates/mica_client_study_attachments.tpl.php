<?php if (!empty($documents->id)): ?>
  <ul class="list-group">
    <?php foreach ($documents as $document) : ?>
      <li class="list-group-item">
        <a
          href="<?php print mica_client_commons_safe_expose_server_url($study_id, $document) ?>"
          type="<?php print $document->type; ?>; length=<?php print $document->size; ?>"
          title="<?php print $document->fileName; ?>">
          <span class="glyphicon glyphicon-download"></span>
          <?php print urldecode($document->fileName); ?></a>

      </li>
    <?php endforeach; ?>
  </ul>
<?php endif; ?>