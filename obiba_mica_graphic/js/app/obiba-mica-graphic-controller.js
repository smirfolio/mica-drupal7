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
  .controller('AccessController', ['$scope', function ($scope) {
    $scope.chart = {
      options: Drupal.settings.GraphicChartsOptions.ChartsOptions.access.options,
      header: Drupal.settings.GraphicChartsOptions.ChartsOptions.access.header
    };

  }])
  .controller('BioSamplesController', ['$scope', function ($scope) {
    $scope.chart = {
      options: Drupal.settings.GraphicChartsOptions.ChartsOptions.biologicalSamples.options,
      header: Drupal.settings.GraphicChartsOptions.ChartsOptions.biologicalSamples.header
    };

  }])
  .controller('GeoChartController', ['$scope', function ($scope) {
    $scope.chart = {
      options: Drupal.settings.GraphicChartsOptions.ChartsOptions.geoChartOptions.options,
      header: Drupal.settings.GraphicChartsOptions.ChartsOptions.geoChartOptions.header
    };

  }])
  .controller('RecruitmentResourcesController', ['$scope', function ($scope) {
    $scope.chart = {
      options: Drupal.settings.GraphicChartsOptions.ChartsOptions.recruitmentResources.options,
      header: Drupal.settings.GraphicChartsOptions.ChartsOptions.recruitmentResources.header
    };

  }])
  .controller('StudiesDesignsController', ['$scope', function ($scope) {
    $scope.chart = {
      options: Drupal.settings.GraphicChartsOptions.ChartsOptions.studiesDesigns.options,
      header: Drupal.settings.GraphicChartsOptions.ChartsOptions.studiesDesigns.header
    };

  }]);
