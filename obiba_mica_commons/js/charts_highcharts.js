/*
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
