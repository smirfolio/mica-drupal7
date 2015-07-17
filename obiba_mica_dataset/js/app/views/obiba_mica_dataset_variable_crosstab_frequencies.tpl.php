<tr ng-if="options.showDetails" ng-repeat="frequency in contingency.aggregations[0].frequencies track by $index">
  <td ng-if="datasetHarmo && $index === 0" rowspan="{{crosstab.rhs.xVariable.categories.length + 1}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>

  <td>
    <span class="clickable" title="" data-toggle="popover" data-placement="bottom" data-trigger="hover"
          data-content="{{crosstab.rhs.xVariable.categories | variableCategory:frequency.value | variableLabel}}">
      {{frequency.value}}
    </span>
  </td>

  <td class="text-center" ng-repeat="aggregation in contingency.aggregations">
    <span ng-show="options.showFrequency">
      {{aggregation.frequencies[$parent.$index].count}}
    </span>
    <span ng-show="!options.showFrequency">
      {{aggregation.frequencies[$parent.$index].percent | number:2}}%
    </span>
  </td>
  <td class="text-center">
    <span ng-if="options.showFrequency">
      {{contingency.all.frequencies[$index].count}}
    </span>
    <span ng-if="!options.showFrequency">
      {{contingency.all.frequencies[$index].percent | number:2}}%
    </span>
  </td>
</tr>
<tr>
  <td ng-if="datasetHarmo && !options.showDetails" rowspan="{{crosstab.rhs.xVariable.categories.length}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td class="grand-total">N</td>
  <td class="text-center grand-total" ng-repeat="aggregation in contingency.aggregations">
    <span ng-if="options.showFrequency">
      {{aggregation.n}}
    </span>
    <span ng-if="!options.showFrequency">
      {{aggregation.percent | number:2}}%
    </span>
  </td>
  <td class="text-center grand-total">
    <span ng-if="options.showFrequency">
      {{contingency.all.n}}
    </span>
    <span ng-if="!options.showFrequency">
      100%
    </span>
  </td>
</tr>
