<!--
  ~ Copyright (c) 2017 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->
<div ng-show="display === 'list'">
    <ul class="nav nav-pills pull-left voffset2" test-ref="search-counts">
        <li role="presentation" ng-repeat="res in resultTabsOrder"
            ng-class="{active: activeTarget[targetTypeMap[res]].active && resultTabsOrder.length > 1, disabled: resultTabsOrder.length === 1}"
            ng-if="options[targetTypeMap[res]].showSearchTab">
            <a href
               ng-click="selectTarget(targetTypeMap[res])" ng-if="resultTabsOrder.length > 1"">
                {{targetTypeMap[res] | translate}}
                <span class="badge hoffset1" test-ref="{{targetTypeMap[res]}}"><small>{{getTotalHits(res) | localizedNumber}}</small></span>
            </a>
            <a href style="cursor: default;" ng-if="resultTabsOrder.length === 1">
                <div class="search-count">
                    {{totalHits = getTotalHits(res);""}}
                    {{singleLabel = res + ".label";""}}
                    <span>
                        {{totalHits | localizedNumber }}  {{totalHits>1?targetTypeMap[res]:singleLabel | translate}}
                    </span>
                </div>
            </a>
        </li>
    </ul>
    <ul class="nav nav-pills pull-right voffset2">
        <li>
            <list-sort-widget></list-sort-widget>
        </li>
    </ul>
    <div class="clearfix"/>
    <div class="tab-content">
        <ng-include include-replace ng-repeat="res in resultTabsOrder"
                    src="'search/views/search-result-list-' + res + '-template.html'"></ng-include>
    </div>
    <div class="pull-right voffset2">
        <div ng-repeat="res in resultTabsOrder" ng-show="activeTarget[targetTypeMap[res]].active" class="inline" test-ref="pager">
          <span search-result-pagination
                target="activeTarget[targetTypeMap[res]].name"
                total-hits="activeTarget[targetTypeMap[res]].totalHits"
                on-change="onPaginate"></span>
        </div>
    </div>

</div>
