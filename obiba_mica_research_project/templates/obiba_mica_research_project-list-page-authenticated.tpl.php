<?php print render($node_page); ?>

<div class="list-page">
  <div class="table-responsive">
    <table class="table table-bordered table-stripped">
      <?php if($total_items > 0) : ?>
      <thead>
      <tr>
        <?php if(obiba_mica_user_has_role('mica-data-access-officer')) : ?>
        <th><?php print t('Applicant') ?></th>
        <?php endif; ?>
        <th><?php print t('Title') ?></th>
        <th><?php print t('Data Access Request') ?>
        </th>
        <th><?php print t('Start Date') ?></th>
        <th><?php print t('End Date') ?></th>
      </tr>
      </thead>
      <?php endif; ?>
      <tbody>
      <?php if (!empty($list_projects)): ?>
        <?php print render($list_projects); ?>
      <?php endif; ?>
      </tbody>
    </table>
  </div>
</div>
