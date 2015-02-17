<?php foreach ($variable_harmonization_algorithms as $key_var_harmo => $variable_harmonization_algorithm) : ?>
  <h3><?php print l($key_var_harmo, 'mica/variable/' . $variable_harmonization_algorithm['var_id'], array(
      'query' => array(
        'title' => $key_var_harmo
      )
    )); ?></h3>


  <div class="algo-list">
    <?php print !empty($variable_harmonization_algorithm['var_detail']) ? $variable_harmonization_algorithm['var_detail']
      : NULL ?>
  </div>

<?php endforeach; ?>