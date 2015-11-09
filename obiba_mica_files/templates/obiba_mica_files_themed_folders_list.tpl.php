<div>
  <?php if (empty($folder_path)): ?>
    <i class="glyphicon glyphicon-folder-close"></i> ../<?php print $folder_path; ?>
    <?php print $list_files; ?>
  <?php else: ?>
    <div style="margin-left:  <?php print 5*$indent?>px;">
      <?php $folder_id = preg_replace('/[^A-Za-z0-9\-]/', '', $folder_path) ?>
      <?php str_repeat('&nbsp;', $indent); ?>
        <i class="glyphicon glyphicon-folder-close"></i>
        <?php print $folder_path; ?>

      <div class="" id="folder-<?php print $folder_id; ?>">
        <?php print $list_files; ?>
      </div>
    </div>
  <?php endif; ?>

</div>


