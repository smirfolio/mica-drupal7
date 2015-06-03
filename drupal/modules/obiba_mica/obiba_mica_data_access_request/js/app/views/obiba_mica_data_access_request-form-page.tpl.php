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
      <li> <?php print l('Data Access Requestes list', 'data-access-request-list'); ?>
      <li class="active">
        <span ng-if="newRequest"><?php print t('Add Access Request'); ?>
        </span>
        <span ng-if="!newRequest"><?php print t('Edit'); ?>
        </span>
        <small><span translate>or</span>
          <a ng-click="cancel()">
            <span><?php print t('Cancel'); ?>
            </span>
          </a></small>
      </li>
    </ul>

  </h3>

  <h3 ng-if="!newRequest && !canEdit" class="voffset2">{{dataAccessRequest.title}}</h3>

  <div>
    <obiba-alert id="DataAccessRequestEditController"></obiba-alert>

    <form name="requestForm" ng-submit="submit(requestForm)">
      <div ng-if="newRequest || canEdit" class="voffset2" form-input name="data-access-request.title"
        model="dataAccessRequest.title"
        label="<?php print t('Title'); ?>"
        help="<?php print t('Short summary to help identifying the request.'); ?>"></div>

      <tabset class="voffset5">
        <div class="pull-right">
        </div>
        <tab heading="<?php print t('Application form'); ?>
        ">
          <div sf-model="form.model" sf-form="form.definition" sf-schema="form.schema" required="true"></div>
        </tab>
        <tab heading="<?php print t('Attachments'); ?>
        ">
          <div class="form-group">
            <attachment-input files="dataAccessRequest.attachments" multiple="true"></attachment-input>
          </div>
        </tab>
      </tabset>

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
    </form>

  </div>

</div>


