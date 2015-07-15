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

(function ($) {
  Drupal.behaviors.obiba_mica_dataset_variable_crosstab_controller = {
    attach: function (context, settings) {
      mica.DatasetVariableCrosstab
        .controller('DatasetVariableCrosstabController', ['$rootScope', '$scope', '$routeParams', '$log',
          'DatasetCategoricalVariablesResource',
          'DatasetVariablesResource',
          'DatasetVariableResource',
          'DatasetVariablesCrosstabResource',
          'ServerErrorAlertService',

          function ($rootScope, $scope, $routeParams, $log,
                    DatasetCategoricalVariablesResource,
                    DatasetVariablesResource,
                    DatasetVariableResource,
                    DatasetVariablesCrosstabResource,
                    ServerErrorAlertService) {

            var onError = function (response) {
              $scope.serverError = true;
              ServerErrorAlertService.alert('DataAccessRequestEditController', response);
              ForbiddenDrupalRedirect.redirectDrupalMessage(response);
              $.ObibaProgressBarController().finish();
            };

            var searchCategoricalVariables = function(queryString) {
              if (!queryString) return;
              DatasetCategoricalVariablesResource.get({
                  dsType: $routeParams.type,
                  dsId: $routeParams.ds,
                  query: queryString
                },
                function onSuccess(response) {
                  $scope.crosstab.lhs.variables = response.variables;
                },
                onError
              );
            };

            var searchVariables = function(queryString) {
              if (!queryString) return;
              DatasetVariablesResource.get({dsType: $routeParams.type, dsId: $routeParams.ds, query: queryString},
                function onSuccess(response) {
                  $scope.crosstab.rhs.variables = response.variables;
                },
                function onFail(response) {
                  $log.debug('Failed', response);
                });
            };

            var clear = function() {
              initCrosstab();
            };

            var isStatistical = function(variable) {
              return variable && variable.nature.toLowerCase() === 'continuous';
            };

            function normalizeStatistics(contingency, v1Cats) {
              var terms = contingency.aggregations.map(function(aggregation) {
                return aggregation.term;
              });

              v1Cats.forEach(function (cat, i) {
                if (terms.indexOf(cat) === -1) {
                  // create a cat at the same index
                  contingency.aggregations.splice(i, 0, {
                    statistics: {
                      min: '-',
                      max: '-',
                      mean: '-',
                      stdDeviation: '-'
                    },
                    n: '-'
                  });
                }
              });
            }

            function normalizeFrequencies(contingency, v2Cats) {

              function normalize(aggregation) {
                var fCats = aggregation.frequencies.map(function (frq) {
                  return frq.value;
                });

                v2Cats.forEach(function (cat, i) {
                  if (fCats.indexOf(cat) === -1) {
                    // create a cat at the same index
                    aggregation.frequencies.splice(i, 0, {count: 0, value: cat});
                  }
                });
              }

              if (contingency.aggregations) {
                contingency.aggregations.forEach(function(aggregation) {
                  normalize(aggregation);
                });
              }

              normalize(contingency.all, v2Cats);
            }

            /**
             * Normalized data; fills collection with dummy values (statistical or categorical)
             * @param contingencies
             * @returns {*}
             */
            function normalizeData(contingencies) {
              var v2Cats = $scope.crosstab.rhs.variable.categories.map(function(category) {
                return category.name;
              });
              var v1Cats = $scope.crosstab.lhs.variable.categories.map(function(category) {
                return category.name;
              });

              if (contingencies) {
                contingencies.forEach(function (contingency) {
                  $log.debug('>', contingency);

                  if (isStatistical($scope.crosstab.rhs.variable)) {
                    normalizeStatistics(contingency, v1Cats);
                  } else {
                    normalizeFrequencies(contingency, v2Cats);
                  }

                });
              }

              return contingencies;
            }

            /**
             * Submits the crosstab query
             */
            var submit = function() {
              if ($scope.crosstab.lhs.variable && $scope.crosstab.rhs.variable) {
                DatasetVariablesCrosstabResource.get({
                    dsType: $routeParams.type,
                    dsId: $routeParams.ds,
                    v1: $scope.crosstab.lhs.variable.name,
                    v2: $scope.crosstab.rhs.variable.name
                  },
                  function onSuccess(response) {
                    $log.debug('Crosstab Succeeded', response);

                    $scope.crosstab.contingencies = normalizeData(response.contingencies ? response.contingencies : [response]);

                    if ($scope.datasetHarmo) {
                      $scope.crosstab.all = normalizeData(response.all ? [response.all] : [])[0];
                    }
                  },
                  onError
                );
              }
            };

            /**
             * Returns the proper template based on total.n
             * @param contingency
             * @param basePath
             * @returns {string}
             */
            var getTemplatePath = function(contingency, basePath){
              if ($scope.crosstab.rhs.variable) $log.error('RHS variable is not initialized!');

              var folder = basePath + "obiba_main_app_angular/obiba_mica_data_access_request/";
              var template = isStatistical($scope.crosstab.rhs.variable)
                ? (contingency.all.n > 0 ? "obiba_mica_dataset_variable_crosstab_statistics" : "obiba_mica_dataset_variable_crosstab_statistics_empty")
                : (contingency.all.n > 0 ? "obiba_mica_dataset_variable_crosstab_frequencies" : "obiba_mica_dataset_variable_crosstab_frequencies_empty");

              return folder + template;
            };

            var initCrosstab = function() {
              $scope.crosstab = {
                lhs: {
                  variable : null,
                  variables : []
                },
                rhs: {
                  variable: null,
                  variables: []
                },
                data: null
              };
            };

            $scope.isStatistical = isStatistical;
            $scope.datasetHarmo = $routeParams.type === 'harmonization-dataset';
            $scope.getTemplatePath = getTemplatePath;
            $scope.showDetails = true;
            $scope.clear = clear;
            $scope.submit = submit;
            $scope.searchCategoricalVariables = searchCategoricalVariables;
            $scope.searchVariables = searchVariables;

            initCrosstab();

            if ($routeParams.varId) {
              DatasetVariableResource.get({varId: $routeParams.varId},
                function onSuccess(response) {
                  $log.debug('Variable info', response);
                  $scope.crosstab.lhs.variable = response;
                  $scope.crosstab.lhs.variables = [response];
                },
                onError

              );
            }

          }]);
    }
  }
}(jQuery));