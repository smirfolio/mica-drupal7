/*
 * Copyright (c) 2015 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Copyright (c) 2014 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
'use strict';

mica.ObibaGraphicCharts
  .controller('GeoChartController', ['$scope', 'GraphicChartsConfig', function ($scope, GraphicChartsConfig) {
    var charOptions = GraphicChartsConfig.getOptions().ChartsOptions;
    $scope.chart = {
      geoTitle : charOptions.geoChartOptions.title,
      title: charOptions.geoChartOptions.title,
      options: charOptions.geoChartOptions.options,
      header: charOptions.geoChartOptions.header,
      active: true
    };
  }])
  .controller('StudiesDesignsController', ['$scope', 'GraphicChartsConfig', function ($scope, GraphicChartsConfig) {
    var charOptions = GraphicChartsConfig.getOptions().ChartsOptions;
    $scope.chart = {
      title: charOptions.studiesDesigns.title,
      options: charOptions.studiesDesigns.options,
      header: charOptions.studiesDesigns.header,
      tableOptions: charOptions.studiesDesigns.tableOptions,
      active: true
    };
  }])
  .controller('BioSamplesController', ['$scope', 'GraphicChartsConfig', function ($scope, GraphicChartsConfig) {
  var charOptions = GraphicChartsConfig.getOptions().ChartsOptions;
  $scope.chart = {
    title: charOptions.biologicalSamples.title,
    options: charOptions.biologicalSamples.options,
    header: charOptions.biologicalSamples.header,
    tableOptions: charOptions.biologicalSamples.tableOptions,
    active: true
  };
}]);
