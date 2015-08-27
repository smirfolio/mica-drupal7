<div class="modal-content">
  <div class="modal-header">
    <button type="button" class="close" aria-hidden="true"
      ng-click="$dismiss()">&times;</button>
    <h4 class="modal-title">
      <?php print t('Applicant Profile'); ?>
    </h4>
  </div>
  <div class="modal-body">
    <div>
      <label for="recipient-name"
        class="control-label"><?php print t('Name : '); ?></label>
      <span
        id="data-name-applicant">{{getFullName(dataAccessRequest.profile)}}</span>
    </div>

    <div>
      <label for="recipient-email"
        class="control-label"><?php print t('E-mail : '); ?></label>
      <span id="data-email-applicant">{{getProfileEmail(dataAccessRequest.profile)}}</span>
    </div>

    <div
      ng-repeat="attribute in dataAccessRequest.profile.attributes | filterAttributes">
      <label for="recipient-email" class="control-label">
        {{attribute.key}}
      </label> :
      <span id="data-email-applicant">{{attribute.value}}</span>
    </div>
    <a id="data-email-applicant" class="btn btn-default" href=""
      target="_blank"><?php print t('Send E-mail'); ?></a>
  </div>
  <div class="modal-footer">
    <button type="button" class="btn btn-primary voffest4"
      ng-click="$dismiss()">
      <span ng-hide="confirm.close" translate>close</span>
      {{confirm.close}}
    </button>
  </div>
</div>
