<div class="outer">

  <div class="innerdivs">
    <div class="row">
      <div class="col-md-6 text-center bg-primary"><?php print t('Login') ?></div>
      <div class="col-md-6 text-center "><?php print l('Create an account ', 'user/register') ?></div>
    </div>
    <p><?php print render($intro_text); ?></p>

    <div class="obiba-bootstrap-user-login-form-wrapper">
      <!--  --><?php print drupal_render_children($form) ?>
    </div>
    <?php print l('Forgot your password?', 'user/password') ?>
  </div>

</div>