<div class="modal-content">
  <div class="modal-header">
    <button type="button" class="close" aria-hidden="true" ng-click="$dismiss()">&times;</button>
    <h4 class="modal-title">
      {{'data-access-request.profile.title' | translate}}
    </h4>
  </div>
  <div class="modal-body">
    <div>
      <label for="recipient-name"
        class="control-label">{{'data-access-request.profile.name' | translate}} :</label>
      <span id="data-name-applicant">{{getFullName(dataAccessRequest.profile)}}</span>
    </div>

    <div>
      <label for="recipient-email"
        class="control-label">{{'data-access-request.profile.email' | translate}} :</label>
      <span id="data-email-applicant">{{getProfileEmail(dataAccessRequest.profile)}}</span>
    </div>

    <div ng-repeat="attribute in dataAccessRequest.profile.attributes | filterAttributes">
      <label for="recipient-email"
        class="control-label">{{attribute.key}}</label> :
      <span id="data-email-applicant">{{attribute.value}}</span>
    </div>

    <div id="user-attributes" >
      {{getProfileAttributes(dataAccessRequest.profile)}}
    </div>
    <a id="data-email-applicant" class="btn btn-default" href=""
      target="_blank"><?php print t('Send a mail to this applicant'); ?></a>

  </div>
  <div class="modal-footer">
    <button type="button" class="btn btn-primary voffest4" ng-click="$dismiss()">
      <span ng-hide="confirm.close" translate>close</span>
      {{confirm.close}}
    </button>
  </div>
</div>
