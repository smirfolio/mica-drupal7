<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<?php print render($node_content); ?>

<?php if ($data_access_register_user) : ?>
  <p class="md-top-margin">
    <?php print t('You need to be authenticated to start an application') ?>
    <?php print l(t(variable_get_value('access_signup_button')), 'agate/register', array('attributes' => array('class' => 'btn btn-info'))) ?>
    <?php print l(t(variable_get_value('access_signin_button')), 'user/login', array(
      'query' => array('destination' => MicaClientPathProvider::DATA_ACCESS_HOME),
      'attributes' => array(
        'class' => 'btn btn-default'
      )
    )) ?>
  </p>
<?php endif; ?>

<?php if ($data_access_list_display) : ?>
  <p class="md-top-margin text-center">
    <?php
    $can_access = obiba_mica_data_access_request_user_permission(MicaDataAccessRequest::LIST_DATA_ACCESS);
    if ($can_access) {
      print l(t(variable_get_value('access_my_requests_button')), 'mica/data_access/requests',
      array(
        'attributes' => array('class' => array('btn', 'btn-primary'))
      )
      );
    } ?>
    <?php
    $can_access = obiba_mica_data_access_request_user_permission(MicaDataAccessRequest::NEW_DATA_ACCESS);
    if ($can_access) {
      print l('<i class="fa fa-plus"></i> ' . t(variable_get_value('access_new_request_button')), 'mica/data-access/request',
        array(
          'attributes' => array('class' => array('btn', 'btn-info', 'indent')),
          'fragment' => 'new',
          'html' => TRUE
        )
      );
    } ?>
  </p>
<?php endif; ?>



