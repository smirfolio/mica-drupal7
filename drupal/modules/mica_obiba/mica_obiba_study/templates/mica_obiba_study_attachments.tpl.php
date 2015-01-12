<li class="list-group-item">
  <a
    id="download-attachment"
    entity="study"
    id_entity="<?php print $study_id ?>"
    id_attachment="<?php print $attachment->id ?>"
    type="<?php print $attachment->type; ?>"
    length="<?php print $attachment->size; ?>"
    title="<?php print $attachment->fileName; ?>"
    download="<?php print rawurldecode($attachment->fileName); ?>"
    >
    <span class="glyphicon glyphicon-download"></span>
    <?php print urldecode($attachment->fileName); ?></a>
</li>

