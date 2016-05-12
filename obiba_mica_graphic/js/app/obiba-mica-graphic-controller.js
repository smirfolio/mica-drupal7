/*
 * Copyright (c) 2015 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

'use strict';

mica.ObibaGraphicCharts
  .controller('ChartController', ['$rootScope','$scope', 'GraphicChartsConfig', 'ChartType',
    function ($rootScope, $scope, GraphicChartsConfig, ChartType) {

      function getChartOptions(type) {
        var charOptions = GraphicChartsConfig.getOptions().ChartsOptions;

        switch (type) {
          case ChartType.GEO_CHARTS:
            $scope.directive = {title:charOptions.geoChartOptions.title};
            $scope.chart = {
              type: 'GeoChart',
              title: charOptions.geoChartOptions.title,
              options: charOptions.geoChartOptions.options,
              header: charOptions.geoChartOptions.header,
              fieldTransformer: 'country',
              aggregationName: 'populations-selectionCriteria-countriesIso',
              optionsName: 'geoChartOptions',
              entityDto: 'studyResultDto',
              active: true,
              ordered:true,
              notOrdered: false
            };
            break;
          case ChartType.STUDY_DESIGN:
            $scope.directive = {title:charOptions.studiesDesigns.title};
            $scope.chart = {
              type: 'google.charts.Bar',
              title: charOptions.studiesDesigns.title,
              options: charOptions.studiesDesigns.options,
              header: charOptions.studiesDesigns.header,
              fieldTransformer: null,
              aggregationName: 'methods-designs',
              optionsName: 'studiesDesigns',
              entityDto: 'studyResultDto',
              active: true,
              ordered:true,
              notOrdered: false
            };
            break;
          case ChartType.NUMBER_PARTICIPANTS:
            $scope.directive = null;
            $scope.chart = {
              type: 'PieChart',
              title: charOptions.numberParticipants.title,
              options: charOptions.numberParticipants.options,
              header: charOptions.numberParticipants.header,
              fieldTransformer: null,
              aggregationName: 'numberOfParticipants-participant-range',
              optionsName: 'numberParticipants',
              entityDto: 'studyResultDto',
              active: true,
              ordered:false,
              notOrdered: true
            };
            break;
          case ChartType.BIO_SAMPLES:
            $scope.directive = null;
            $scope.chart = {
              type: 'BarChart',
              title: charOptions.biologicalSamples.title,
              options: charOptions.biologicalSamples.options,
              header: charOptions.biologicalSamples.header,
              fieldTransformer: null,
              aggregationName: 'populations-dataCollectionEvents-bioSamples',
              optionsName: 'biologicalSamples',
              entityDto: 'studyResultDto',
              active: true,
              ordered:true,
              notOrdered: false
            };
            break;

          default:
            throw new Error('Invalid type: ' + type);
        }

      }
    
      $scope.$watch('type', function(type) {
        getChartOptions(type);
      });

  }]);
