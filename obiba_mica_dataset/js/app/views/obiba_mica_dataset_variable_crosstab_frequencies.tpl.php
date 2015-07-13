<tr ng-if="$parent.showDetails" ng-repeat="frequency in contingency.aggregations[0].frequencies track by $index">
  <td width="20%" ng-if="$index === 0" rowspan="{{crosstab.rhs.variable.categories.length + 1}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal">{{'total' | translate}}</span>
  </td>
  <td >{{frequency.value}}</td>
  <td ng-repeat="aggregation in contingency.aggregations">
    {{aggregation.frequencies[$parent.$index].count}}
  </td>
  <td >
    {{contingency.all.frequencies[$index].count}}
  </td>
</tr>
<tr>
  <td ng-if="!showDetails" rowspan="{{crosstab.rhs.variable.categories.length}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal">{{'total' | translate}}</span>
  </td>
  <td>N</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.n}}</td>
  <td>{{contingency.all.n}}</td>
</tr>
