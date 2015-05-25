<?php
// dpm($variables);
?>

<div class="obiba-bootstrap-data-access-request">

  <div ng-app="DataAccessRequest" ng-controller="DataAccessRequestForm">
    <alert ng-if="alert.message" type="{{alert.type}}" close="closeAlert($index)">{{alert.message}}</alert>
    <br/>

    <form id="obiba-data-access-request-form" name="theForm" ng-submit="submit(form)">
      <div sf-schema="schema" sf-form="form" sf-model="model">

      </div>
      <button type="submit" class="btn btn-primary" ng-click="onSubmit(theForm)">
        <span translate><?php print t('Join') ?></span>
      </button>

      <a href="#/" type="button" class="btn btn-default">
        <span translate><?php print t('Cancel') ?></span>
      </a>
    </form>

  </div>

</div>
