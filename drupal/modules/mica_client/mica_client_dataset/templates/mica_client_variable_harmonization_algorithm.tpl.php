<h3><?php print t('Harmonization Algorithms') ?></h3>
<?php foreach ($variable_harmonization_algorithms as $key_var_harmo => $variable_harmonization_algorithm) : ?>
  <h4><?php print l($key_var_harmo, 'mica/variable/' . $variable_harmonization_algorithm['var_id'], array(
      'query' => array(
        'title' => $key_var_harmo
      )
    )); ?></h4>


  <blockquote>
    <?php print !empty($variable_harmonization_algorithm['var_detail']) ? $variable_harmonization_algorithm['var_detail']
      : t('No algorithm implemented'); ?>
  </blockquote>
  <hr>
<?php endforeach; ?>