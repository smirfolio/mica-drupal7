<div>
  <uib-tabset class="voffset5">

    <uib-tab ng-click="selectTab('geoCharts')"
      heading="{{'graphics.geo-charts' | translate}}">
      <div ng-controller='GeoChartController'>
        <div obiba-chart
          field-transformer="country"
          chart-type="GeoChart"
          chart-aggregation-name="populations-selectionCriteria-countriesIso"
          chart-entity-dto="studyResultDto"
          chart-options-name="geoChartOptions"
          chart-options ="chart.options"
          chart-header="chart.header">
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('selectionCriteria')"
      heading="{{'graphics.selection-criteria' | translate}}">
      <div ng-controller='RecruitmentResourcesController'>
        <div obiba-chart
          chart-type="PieChart"
          chart-aggregation-name="populations-recruitment-dataSources"
          chart-entity-dto="studyResultDto"
          chart-options-name="recruitmentResources"
          chart-options ="chart.options"
          chart-header="chart.header">
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('studyDesign')"
      heading="{{'graphics.study-design' | translate}}">
      <div ng-controller='StudiesDesignsController'>
        <div obiba-chart
          chart-type="PieChart"
          chart-aggregation-name="methods-designs"
          chart-entity-dto="studyResultDto"
          chart-options-name="studiesDesigns"
          chart-options="chart.options"
          chart-header="chart.header">
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('bioSamples')"
      heading="{{'graphics.biological-samples' | translate}}">
      <div ng-controller='BioSamplesController'>
        <div obiba-chart
          chart-type="PieChart"
          chart-aggregation-name="populations-dataCollectionEvents-bioSamples"
          chart-entity-dto="studyResultDto"
          chart-options-name="biologicalSamples"
          chart-options ="chart.options"
          chart-header="chart.header">
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('accessPotential')"
      heading="{{'graphics.access-potential' | translate}}">
      <div ng-controller='AccessController' >
        <div obiba-chart
          chart-type="BarChart"
          chart-aggregation-name="access"
          chart-entity-dto="studyResultDto"
          chart-options-name="access"
          chart-options ="chart.options"
          chart-header="chart.header">
        </div>
      </div>
    </uib-tab>

  </uib-tabset>
</div>