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
      <?php
      print l('login', 'user/login', array(
        'query' => array(current_path()),
        'attributes' => array('class' => array('btn', 'btn-primary'))
      ));?>
    </p>

  </div>
<?php endif; ?>


