(function ($) {
  Drupal.behaviors.obiba_mica_graphic_all_studies_geo_chart = {
    attach: function (context, settings) {
      if (context === document) {
        var GeoChart = new $.ObibaGeoChart();
        var statisticsOptions = Drupal.settings.statisticsOptions;
        var pathResources = Drupal.settings.basePath + statisticsOptions.studiesByCountries.StatPathResource;
          var GeoChartOption = {
            options: statisticsOptions.studiesByCountries.options,
            idEntities: statisticsOptions.studiesByCountries.idEntities,
            pathResources: pathResources,
            divChartElement: statisticsOptions.studiesByCountries.divChartElement,
            viewTotalStudies: statisticsOptions.studiesByCountries.viewTotalStudies
          };
            GeoChart.getGeoChart(GeoChartOption);


        //redraw map on resize browser
        window.addEventListener('resize', function(){
          GeoChart.getGeoChart(GeoChartOption)
        });

      }
    }
  }
}(jQuery));