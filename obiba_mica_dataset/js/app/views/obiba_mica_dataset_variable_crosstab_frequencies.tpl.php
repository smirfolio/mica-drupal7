<tr ng-if="$parent.showDetails" ng-repeat="frequency in contingency.aggregations[0].frequencies track by $index">
  <td width="20%" ng-if="datasetHarmo && $index === 0" rowspan="{{crosstab.rhs.xVariable.categories.length + 1}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td>{{frequency.value}}</td>
  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">
    {{aggregation.frequencies[$parent.$index].count}}
  </td>
  <td class="text-center">
    {{contingency.all.frequencies[$index].count}}
  </td>
</tr>
<tr>
  <td ng-if="!showDetails" rowspan="{{crosstab.rhs.xVariable.categories.length}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td class="grand-total">N</td>
  <td class="text-center grand-total" ng-repeat="aggregation in contingency.aggregations">{{aggregation.n}}</td>
  <td class="text-center grand-total">{{contingency.all.n}}</td>
</tr>
