<tr ng-if="options.showDetails">
  <td ng-if="datasetHarmo" rowspan="5">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td translate>min</td>
  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.min | roundNumber}}</td>
  <td class="text-center">{{contingency.all.statistics.min | roundNumber}}</td>
</tr>
<tr ng-if="options.showDetails">
  <td translate>max</td>
  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.max | roundNumber}}</td>
  <td class="text-center">{{contingency.all.statistics.max | roundNumber}}</td>
</tr>
<tr ng-if="options.showDetails">
  <td translate>mean</td>
  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.mean | roundNumber}}</td>
  <td class="text-center">{{contingency.all.statistics.mean | roundNumber}}</td>
</tr>
<tr ng-if="options.showDetails">
  <td translate>std-deviation</td>
  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">{{aggregation.statistics.stdDeviation | roundNumber}}</td>
  <td class="text-center">{{contingency.all.statistics.stdDeviation | roundNumber}}</td>
</tr>
<tr>
  <td ng-if="datasetHarmo && !options.showDetails">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td class="grand-total">N</td>
  <td class="text-center grand-total" ng-repeat="aggregation in contingency.aggregations">{{aggregation.n}}</td>
  <td class="text-center grand-total">{{contingency.all.n}}</td>
</tr>
