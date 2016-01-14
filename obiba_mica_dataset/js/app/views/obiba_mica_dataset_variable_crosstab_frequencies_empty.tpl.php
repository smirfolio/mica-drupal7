<?php
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

<tr>
  <td ng-if="datasetHarmo" rowspan="{{crosstab.rhs.xVariable.categories.length + 1}}">
    <span ng-include="'<?php print base_path(); ?>obiba_mica_app_angular_view_template/obiba_mica_dataset_study_table'"></span>
  </td>
  <td colspan="{{crosstab.lhs.xVariable.categories.length + 2}}"><em>{{'no-results' | translate}}</em></td>
</tr>
