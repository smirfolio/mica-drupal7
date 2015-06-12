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
    <?php print l(t('Sign Up'), 'obiba_user/register', array('attributes' => array('class' => 'btn btn-info'))) ?>
    <?php print l(t('Sign In'), 'user/login', array(
      'query' => array('destination' => 'data-access'),
      'attributes' => array(
        'class' => 'btn btn-default'
      )
    )) ?>
  </p>
<?php endif; ?>

<?php if ($data_access_list_display) : ?>
  <p class="md-top-margin">
    <?php print l('See Data Access Requests', 'data-access-request-list',
      array(
        'attributes' => array('class' => array('btn', 'btn-primary'))
      )
    ); ?>
  </p>
<?php endif; ?>



