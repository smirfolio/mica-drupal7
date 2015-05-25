<?php print render($node_content); ?>
<?php if ($data_access_form_display) : ?>
  <div class="text-center"><a class='btn btn-primary'
      href='data-access-request'><?php print t('Data Access Request Form') ?></a></div>
<?php endif; ?>
<?php if ($data_access_register_user) : ?>
  <div class="text-center">
    <p>
      <a class='btn btn-primary' href='obiba_user/register'>
        <?php print t('Please Create an Account to Start Your Application') ?>
      </a>
    </p>

    <p><?php print t('Or') ?></p>

    <p>
      <a class='btn btn-primary' href='user/login'>
        <?php print t('Login') ?>
      </a>
    </p>

  </div>
<?php endif; ?>


