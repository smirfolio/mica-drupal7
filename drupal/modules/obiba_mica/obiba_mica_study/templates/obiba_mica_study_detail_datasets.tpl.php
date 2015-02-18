<h2><?php print t('Datasets'); ?></h2>
<div id="datasetsDisplay" class="scroll-content-tab" data-dce-variables='<?php print json_encode($datasets['dce_variables']) ?>'
  data-total-variables='<?php print json_encode($datasets['total_variable_nbr']) ?>'>
  <?php print render($datasets['dataset-tab']); ?>
</div>