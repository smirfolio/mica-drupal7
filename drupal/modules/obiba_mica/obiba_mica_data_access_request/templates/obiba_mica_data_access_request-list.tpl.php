<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div ng-app="DataAccessRequest">

  <h2 class="voffset5">
    <?php print t('Data Access Requests'); ?>
  </h2>
  <?php print l('<i class="fa fa-plus"></i>' . t('Add Data Access Request'), 'data-access-request#/new', array(
      'html' => TRUE,
      'external' => TRUE,
      'attributes' => array('class' => array('btn', 'btn-info'))
    )
  ); ?>

  <table class="table table-striped" id="table-requests"></table>


</div>
