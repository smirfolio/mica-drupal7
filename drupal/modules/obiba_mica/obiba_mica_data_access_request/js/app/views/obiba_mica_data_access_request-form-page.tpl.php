<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div>
  <h1 class="page-header">
    <span ng-if="newRequest">
      <?php print t('New Data Access Request'); ?>
    </span>
    <span ng-if="!newRequest">
      <?php print t('Edit Data Access Request'); ?>: {{requestId}}
    </span>
  </h1>

  <div class="pull-right">
    <?php print l(t('Cancel'), 'mica/data-access/requests', array(
      'attributes' => array(
        'class' => 'btn btn-default',
        'ng-if' => 'newRequest'
      )
    )); ?>

    <a ng-if="!newRequest" ng-click="cancel()" type="button" class="btn btn-default">
      <?php print t('Cancel'); ?>
    </a>

    <a ng-click="save()" type="button" class="btn btn-primary">
      <?php print t('Save'); ?>
    </a>

    <a ng-click="validate()" type="button" class="btn btn-info">
      <?php print t('Validate'); ?>
    </a>
  </div>

  <div class="clearfix"></div>

  <obiba-alert id="DataAccessRequestEditController"></obiba-alert>
  <form name="requestForm" ng-submit="submit(requestForm)">
    <div sf-model="form.model" sf-form="form.definition" sf-schema="form.schema" required="true"></div>
    <h3><?php print t('Attachments'); ?></h3>

    <div class="form-group md-top-margin">
      <attachment-input files="dataAccessRequest.attachments" multiple="true"></attachment-input>
    </div>
  </form>

  <div class="lg-top-margin">
    <?php print l(t('Cancel'), 'mica/data-access/requests', array(
      'attributes' => array(
        'class' => 'btn btn-default',
        'ng-if' => 'newRequest'
      )
    )); ?>

    <a ng-if="!newRequest" ng-click="cancel()" type="button" class="btn btn-default">
      <?php print t('Cancel'); ?>
    </a>

    <a ng-click="save()" type="button" class="btn btn-primary">
      <?php print t('Save'); ?>
    </a>

    <a ng-click="validate()" type="button" class="btn btn-info">
      <?php print t('Validate'); ?>
    </a>
  </div>

</div>


