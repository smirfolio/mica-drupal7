<li class="list-group-item">
        <a
          href="<?php print mica_client_commons_safe_expose_server_url($study_id, $attachment, 'study') ?>"
          type="<?php print $attachment->type; ?>; length=<?php print $attachment->size; ?>"
          title="<?php print $attachment->fileName; ?>"
          download="<?php print rawurldecode($attachment->fileName); ?>"
          >
        <span class="glyphicon glyphicon-download"></span>
          <?php print urldecode($attachment->fileName); ?></a>
</li>

