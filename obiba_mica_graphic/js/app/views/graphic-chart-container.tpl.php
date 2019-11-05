<div class="row">
  <div class="col-md-6">
    <div obiba-chart
         field-transformer="chart.fieldTransformer"
         chart-type="chart.type"
         chart-aggregation-name="chart.aggregationName"
         chart-entity-dto="chart.entityDto"
         chart-options-name="chart.optionsName"
         chart-options="chart.options"
         chart-header="chart.header"
         chart-title-graph="chart.title"
         chart-subtitle-graph="chart.subtitle"
         chart-select-graphic="true"></div>
  </div>
  <div class="col-md-6"
       obiba-table
       chart-type="{{'Table-' + chart.type}}"
       chart-aggregation-name="chart.aggregationName"
       chart-entity-dto="chart.entityDto"
       chart-options-name="chart.optionsName"
       chart-header="chart.header"
       chart-select-graphic="true"
       chart-ordered="chart.ordered"
       chart-not-ordered="chart.notOrdered"
       chart-sortedby="chart.sortedby">
  </div>
</div>
