(function ($) {
  $.ObibaGeoChart = {};
  Drupal.behaviors.obiba_mica_graphic_geo_chart = {
    attach: function (context, settings) {
      if (context === document) {
        Drupal.settings.GeoStat={};
        /**
         * @constructor
         */
        $.ObibaGeoChart = function (options) {
          this.options = (options instanceof $) ? options : $(options);
        };

        /**
         * public methods exposed
         */
        $.ObibaGeoChart.prototype = {
          getDataGeoChart: getDataGeoChart,
          getGeoChart: getGeoChart
        };

        //getDataGeoChart();

        /*
        * Perform an ajax call and retrieve data, when ready Draw the chart
        * */
        function getDataGeoChart(draw, PassedOptions) {
          $.ajax({
            method: "GET",
            url: PassedOptions.pathResources + '/' + PassedOptions.idEntities + '/ws',
            dataType: "json",
            success: function (data) {console.log(data);
              Drupal.settings.GeoStat[PassedOptions.divChartElement] = data.ChartData;
              if(draw){
                drawGeoChart(Drupal.settings.GeoStat[PassedOptions.divChartElement], PassedOptions);
              }

            }
          });
        }

        /*
        * Public method to draw the chart
        * the used data are sorted on a global variables
        * */
        function getGeoChart(PassedOptions) {
          if(Drupal.settings.GeoStat[PassedOptions.divChartElement]){
          drawGeoChart(Drupal.settings.GeoStat[PassedOptions.divChartElement],PassedOptions);
          }
          else{
            getDataGeoChart(true, PassedOptions);
          }
        }

        /*
        * Method to draw geo charts
        * */
        function drawGeoChart(stats,PassedOptions) {
          google.load("visualization", "1", {packages:["geochart"], callback:drawRegionsMap});
          //google.setOnLoadCallback(drawRegionsMap, true);
          function drawRegionsMap() {
            var data = google.visualization.arrayToDataTable(JSON.parse(stats));
            var options = {colorAxis: {colors: ['#00FF99', '#009900']}};
            if(PassedOptions.options){
              $.extend( options, PassedOptions.options );
            }
            var chart = new google.visualization.GeoChart(document.getElementById(PassedOptions.divChartElement));
            chart.draw(data, options);
          }
        }


      }
    }
  }
}(jQuery));