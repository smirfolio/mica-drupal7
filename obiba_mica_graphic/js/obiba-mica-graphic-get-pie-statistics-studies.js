(function ($) {
  Drupal.behaviors.obiba_mica_graphic_satistic_chart = {
    attach: function (context, settings) {
      if (context === document) {

        var statisticsOptions = Drupal.settings.statisticsOptions;
        var statisticChart = new $.ObibaStatChart();

        $('.PiChart').each(function(){
          var PieStat =  $(this).attr('aria-controls');
            if (statisticsOptions[PieStat]){
              var pathResources = Drupal.settings.basePath + statisticsOptions[PieStat].StatPathResource;
              var chartStatisticsOption = {
                options: statisticsOptions[PieStat].options,
                idEntities: statisticsOptions[PieStat].idEntities,
                pathResources: pathResources,
                divChartElement: statisticsOptions[PieStat].divChartElement,
                divTableElement: statisticsOptions[PieStat].divTableElement,
                viewTotalStudies: statisticsOptions[PieStat].viewTotalStudies
              };
              statisticChart.getTablePieChart(chartStatisticsOption);
            }

        });

      }
    }
  }
}(jQuery));