<p><?php print render($intro_text); ?></p>

<div class="row">
      <div class="col-md-6">
        <?php print drupal_render_children($form) ?>
      </div>
    </div>

    <?php if (!empty($form['obiba_auth']) && $form['obiba_auth']['#value'] == 'obiba_auth_user_register_form'): ?>
      <div class="text-center">
        <p><?php print t('Please use this following link to register') ?></p>
        <?php print l('Sign Up ', 'obiba_user/register') ?>
      </div>
   <?php endif; ?>
