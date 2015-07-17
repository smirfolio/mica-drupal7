<tr ng-if="options.showDetails" ng-repeat="frequency in contingency.aggregations[0].frequencies track by $index">
  <td ng-if="datasetHarmo && $index === 0" rowspan="{{crosstab.rhs.xVariable.categories.length + 2}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>

  <td>
    <span class="clickable" title="" data-toggle="popover" data-placement="bottom" data-trigger="hover"
          data-content="{{crosstab.rhs.xVariable.categories | variableCategory:frequency.value | variableLabel}}">
      {{frequency.value}}
    </span>
  </td>

  <td ng-repeat="aggregation in contingency.aggregations">
    {{aggregation.frequencies[$parent.$index].count}}&nbsp;
    <span class="help-inline">
      <span ng-show="options.statistics === StatType.RPERCENT">
        ({{aggregation.frequencies[$parent.$index].percent | number:2}}%)
      </span>
      <span ng-show="options.statistics === StatType.CPERCENT">
        ({{aggregation.frequencies[$parent.$index].cpercent | number:2}}%)
      </span>
    </span>
  </td>
  <td>
    {{contingency.all.frequencies[$index].count}}&nbsp;
    <span class="help-inline">
      <span ng-if="options.statistics === StatType.RPERCENT">
        (100%)
      </span>
      <span ng-if="options.statistics === StatType.CPERCENT">
        ({{contingency.all.frequencies[$index].percent | number:2}}%)
      </span>
    </span>
  </td>
</tr>
<tr>
  <td ng-if="datasetHarmo && !options.showDetails" rowspan="{{crosstab.rhs.xVariable.categories.length}}">
    <span ng-if="!grandTotal" ng-include="'<?php print base_path(); ?>obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td><em>N</em></td>
  <td ng-repeat="aggregation in contingency.aggregations">
    {{aggregation.n}}&nbsp;
    <span class="help-inline">
      <span ng-if="options.statistics === StatType.RPERCENT">
        ({{aggregation.percent | number:2}}%)
      </span>
      <span ng-if="options.statistics === StatType.CPERCENT">
        (100%)
      </span>
    </span>
  </td>
  <td>
    {{contingency.all.n}}&nbsp;
    <span class="help-inline">
      <span ng-if="options.statistics === StatType.CPERCENT">
        (100%)
      </span>
      <span ng-if="options.statistics === StatType.RPERCENT">
        (100%)
      </span>
    <span>
  </td>
</tr>
<tr>
  <td>
    <em>{{'chi-squared-test' | translate}}</em>
  </td>
  <td colspan="{{crosstab.lhs.xVariable.categories.length + 1}}">
    <span>
      χ2 = {{contingency.chiSquaredInfo.sum | number:4 }},&nbsp;&nbsp;
      df = {{contingency.chiSquaredInfo.df}},&nbsp;&nbsp;
      p-value = {{contingency.chiSquaredInfo.pValue | number:4 }}
    </span>
  </td>
</tr>
