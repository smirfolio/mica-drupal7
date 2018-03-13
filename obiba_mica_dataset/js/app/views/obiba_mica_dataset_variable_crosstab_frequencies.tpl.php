<?php
/**
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * Code for the obiba_mica_dataset modules.
 */

?>
<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<tr ng-if="options.showDetails" ng-repeat="frequency in contingency.aggregations[0].frequencies track by $index">
  <td ng-if="datasetHarmo && $index === 0" rowspan="{{crosstab.rhs.xVariable.categories.length + 2}}">
    <span ng-if="!grandTotal" ng-include="'<?php print $base_path; ?>obiba_mica_app_angular_view_template/obiba_mica_dataset_study_table'"></span>
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

    <span ng-show="aggregation.privacyCheck" class="help-inline">
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
    <span ng-if="contingency.all.privacyCheck" class="help-inline">
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
  <td ng-if="options.showDetailedStats &&  datasetHarmo && !options.showDetails" rowspan="{{crosstab.rhs.xVariable.categories.length}}">
    <span ng-if="!grandTotal" ng-include="'<?php print $base_path; ?>obiba_mica_app_angular_view_template/obiba_mica_dataset_study_table'"></span>
    <span ng-if="grandTotal"><strong>{{'total' | translate}}</strong></span>
  </td>
  <td><em>N</em></td>
  <td ng-repeat="aggregation in contingency.aggregations">
    <span ng-if="contingency.totalPrivacyCheck">
      {{aggregation.n}}&nbsp;
      <span class="help-inline">
        <span ng-if="options.statistics === StatType.RPERCENT">
          ({{aggregation.percent | number:2}}%)
        </span>
        <span ng-if="options.statistics === StatType.CPERCENT">
          (100%)
        </span>
      </span>
    </span>
    <span ng-if="!contingency.totalPrivacyCheck">
      -
    </span>
  </td>
  <td>
    <span ng-if="!contingency.totalPrivacyCheck">
      -
    </span>
    <span ng-if="contingency.totalPrivacyCheck">
      {{contingency.all.n}}&nbsp;
      <span ng-if="contingency.privacyCheck" class="help-inline">
        <span ng-if="options.statistics === StatType.CPERCENT">
          (100%)
        </span>
        <span ng-if="options.statistics === StatType.RPERCENT">
          (100%)
        </span>
      <span>
    </span>
  </td>
</tr>

<tr ng-if="options.showDetails && !grandTotal && contingency.privacyCheck">
  <td>
    <em>{{'dataset.crosstab.chi-squared.test' | translate}}</em>
  </td>
  <td colspan="{{crosstab.lhs.xVariable.categories.length + 1}}">
    <span>
      χ2 = {{contingency.chiSquaredInfo.sum | number:4 }},&nbsp;&nbsp;
      df = {{contingency.chiSquaredInfo.df}},&nbsp;&nbsp;
      p-value = {{contingency.chiSquaredInfo.pValue | number:4 }}
    </span>
    <span class="text-danger" ng-if="!contingency.privacyCheck">
      {{'dataset.crosstab.privacy-check-failed' | translate:{arg0:contingency.privacyThreshold} }}
    <span>
  </td>
</tr>
<tr ng-if="!grandTotal && !contingency.privacyCheck">
  <td colspan="{{crosstab.lhs.xVariable.categories.length + 2}}">
    <span class="text-danger" ng-if="!contingency.privacyCheck">
      {{getPrivacyErrorMessage(contingency) | translate:{arg0:contingency.privacyThreshold} }}
    <span>
  </td>
</tr>
