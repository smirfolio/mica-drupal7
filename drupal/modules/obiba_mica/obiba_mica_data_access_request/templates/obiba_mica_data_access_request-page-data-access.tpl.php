<?php print render($node_content); ?>
<?php if ($data_access_form_display) : ?>
  <article>
    <section>
      <h2><?php print t('Data Access Requests') ?></h2>

      <div id="requests-table">
        <div class="row">
          <div class="col-lg-12 col-xs-12">
            <table class="table table-striped" id="table-requests"></table>
          </div>
        </div>
      </div>
    </section>
  </article>
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


