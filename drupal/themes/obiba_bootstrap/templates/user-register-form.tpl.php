<div class="outer">
  <div class="innerdivs">
    <div class="row">
      <div class="col-md-6 text-center "><?php print l('Login', 'user/login') ?></div>
      <div class="col-md-6 text-center bg-primary"><?php print t('Create an account') ?></div>
    </div>
    <p><?php print render($intro_text); ?></p>

    <?php if (!empty($form['obiba_auth']) && $form['obiba_auth']['#value'] == 'obiba_auth_user_register_form'): ?>
      <div class="text-center">
        <p><?php print t('Please use this following link to register') ?></p>
        <?php print l('Create an account ', 'obiba_user/register') ?>
      </div>
    <?php else: ?>
      <div class="obiba-bootstrap-user-register-form-wrapper">
        <?php print drupal_render_children($form) ?>
      </div>
    <?php endif; ?>
  </div>
</div>