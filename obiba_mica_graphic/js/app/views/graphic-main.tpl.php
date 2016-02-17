<div>
  <uib-tabset class="voffset5">

    <uib-tab ng-click="selectTab('geoCharts')"
      heading="{{'graphics.geo-charts' | translate}}">
      <div ng-controller='GeoChartController'>
        <div ng-if="chart.title" style="color: black; font-size: 12px; font-family:Arial; font-weight:bold; margin:25px 0px 25px 95px;">{{chart.title | translate}}</div>
        <div obiba-chart
          field-transformer="country"
          chart-type="GeoChart"
          chart-aggregation-name="populations-selectionCriteria-countriesIso"
          chart-entity-dto="studyResultDto"
          chart-options-name="geoChartOptions"
          chart-options ="chart.options"
          chart-header="chart.header"
          chart-title="chart.title"
        >
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('studyDesign')"
      heading="{{'graphics.study-design' | translate}}">
      <div ng-controller='StudiesDesignsController'>
        <div obiba-chart
          chart-type="BarChart"
          chart-aggregation-name="methods-designs"
          chart-entity-dto="studyResultDto"
          chart-options-name="studiesDesigns"
          chart-options="chart.options"
          chart-header="chart.header"
          chart-title="chart.title"
        >
        </div>
      </div>
    </uib-tab>

    <uib-tab ng-click="selectTab('bioSamples')"
      heading="{{'graphics.bio-samples' | translate}}">
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
    </uib-tab>

  </uib-tabset>
</div>