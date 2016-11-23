  /*
 * Copyright (c) 2016 OBiBa. All rights reserved.
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
        /**
         * Helper to test whether to show the chart title or not
         *
         * @returns {boolean}
         */
        var canShowTitle = function() {
          return $scope.type >= 0 && [ChartType.NUMBER_PARTICIPANTS, ChartType.BIO_SAMPLES, ChartType.STUDY_DESIGN].indexOf($scope.type) === -1;
        };
        /**
         * Depending on the type of the chart, returns the corresponding options
         *
         * @param type
         */
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
                aggregationName: 'populations-model-selectionCriteria-countriesIso',
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
                type: 'BarChart',
                title: charOptions.studiesDesigns.title,
                options: charOptions.studiesDesigns.options,
                header: charOptions.studiesDesigns.header,
                fieldTransformer: null,
                aggregationName: 'model-methods-design',
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
                aggregationName: 'model-numberOfParticipants-participant-range',
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
                aggregationName: 'populations-dataCollectionEvents-model-bioSamples',
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

        $scope.canShowTitle = canShowTitle;
        $scope.$watch('type', function(type) {
          getChartOptions(type);
        });

    }]).controller('ChartBlockController', ['$rootScope','$scope', 'GraphicChartsConfig', 'ChartType',
      function ($rootScope, $scope, GraphicChartsConfig) {

        /**
         * Depending on the type of the chart, returns the corresponding options
         *
         * @param type
         */

          var charOptions = GraphicChartsConfig.getOptions().ChartsOptions;
          var type = $scope.type;
        switch (type){
          case 'geoChartOptions':
            $scope.canShowTitle = true;
            $scope.directive = {title:charOptions.geoChartOptions.title};
            $scope.chart = {
              type: 'GeoChart',
              title: charOptions.geoChartOptions.title,
              options: charOptions.geoChartOptions.options,
              header: charOptions.geoChartOptions.header,
              fieldTransformer: 'country',
              aggregationName: 'populations-model-selectionCriteria-countriesIso',
              optionsName: 'geoChartOptions',
              entityDto: 'studyResultDto',
              active: true,
              ordered:true,
              notOrdered: false
            };
            break;
          case 'studiesDesigns':
            $scope.directive = {title:charOptions.studiesDesigns.title};
            $scope.chart = {
              type: 'BarChart',
              title: charOptions.studiesDesigns.title,
              options: charOptions.studiesDesigns.options,
              header: charOptions.studiesDesigns.header,
              fieldTransformer: null,
              aggregationName: 'model-methods-design',
              optionsName: 'studiesDesigns',
              entityDto: 'studyResultDto',
              active: true,
              ordered:true,
              notOrdered: false
            };
          break;
          case 'numberParticipants' :
          $scope.directive = null;
          $scope.chart = {
            type: 'PieChart',
            title: charOptions.numberParticipants.title,
            options: charOptions.numberParticipants.options,
            header: charOptions.numberParticipants.header,
            fieldTransformer: null,
            aggregationName: 'model-numberOfParticipants-participant-range',
            optionsName: 'numberParticipants',
            entityDto: 'studyResultDto',
            active: true,
            ordered:false,
            notOrdered: true
          };
            break;
          case 'biologicalSamples' :
          $scope.directive = null;
          $scope.chart = {
            type: 'BarChart',
            title: charOptions.biologicalSamples.title,
            options: charOptions.biologicalSamples.options,
            header: charOptions.biologicalSamples.header,
            fieldTransformer: null,
            aggregationName: 'populations-dataCollectionEvents-model-bioSamples',
            optionsName: 'biologicalSamples',
            entityDto: 'studyResultDto',
            active: true,
            ordered:true,
            notOrdered: false
          };
        }

    }])
    .controller('VariableCoverageChartController', ['$scope', '$location', 'CoverageResource', 'D3ChartConfig', function ($scope, $location, CoverageResource, D3ChartConfig) {
      function normalizeData(data) {

        function sortFunction(a, b) {
          return a.title.localeCompare(b.title);
        }

        // template with zero value
        var zeroValues = data.reduce(function (prev, curr) {
          return prev.values.length > curr.values.length ? prev : curr;
        }).values.map(function (v) {
          return { key: v.key, title: v.title, value: 0 };
        }).sort(sortFunction);

        // values normalization
        data.forEach(function (d) {
          var normalized = [];
          zeroValues.map(function (z) { return z; }).forEach(function (z) {
            var item = d.values.filter(function (value) { return value.title === z.title; }).pop();
            normalized.push({
              key: z.key,
              value: item ? item.value : 0,
              title: z.title,
              link: item ? item.link : null
            });
          });

          d.values = normalized.sort(sortFunction);
        });
      }

      // type and id
      var absUrl = $location.absUrl();
      var re = /\/mica\/(\S+)\/(\S+)$/;
      var found = absUrl.match(re);

      if (found) {
        var type = found[1], id = found[2];
        if (type.indexOf('dataset') !== -1) {
          type = 'dataset';
        }

        if (type === 'variable') {
          id = decodeURIComponent(id);
        }

        // resource query
        var result = CoverageResource.get({type: type, id: id});
        $scope.d3Configs = [];
        result.$promise.then(function (res) {
          res.charts.forEach(function (chart) {
            var data = [];

            var chartData = (chart.data.length ? chart.data : chart.variableData);
            if (type !== 'variable') {
              chartData.map(function (d) { return d.key; }).filter(function (f, i, arr) {
                return arr.indexOf(f) === i;
              }).forEach(function (k) {
                data.push({key: k, values: chartData.filter(function (f) { return f.key === k; })});
              });

              normalizeData(data);
            } else {
              data = chartData;
            }

            var config = new D3ChartConfig().withData(data, true).withTitle(chart.title).withSubtitle(chart.subtitle);

            if (type === 'variable') {
              config.withType('pieChart');
            } else {
              if (data[0].values.length > 5) {
                config.options.chart.rotateLabels = -15;
                config.options.chart.margin = {left: 225, bottom: 100};
              } else {
                config.options.chart.staggerLabels = true;
              }
            }
            
            config.options.chart.showLegend = false;
            config.options.chart.color = chart.color.colors;
            config.options.chart.height = 500;
            $scope.d3Configs.push(config);
          });
        });
      }
    }]);
