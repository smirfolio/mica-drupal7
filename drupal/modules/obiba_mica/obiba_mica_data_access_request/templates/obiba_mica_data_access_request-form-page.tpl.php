<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

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
