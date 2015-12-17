(function ($) {
  Drupal.behaviors.obiba_mica_network_satistic_chart = {
    attach: function (context, settings) {
      if (context === document) {

        var statisticsOptions = Drupal.settings.statisticsOptions;

        function set_options_geo_chart(){
          var pathResources = Drupal.settings.basePath + statisticsOptions.studiesByCountries.StatPathResource;
          return {
            options: statisticsOptions.studiesByCountries.options,
            idEntities: statisticsOptions.studiesByCountries.idEntities,
            pathResources: pathResources,
            divChartElement: statisticsOptions.studiesByCountries.divChartElement,
            viewTotalStudies: statisticsOptions.studiesByCountries.viewTotalStudies
          };
        }
        var GeoChart = new $.ObibaGeoChart();
        var statisticChart = new $.ObibaStatChart();

        $('#statistics').on('show.bs.collapse', function () {
          GeoChart.getGeoChart(set_options_geo_chart());
        });

        $('a[aria-controls="studiesGeoChart"]').on('shown.bs.tab', function () {
          GeoChart.getGeoChart(set_options_geo_chart());
        });

        $('.PiChart').each(function(){
          var PieStat =  $(this).attr('aria-controls');
          var selectorTab =  'a[aria-controls="'+ PieStat +'"]';
          $(selectorTab).on('shown.bs.tab', function () {
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
        });


        //redraw map on resize browser
        window.addEventListener('resize', function(){
          GeoChart.getGeoChart(set_options_geo_chart());
        });

      }
    }
  }
}(jQuery));