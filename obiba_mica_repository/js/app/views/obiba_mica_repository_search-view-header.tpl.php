<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div>
  <div ng-if="options.SearchHelpText">
    <div class="row well">
      <div class="col-md-10">
        <i class="glyphicon glyphicon-info-sign"></i>
        <span ng-bind-html="options.SearchHelpText"></span>
      </div>
      <div class="col-md-2">
        <h4 ng-click="closeHelpBox()"
            title="{{'close' | translate}}"
            class="pull-right" style="cursor: pointer">
          <i class="fa fa-close"></i>
        </h4>
      </div>
    </div>
  </div>
</div>
