<tr width="20%" ng-if="showDetails">
  <td rowspan="5">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal">{{'total' | translate}}</span>
  </td>
  <td translate>min</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.min | number: 2}}</td>
  <td>{{contingency.all.statistics.min | number: 2}}</td>
</tr>
<tr ng-if="showDetails">
  <td translate>max</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.max | number: 2}}</td>
  <td>{{contingency.all.statistics.max | number: 2}}</td>
</tr>
<tr ng-if="showDetails">
  <td translate>mean</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.mean | number: 2}}</td>
  <td>{{contingency.all.statistics.mean | number: 2}}</td>
</tr>
<tr ng-if="showDetails">
  <td translate>std-deviation</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.stdDeviation | number: 2}}</td>
  <td>{{contingency.all.statistics.stdDeviation | number: 2}}</td>
</tr>
<tr>
  <td ng-if="!showDetails">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal">{{'total' | translate}}</span>
  </td>
  <td>N</td>
  <td ng-repeat="aggregation in contingency.aggregations">{{aggregation.n}}</td>
  <td>{{contingency.all.n}}</td>
</tr>

