<li class="list-group-item">
  <a
    id="download-attachment"
    entity="study"
    id_entity="<?php print $study_id ?>"
    id_attachment="<?php print $attachment->id ?>"
    length="<?php print $attachment->size; ?>"
    title="<?php print obiba_mica_commons_get_localized_field($attachment,'description'); ?>"
    data-original-title="<?php print obiba_mica_commons_get_localized_field($attachment,'description'); ?>"
    download="<?php print rawurldecode($attachment->fileName); ?>"
    data-placement="top"
    data-toggle="tooltip"
    >
    <span class="glyphicon glyphicon-download"></span>
    <?php print urldecode($attachment->fileName); ?></a>
  <?php $types =  explode(',',$attachment->type)?>
  <div>
  <?php foreach($types as $type): ?>
    <span class="label label-default"><?php print $type; ?></span>
  <?php endforeach;?>
  </div>
</li>

