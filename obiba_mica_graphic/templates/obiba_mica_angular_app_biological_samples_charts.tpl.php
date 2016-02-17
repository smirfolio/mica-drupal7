<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<div ng-controller='BioSamplesController'>
  <div obiba-chart
    chart-type="PieChart"
    chart-aggregation-name="populations-dataCollectionEvents-bioSamples"
    chart-entity-dto="studyResultDto"
    chart-options-name="biologicalSamples"
    chart-options ="chart.options"
    chart-header="chart.header"
    chart-title="chart.title"
  >
  </div>
</div>
