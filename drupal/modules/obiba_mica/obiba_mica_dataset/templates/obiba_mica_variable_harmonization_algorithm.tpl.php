<?php foreach ($variable_harmonization_algorithms as $key_var_harmo => $variable_harmonization_algorithm) : ?>
  <h4><?php print l($key_var_harmo, 'mica/variable/' . $variable_harmonization_algorithm['var_id'], array(
      'query' => array(
        'title' => $key_var_harmo
      )
    )); ?></h4>

  <div class="row">
    <div class="col-md-6 col-sm-12">
      <?php print !empty($variable_harmonization_algorithm['var_detail']) ? $variable_harmonization_algorithm['var_detail']
        : NULL ?>
    </div>
  </div>

<?php endforeach; ?>