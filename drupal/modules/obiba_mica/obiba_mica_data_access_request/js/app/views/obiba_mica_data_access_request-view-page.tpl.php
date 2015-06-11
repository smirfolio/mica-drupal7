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
      <li class="active">{{dataAccessRequest.id}}</li>
    </ul>
  </h3>

  <obiba-alert id="DataAccessRequestViewController"></obiba-alert>

  <p class="help-block pull-left"><span><?php print t('Created by'); ?>
  </span> {{dataAccessRequest.applicant}} <span
      class="label label-success">{{dataAccessRequest.status}}</span></p>

  <div class="pull-right">

    <a target="_self" ng-href="" class="btn btn-default download-btn">
      <i class="glyphicon glyphicon-download-alt"></i> <span><?php print t('Download'); ?></span>
    </a>
    <a ng-href="#/edit/{{dataAccessRequest.id}}"
      ng-if="actions.canEdit(dataAccessRequest)"
      class="btn btn-primary" title="<?php print t('Edit'); ?>
      ">
      <i class="glyphicon glyphicon-edit"></i>
    </a>

    <a ng-click="submit()"
      ng-if="actions.canEditStatus(dataAccessRequest) && nextStatus.canSubmit(dataAccessRequest)"
      class="btn btn-info"><?php print t('Submit'); ?>

    </a>
    <a ng-click="reopen()"
      ng-if="actions.canEditStatus(dataAccessRequest) && nextStatus.canReopen(dataAccessRequest)"
      class="btn btn-info"><?php print t('Reopen'); ?>
    </a>
    <a ng-click="review()"
      ng-if="actions.canEditStatus(dataAccessRequest) && nextStatus.canReview(dataAccessRequest)"
      class="btn btn-info"><?php print t('Review'); ?>
    </a>
    <a ng-click="approve()"
      ng-if="actions.canEditStatus(dataAccessRequest) && nextStatus.canApprove(dataAccessRequest)"
      class="btn btn-info"><?php print t('Approve'); ?>
    </a>
    <a ng-click="reject()"
      ng-if="actions.canEditStatus(dataAccessRequest) && nextStatus.canReject(dataAccessRequest)"
      class="btn btn-info"><?php print t('Reject'); ?>
    </a>
    <a ng-click="delete()"
      ng-if="actions.canDelete(dataAccessRequest)"
      class="btn btn-danger" title="<?php print t('Delete'); ?>
      ">
      <i class="glyphicon glyphicon-trash"></i>
    </a>
  </div>

  <div class="clearfix"></div>

  <tabset class="lg-top-margin">
    <div class="pull-right">
    </div>
    <tab heading="<?php print t('Application form'); ?>
    ">
      <form id="request-form" name="forms.requestForm">
        <div sf-model="form.model" sf-form="form.definition" sf-schema="form.schema"></div>
      </form>
    </tab>
    <tab heading="<?php print t('Attachments'); ?>">
      <attachment-list files="dataAccessRequest.attachments"
        href-builder="getDownloadHref(attachments, id)"></attachment-list>
    </tab>
    <tab ng-click="selectTab('comments')" heading="<?php print t('Comments'); ?>">
      <obiba-comments comments="form.comments" on-update="updateComment" on-delete="deleteComment"></obiba-comments>
      <obiba-comment-editor on-submit="submitComment" class="md-top-margin"></obiba-comment-editor>
    </tab>
    <tab heading="<?php print t('History'); ?>">
      <div
        ng-include="'obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_data_access_request-histroy-view'"></div>
    </tab>

  </tabset>

</div>
