<div>
  <uib-tabset class="voffset5">

    <uib-tab ng-click="selectTab('geoCharts')"
             heading="{{'graphics.geo-charts' | translate}}">
      <div class="row" ng-controller='GeoChartController'>
        <div class="col-md-6">
          <div ng-if="chart.title"
               style="color: black; font-size: 13px; font-family:Arial; font-weight:bold; margin:25px 0px 25px 95px;">
            {{chart.title | translate}}
          </div>
          <div obiba-chart
               field-transformer="country"
               chart-type="GeoChart"
               chart-aggregation-name="populations-selectionCriteria-countriesIso"
               chart-entity-dto="studyResultDto"
               chart-options-name="geoChartOptions"
               chart-options="chart.options"
               chart-header="chart.header"
               chart-title="chart.title"
               chart-select-graphic="selectedTabGraphic.geoCharts"
          >
          </div>
        </div>
          <div class="col-md-6" obiba-table
               chart-type="Table"
               chart-aggregation-name="populations-selectionCriteria-countriesIso"
               chart-entity-dto="studyResultDto"
               chart-options-name="geoChartOptions"
               chart-header="chart.header"
               chart-select-graphic="selectedTabGraphic.geoCharts"
               chart-ordered="chart.ordered"
               chart-not-ordered="chart.notOrdered"
          >
          </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('studyDesign')"
             heading="{{'graphics.study-design' | translate}}">
      <div class="row" ng-controller='StudiesDesignsController'>
        <div class="col-md-6" obiba-chart
             chart-type="google.charts.Bar"
             chart-aggregation-name="methods-designs"
             chart-entity-dto="studyResultDto"
             chart-options-name="studiesDesigns"
             chart-options="chart.options"
             chart-header="chart.header"
             chart-title="chart.title"
             chart-select-graphic="selectedTabGraphic.studyDesign"
        >
        </div>
        <div class="col-md-6" obiba-table
             chart-type="Table"
             chart-aggregation-name="methods-designs"
             chart-entity-dto="studyResultDto"
             chart-options-name="studiesDesigns"
             chart-header="chart.header"
             chart-select-graphic="selectedTabGraphic.studyDesign"
             chart-ordered="chart.ordered"
             chart-not-ordered="chart.notOrdered"
        >
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('nbrParticipants')"
             heading="{{'graphics.number-participants' | translate}}">
      <div class="row" ng-controller='NumberParticipantsController'>
        <div class="col-md-6" obiba-chart
             chart-type="PieChart"
             chart-aggregation-name="numberOfParticipants-participant-range"
             chart-entity-dto="studyResultDto"
             chart-options-name="numberParticipants"
             chart-options="chart.options"
             chart-header="chart.header"
             chart-title="chart.title"
             chart-select-graphic="selectedTabGraphic.nbrParticipants"
        >
        </div>
        <div class="col-md-6" obiba-table
             chart-type="Table"
             chart-aggregation-name="numberOfParticipants-participant-range"
             chart-entity-dto="studyResultDto"
             chart-options-name="numberParticipants"
             chart-header="chart.header"
             chart-select-graphic="selectedTabGraphic.nbrParticipants"
             chart-ordered="chart.ordered"
             chart-not-ordered="chart.notOrdered"
        >
        </div>
      </div>
    </uib-tab>


    <uib-tab ng-click="selectTab('bioSamples')"
             heading="{{'graphics.bio-samples' | translate}}">

      <div class="row" ng-controller='BioSamplesController'>
        <div class="col-md-6" obiba-chart
             chart-type="BarChart"
             chart-aggregation-name="populations-dataCollectionEvents-bioSamples"
             chart-entity-dto="studyResultDto"
             chart-options-name="biologicalSamples"
             chart-options="chart.options"
             chart-header="chart.header"
             chart-title="chart.title"
             chart-select-graphic="selectedTabGraphic.bioSamples"
        >
        </div>
        <div class="col-md-6" obiba-table
             chart-type="Table"
             chart-aggregation-name="populations-dataCollectionEvents-bioSamples"
             chart-entity-dto="studyResultDto"
             chart-options-name="biologicalSamples"
             chart-header="chart.header"
             chart-select-graphic="selectedTabGraphic.bioSamples"
             chart-ordered="chart.ordered"
             chart-not-ordered="chart.notOrdered"
        >
        </div>
      </div>

    </uib-tab>
  </uib-tabset>
</div>