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
  <h3>
    <ul class="breadcrumb">
      <li><?php print l('Data Access Requests', 'data-access-request-list'); ?></li>
      <li ng-if="!newRequest"><a ng-click="cancel()">{{requestId}}</a></li>
      <li class="active">
        <span ng-if="newRequest"><?php print t('add'); ?>
        </span>
        <span ng-if="!newRequest"><?php print t('edit'); ?>
        </span>
        <small><span translate>or</span>
          <a ng-click="cancel()">
            <span><?php print t('cancel'); ?>
            </span>
          </a></small>
      </li>
    </ul>
  </h3>

  <div>
    <obiba-alert id="DataAccessRequestEditController"></obiba-alert>

    <form name="requestForm" ng-submit="submit(requestForm)">
      <tabset class="lg-top-margin">
        <div class="pull-right"></div>
        <tab heading="<?php print t('Application form'); ?>">
          <div sf-model="form.model" sf-form="form.definition" sf-schema="form.schema" required="true"></div>
        </tab>
        <tab heading="<?php print t('Attachments'); ?>">
          <div class="form-group md-top-margin">
            <attachment-input files="dataAccessRequest.attachments" multiple="true"></attachment-input>
          </div>
        </tab>
      </tabset>

      <div class="lg-top-margin">
        <a ng-click="cancel()" type="button" class="btn btn-default">
          <span><?php print t('Cancel'); ?></span>
        </a>

        <a ng-click="save()" type="button" class="btn btn-primary">
        <span><?php print t('Save'); ?>
        </span>
        </a>

        <button type="submit" class="btn btn-info">
          <span><?php print t('Validate'); ?></span>
        </button>
      </div>
      
    </form>

  </div>

</div>


