<li class="list-group-item">
  <a
    id="download-attachment"
    entity="<?php print $entity_type ?>"
    id_entity="<?php print $id_entity ?>"
    file_name="<?php print rawurlencode($attachment->fileName) ?>"
    file_path="<?php print $attachment->path ?>"
    title="<?php print obiba_mica_commons_get_localized_field($attachment, 'description'); ?>"
    data-original-title="<?php print obiba_mica_commons_get_localized_field($attachment, 'description'); ?>"
    download="<?php print rawurldecode($attachment->fileName); ?>"
    data-placement="top"
    data-toggle="tooltip"
    >
    <span class="glyphicon glyphicon-download"></span>
    <?php print urldecode($attachment->fileName); ?></a>
  <?php if (!empty($attachment->type)): ?>
    <?php $types = explode(',', $attachment->type) ?>
    <div>
      <?php foreach ($types as $type): ?>
        <span class="label label-default"><?php print $type; ?></span>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>
</li>

