<h3>{{'dataset.crosstab.title' | translate}}</h3>

<obiba-alert id="DatasetVariableCrosstabController"></obiba-alert>

<!-- crosstab variable selection -->
<div class="well well-sm">
  <div class="row">
    <div class="col-xs-4">
      <ui-select ng-model="crosstab.lhs.variable" theme="bootstrap">
        <ui-select-match placeholder="{{'dataset.crosstab.categorical' | translate}}">{{$select.selected.name}}
        </ui-select-match>
        <ui-select-choices refresh="searchCategoricalVariables($select.search)" refresh-delay="0"
                           repeat="variable in crosstab.lhs.variables">

          <div>{{variable.name}}</div>
          <small>{{variable | variableLabel}}</small>
        </ui-select-choices>
      </ui-select>
    </div>

    <div class="col-xs-2 text-center no-padding no-margin sm-width">
      <i class="fa fa-times fa-2x"></i>
    </div>

    <div class="col-xs-4">
      <ui-select ng-model="crosstab.rhs.variable" theme="bootstrap">
        <ui-select-match placeholder="{{'dataset.crosstab.another' | translate}}">{{$select.selected.name}}
        </ui-select-match>
        <ui-select-choices refresh="searchVariables($select.search)" refresh-delay="0"
                           repeat="variable in crosstab.rhs.variables">

          <div>{{variable.name}}</div>
          <small>{{variable | variableLabel}}</small>
        </ui-select-choices>
      </ui-select>
    </div>

    <div class="col-xs-2">
    <span>
      <button type="button" class="btn btn-primary" aria-hidden="true" ng-click="submit()">{{'submit' | translate}}
      </button>
      <button type="button" class="btn btn-default" aria-hidden="true" ng-click="clear()">{{'clear' | translate}}
      </button>
    </span>
    </div>
  </div>
  <span class="help-block">{{'dataset.crosstab.query-help' | translate}}</span>
</div>

<!-- crosstab results -->
<div ng-if="crosstab.contingencies && crosstab.contingencies.length > 0">
  <label>
    <input type="checkbox" ng-model="showDetails"> {{'show-details' | translate}}
  </label>

    <table class="table table-striped table-bordered no-margin no-padding">
    <thead>
      <tr>
        <th ng-if="datasetHarmo" width="20%" rowspan="{{crosstab.lhs.variable.categories.length}}">{{'study-table' | translate}}</th>
        <th rowspan="{{crosstab.lhs.variable.categories.length}}">{{crosstab.rhs.variable.name}}</th>
        <th colspan="{{crosstab.lhs.variable.categories.length}}"> {{crosstab.lhs.variable.name}}</th>
        <th rowspan="{{crosstab.lhs.variable.categories.length}}">{{'total' | translate}}</th>
      </tr>
      <tr>
        <th class="text-center" ng-repeat="category in crosstab.lhs.variable.categories">{{category.name}}</th>
      </tr>
    </thead>


    <!-- Categorical -->
    <tbody ng-repeat="contingency in crosstab.contingencies track by $index" ng-if="!isStatistical(crosstab.rhs.variable)"
           ng-include="getTemplatePath(contingency, '<?php print base_path(); ?>')">
    </tbody>
    <tbody ng-init="contingency = crosstab.all; grandTotal = true" ng-if="datasetHarmo && !isStatistical(crosstab.rhs.variable)"
           ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_variable_crosstab_frequencies'">
    </tbody>

    <!-- Statistical -->
    <tbody ng-repeat="contingency in crosstab.contingencies" ng-if="isStatistical(crosstab.rhs.variable)"
           ng-include="getTemplatePath(contingency, '<?php print base_path(); ?>')">
    </tbody>
    <tbody ng-init="contingency = crosstab.all; grandTotal = true" ng-if="datasetHarmo && isStatistical(crosstab.rhs.variable)"
           ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_variable_crosstab_statistics'">
    </tbody>

  </table>
</div>
