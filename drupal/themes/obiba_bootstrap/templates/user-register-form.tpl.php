<?php
//dpm($variables);
?>

<div class="outer">
  <div class="innerdivs">
    <div class="row">
      <div class="col-md-6 text-center "><?php print l('Login', 'user/login') ?></div>
      <div class="col-md-6 text-center bg-primary"><?php print t('Create an account') ?></div>
    </div>
    <p><?php print render($intro_text); ?></p>

    <div class="obiba-bootstrap-user-register-form-wrapper">
      <?php print drupal_render_children($form) ?>
    </div>
  </div>
</div>