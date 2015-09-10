<?php
/**
 * @file
 * Code for the obiba_mica_data_access_request modules.
 */

?>
<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div class="modal-content">
  <div class="modal-header">
    <button type="button" class="close" aria-hidden="true" ng-click="$dismiss()">&times;</button>
    <h4 ng-if="requestForm.$valid" class="modal-title">
      <i class="fa fa-check fa-lg"></i>
      {{'data-access-request.validation.title-success' | translate}}
    </h4>
    <h4 ng-if="!requestForm.$valid" class="modal-title">
      <i class="fa fa-times fa-lg"></i>
      {{'data-access-request.validation.title-error' | translate}}
    </h4>
  </div>
  <div class="modal-body">
    <p ng-if="requestForm.$valid">{{'data-access-request.validation.success' | translate}}</p>
    <p ng-if="!requestForm.$valid" translate>{{'data-access-request.validation.error' | translate}}</p>
  </div>
  <div class="modal-footer">
    <button type="button" class="btn btn-primary voffest4" ng-click="$dismiss()">
      <span ng-hide="confirm.ok" translate>ok</span>
      {{confirm.ok}}
    </button>
  </div>
</div>
