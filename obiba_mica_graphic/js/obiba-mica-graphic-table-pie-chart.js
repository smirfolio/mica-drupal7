(function ($) {
  $.ObibaStatChart = {};
  Drupal.behaviors.obiba_mica_graphic_table_pie_chart = {
    attach: function (context, settings) {
      if (context === document) {
        Drupal.settings.pieStat = {};
        Drupal.settings.tableStat = {};

        /**
         * @constructor
         */
        $.ObibaStatChart = function (options) {
          this.options = (options instanceof $) ? options : $(options);
        };


        /**
         * public methods exposed
         */
        $.ObibaStatChart.prototype = {
          getDataTablePieChart: getDataTablePieChart,
          getTablePieChart: getTablePieChart
        };

        /*
         * Perform an ajax call and retrieve data, when ready Draw the chart
         * */
        function getDataTablePieChart(draw, PassedOptions) {
          $.ajax({
            method: "GET",
            url: PassedOptions.pathResources + '/' + PassedOptions.idEntities + '/ws',
            dataType: "json",
            success: function (data) {
              Drupal.settings.pieStat[PassedOptions.divChartElement] = data.PieData;
              Drupal.settings.tableStat[PassedOptions.divChartElement] = data.TableData;
              if (draw) {
                drawPieChart(Drupal.settings.pieStat[PassedOptions.divChartElement], PassedOptions);
                drawTableChart(Drupal.settings.tableStat[PassedOptions.divChartElement],PassedOptions);
              }
            }
          });
        }

        /*
         * Public method to draw the chart
         * the used data are sorted on a global variables
         * */
        function getTablePieChart(PassedOptions) {
          if (Drupal.settings.pieStat[PassedOptions.divChartElement]) {
            drawPieChart(Drupal.settings.pieStat[PassedOptions.divChartElement], PassedOptions);
            drawTableChart(Drupal.settings.tableStat[PassedOptions.divChartElement], PassedOptions);
          }
          else {
            getDataTablePieChart(true, PassedOptions);
          }
        }

        /*
         * Method to draw geo charts
         * */
        function drawPieChart(stats, PassedOptions) {
          google.load("visualization", "1", {packages: ["corechart"], callback: DrawPieChart});
          // google.setOnLoadCallback(drawChart);
          function DrawPieChart() {
            if (!Drupal.settings[PassedOptions.divChartElement]) {
              Drupal.settings[PassedOptions.divChartElement] = {};
            }
            var data = google.visualization.arrayToDataTable(JSON.parse(stats));
            var options = {
              colors: ['#006600', '#009900', '#009966', '#009933', '#66CC33'],
              width: 500,
              height: 500
            };
            if (PassedOptions.options) {
              var N = get_sum_stat_item(JSON.parse(stats));
              if (PassedOptions.options.title && PassedOptions.viewTotalStudies && !Drupal.settings[PassedOptions.divChartElement].titleSet) {
                PassedOptions.options.title = PassedOptions.options.title + ' (N=' + N + ')';
                Drupal.settings[PassedOptions.divChartElement].titleSet = true;
              }
              $.extend(options, PassedOptions.options);
            }
            var chart = new google.visualization.PieChart(document.getElementById(PassedOptions.divChartElement));
            chart.draw(data, options);
          }
        }


        /*
         * Method to draw geo charts
         * */
        function drawTableChart(Table, PassedOptions) {
          if (!Drupal.settings[PassedOptions.divChartElement]) {
            Drupal.settings[PassedOptions.divChartElement] = {};
          }
         if( !Drupal.settings[PassedOptions.divChartElement].displaylaTab)
          {
            $("div#" + PassedOptions.divTableElement).append(Table);
            Drupal.settings[PassedOptions.divChartElement].displaylaTab =true;
          }
        }

        function get_sum_stat_item(stats) {
          var totalN = 0;
          $.each(stats, function (key, stat) {
            if (key != 0) {
              totalN += stat[1];
            }
          });
          return totalN;
        }


      }
    }
  }
}(jQuery));