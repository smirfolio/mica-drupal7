/**
 * @file
 * JavaScript integration between Highcharts and Drupal.
 */
(function ($) {

  Drupal.behaviors.chartsHighcharts = {};
  Drupal.behaviors.chartsHighcharts.attach = function (context, settings) {
    $('.charts-highchart').once('charts-highchart', function () {
      if ($(this).attr('data-chart')) {
        var config = $.parseJSON($(this).attr('data-chart'));
        config.plotOptions = {
          series: {
            stacking: "normal",
            cursor: 'pointer',
            point: {
              events: {
                click: function () {
                  window.location.href = Drupal.settings.basePath + 'mica/search#!query=' +
                    config.options.links[this.x][this.series['_i'] + 1];
                }
              }
            }
          }
        };
        $(this).highcharts(config);
      }
    });
  };

})(jQuery);
