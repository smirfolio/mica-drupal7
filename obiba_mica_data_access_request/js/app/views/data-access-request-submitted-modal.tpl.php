<div class="modal-content">
  <div class="modal-header">
    <button type="button" class="close" aria-hidden="true" ng-click="$dismiss()">&times;</button>
    <h4 class="modal-title">
      <i class="fa fa-check fa-lg"></i>
      {{'data-access-request.submit-confirmation.title' | translate}}
    </h4>
  </div>
  <div class="modal-body">
    <p>{{'data-access-request.submit-confirmation.message' | translate}}</p>
  </div>
  <div class="modal-footer">
    <button type="button" class="btn btn-primary voffest4" ng-click="$dismiss()">
      <span ng-hide="confirm.ok" translate>ok</span>
      {{confirm.ok}}
    </button>
  </div>
</div>
