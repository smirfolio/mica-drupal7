  <div>
    <div ng-if="canShowTitle && chart.title" class="chart-title">
      {{directive.title | translate}}
    </div>
    <div obiba-chart
         field-transformer="chart.fieldTransformer"
         chart-type="chart.type"
         chart-aggregation-name="chart.aggregationName"
         chart-entity-dto="chart.entityDto"
         chart-options-name="chart.optionsName"
         chart-options="chart.options"
         chart-header="chart.header"
         chart-title-graph="chart.title"
         chart-select-graphic="true"></div>
  </div>

