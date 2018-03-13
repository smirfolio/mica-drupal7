/*
 * Copyright (c) 2018 OBiBa. All rights reserved.
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
        .controller('DatasetVariableCrosstabController', ['$rootScope',
          '$scope',
          '$routeParams',
          '$log',
          '$location',
          '$route',
          '$translate',
          'DatasetResource',
          'DatasetCategoricalVariablesResource',
          'DatasetVariablesResource',
          'DatasetVariableResource',
          'DatasetVariablesCrosstabResource',
          'ServerErrorAlertService',
          'ContingencyService',
          'LocalizedValues',
          'ChiSquaredCalculator',

          function ($rootScope, $scope, $routeParams, $log, $location, $route, $translate,
                    DatasetResource,
                    DatasetCategoricalVariablesResource,
                    DatasetVariablesResource,
                    DatasetVariableResource,
                    DatasetVariablesCrosstabResource,
                    ServerErrorAlertService,
                    ContingencyService,
                    LocalizedValues,
                    ChiSquaredCalculator) {

            startProgess();

            function updateLocation(currentPath, param) {
              var original = $location.path;
              $location.path = function (path, reload) {
                if (reload === false) {
                  var lastRoute = $route.current;
                  var un = $rootScope.$on('$locationChangeSuccess', function () {
                    $route.current = lastRoute;
                    un();
                  });
                }
                return original.apply($location, [path]);
              };
              $location.path(currentPath + '/' + param, false);
              $location.path = original;
            }

            function startProgess() {
              $.ObibaProgressBarController().start();
              $.ObibaProgressBarController().setPercentage(65, true);
            }

            function endProgress() {
              $.ObibaProgressBarController().finish();
            }

            var onError = function (response) {
              $scope.serverError = true;
              ServerErrorAlertService.alert('MainController', response);
              endProgress();
            };

            var searchCategoricalVariables = function (queryString) {
              if (! queryString) return;
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

            var searchVariables = function (queryString) {
              if (! queryString) return;
              DatasetVariablesResource.get({
                  dsType: $routeParams.type,
                  dsId: $routeParams.ds,
                  query: queryString
                },
                function onSuccess(response) {
                  $scope.crosstab.rhs.variables = response.variables;
                },
                onError
              );
            };

            var canExchangeVariables = function () {
              return $scope.crosstab.lhs.variable
                && $scope.crosstab.rhs.variable
                && ! isStatistical($scope.crosstab.rhs.variable);
            };

            var exchangeVariables = function () {
              if (canExchangeVariables()) {
                var temp = $scope.crosstab.lhs.variable;
                $scope.crosstab.lhs.variable = $scope.crosstab.rhs.variable;
                $scope.crosstab.rhs.variable = temp;
                submit();
              }
            };

            var clear = function () {
              initCrosstab();
            };

            var isStatistical = function (variable) {
              return variable && variable.nature === 'CONTINUOUS';
            };

            function normalizeStatistics(contingency, v1Cats) {
              function createEmptyStatistics() {
                return {
                  min: '-',
                  max: '-',
                  mean: '-',
                  stdDeviation: '-'
                }
              }

              contingency.privacyCheck = contingency.aggregations.filter(function (aggregation) {
                  return aggregation.statistics !== null;
                }).length === contingency.aggregations.length;

              var terms = contingency.aggregations.map(function (aggregation) {
                return aggregation.term;
              });

              if (! contingency.privacyCheck) {
                // server returns no aggregation, create emptyu ones
                contingency.aggregations.forEach(function (aggregation, i) {
                  aggregation.statistics = createEmptyStatistics();
                });

                contingency.all.statistics = createEmptyStatistics();

              } else {
                // create the missing category aggregations
                v1Cats.forEach(function (cat, i) {
                  if (terms.indexOf(cat) === - 1) {
                    // create a cat at the same index
                    contingency.aggregations.splice(i, 0, {
                      n: '-',
                      statistics: createEmptyStatistics()
                    });
                  }

                });
              }
            }

            function normalizeFrequencies(contingency, v2Cats) {

              function percentage(value, total) {
                return total === 0 ? 0 : value / total * 100;
              }

              function expected(cTotal, rTotal, gt) {
                return (cTotal * rTotal) / gt;
              }

              function cellChiSquared(value, expected) {
                return expected === 0 ? 0 : Math.pow(value - expected, 2) / expected;
              }

              function degreeOfFreedom(rows, columns) {
                return (rows - 1) * (columns - 1);
              }

              /**
               * Normalized data; accounts for frequencies with no value (ignored by Elasticsearch)
               * @param aggregation
               */
              function normalize(aggregation) {
                if (!aggregation.frequencies) {
                  aggregation.frequencies = [];
                }
                var fCats = aggregation.frequencies.map(function (frq) {
                  return frq.value;
                });

                v2Cats.forEach(function (cat, i) {
                  if (fCats.indexOf(cat) === - 1) {
                    // create a cat at the same index
                    aggregation.frequencies.splice(i, 0, {
                      count: aggregation.privacyCheck ? 0 : '-',
                      value: cat
                    });
                  }
                });
              }

              /**
               * Calulates frequency percentages and chi-squared
               * @param aggregation
               * @param grandTotal
               * @param totals
               * @param chiSquaredInfo
               */
              function statistics(aggregation, grandTotal, totals, chiSquaredInfo) {
                if (chiSquaredInfo) {
                  aggregation.percent = percentage(aggregation.n, grandTotal);
                  aggregation.frequencies.forEach(function (frequency, i) {
                    frequency.percent = percentage(frequency.count, totals.frequencies[i].count);
                    frequency.cpercent = percentage(frequency.count, aggregation.n);

                    chiSquaredInfo.sum += cellChiSquared(frequency.count, expected(aggregation.n, totals.frequencies[i].count, grandTotal));
                  });
                } else {
                  aggregation.frequencies.forEach(function (frequency) {
                    frequency.percent = percentage(frequency.count, grandTotal);
                    frequency.cpercent = percentage(frequency.n, grandTotal);
                  });
                }
              }

              /**
               * process contingency
               */

              var privacyThreshold = contingency.privacyThreshold;
              var grandTotal = contingency.all.total;
              contingency.all.privacyCheck = contingency.all.frequencies && contingency.all.frequencies.length > 0;
              normalize(contingency.all, privacyThreshold);
              statistics(contingency.all, grandTotal, contingency.all);

              if (contingency.aggregations) {
                contingency.chiSquaredInfo = {
                  pValue: 0,
                  sum: 0,
                  df: degreeOfFreedom(
                    $scope.crosstab.rhs.xVariable.categories.length,
                    $scope.crosstab.lhs.xVariable.categories.length
                  )
                };

                contingency.privacyCheck = true;
                contingency.aggregations.forEach(function (aggregation) {
                  aggregation.privacyCheck =  aggregation.frequencies ? aggregation.frequencies.length > 0 : false;
                  contingency.privacyCheck = contingency.privacyCheck && aggregation.privacyCheck;

                  normalize(aggregation);
                  statistics(aggregation, grandTotal, contingency.all, contingency.chiSquaredInfo);
                });

                if (contingency.privacyCheck) {
                  // no cell has an observation < 5
                  contingency.chiSquaredInfo.pValue = (1 - ChiSquaredCalculator.compute(contingency.chiSquaredInfo));
                }
              }
            }

            /**
             * Normalized data; fills collection with dummy values (statistical or categorical)
             * @param contingencies
             * @returns {*}
             */
            function normalizeData(contingencies) {
              var v2Cats = $scope.crosstab.rhs.xVariable.categories ? $scope.crosstab.rhs.xVariable.categories.map(function (category) {
                return category.name;
              }) : undefined;
              var v1Cats = $scope.crosstab.lhs.xVariable.categories ? $scope.crosstab.lhs.xVariable.categories.map(function (category) {
                return category.name;
              }) : undefined;

              if (contingencies) {
                contingencies.forEach(function (contingency) {
                  // Show the details anyway.
                  contingency.totalPrivacyCheck = contingency.all.n !== - 1;
                  if (! contingency.totalPrivacyCheck || contingency.all.n > 0) {

                    if (isStatistical($scope.crosstab.rhs.xVariable)) {
                      normalizeStatistics(contingency, v1Cats);
                    } else {
                      normalizeFrequencies(contingency, v2Cats);
                    }
                  }
                });
              }

              return contingencies;
            }

            /**
             * Submits the crosstab query
             */
            var submit = function () {
              if ($scope.crosstab.lhs.variable && $scope.crosstab.rhs.variable) {
                $scope.crosstab.lhs.xVariable = $scope.crosstab.lhs.variable;
                $scope.crosstab.rhs.xVariable = $scope.crosstab.rhs.variable;

                updateLocation(
                  ContingencyService.removeVariableFromUrl($location.path()),
                  ContingencyService.createVariableUrlPart(
                    $scope.crosstab.lhs.xVariable.id,
                    $scope.crosstab.rhs.xVariable.id
                  )
                );

                $scope.loading = true;
                startProgess();

                DatasetVariablesCrosstabResource.get({
                    dsType: $routeParams.type,
                    dsId: $routeParams.ds,
                    v1: $scope.crosstab.lhs.xVariable.name,
                    v2: $scope.crosstab.rhs.xVariable.name
                  },
                  function onSuccess(response) {
                    if (Object.keys(response).filter(function (k) {return k[0] !== '$';}).length === 0) {
                      // response with all properties prefixed with '$' filtered out is empty
                      onError({status: 'crosstab.no-data'});
                    } else {
                      $scope.crosstab.contingencies = normalizeData(response.contingencies ? response.contingencies : [response]);

                      if ($scope.datasetHarmo) {
                        $scope.crosstab.all = normalizeData(response.all ? [response.all] : [])[0];
                      }
                    }

                    endProgress();
                    $scope.loading = false;
                  },
                  onError
                );
              }
            };

            var download = function (docType) {
              var downloadUrl = ContingencyService.getCrossDownloadUrl({
                ':dsType': $routeParams.type,
                ':dsId': $routeParams.ds,
                ':docType': docType,
                ':v1': $scope.crosstab.lhs.xVariable.name,
                ':v2': $scope.crosstab.rhs.xVariable.name
              });

              var form = $("<form action='" + downloadUrl + "' method='get'>");
              $('body').after(form);
              form.submit().remove();
              return false;
            };

            var lhsVariableCategory = function (category) {
              return getVariableCategory($scope.crosstab.lhs.xVariable, category);
            };

            var rhsVariableCategory = function (category) {
              return getVariableCategory($scope.crosstab.rhs.xVariable, category);
            };

            function getVariableCategory(variable, category) {
              var result = null;

              if (variable && variable.categories) {
                result = lhsVar.categories.filter(function (cat) {
                  return cat.name === category;
                });
              }

              return result ? result[0] : category;
            }

            /**
             * Retrieves study table info for the result page
             * @param opalTable
             * @returns {{summary: *, population: *, dce: *, project: *, table: *}}
             */
            var extractSummaryInfo = function (opalTable) {
              var summary = opalTable.studySummary || opalTable.networkSummary;

              if (opalTable.studySummary) {
                var studySummary = opalTable.studySummary;
                var pop = studySummary.populationSummaries ? studySummary.populationSummaries[0] : null;
                var dce = pop && pop.dataCollectionEventSummaries
                    ? pop.dataCollectionEventSummaries.filter(function (dce) {
                  return dce.id === opalTable.dataCollectionEventId;
                })
                    : null;
              }

              var currentLanguage = $translate.use();
              return {
                summary: LocalizedValues.forLocale(summary.acronym, currentLanguage),
                population: pop ? LocalizedValues.forLocale(pop.name, currentLanguage) : '',
                dce: dce ? LocalizedValues.forLocale(dce[0].name, currentLanguage) : '',
                project: opalTable.project,
                table: opalTable.table
              }
            };

            var getPrivacyErrorMessage = function (contingency) {
              return ! contingency.totalPrivacyCheck
                ? 'dataset.crosstab.total-privacy-check-failed'
                : (! contingency.privacyCheck ? 'dataset.crosstab.privacy-check-failed' : '');
            };

            /**
             * Returns the proper template based on total.n
             * @param contingency
             * @returns {string}
             */
            var getTemplatePath = function (contingency) {
              if (! $scope.crosstab.rhs.xVariable) {
                $log.error('RHS variable is not initialized!');
                return;
              }
              var basePath = Drupal.settings.basePath;
              var folder = basePath + "obiba_mica_app_angular_view_template/";
              var template = isStatistical($scope.crosstab.rhs.xVariable)
                ? (! contingency.totalPrivacyCheck || contingency.all.n > 0 ? "obiba_mica_dataset_variable_crosstab_statistics" : "obiba_mica_dataset_variable_crosstab_statistics_empty")
                : (! contingency.totalPrivacyCheck || contingency.all.n > 0 ? "obiba_mica_dataset_variable_crosstab_frequencies" : "obiba_mica_dataset_variable_crosstab_frequencies_empty");

              return folder + template;
            };

            var initCrosstab = function () {
              $scope.crosstab = {
                lhs: {
                  variable: null,
                  xVariable: null,
                  variables: []
                },
                rhs: {
                  variable: null,
                  xVariable: null,
                  variables: []
                },
                all: null,
                contingencies: null
              };
            };

            $scope.isStatistical = isStatistical;
            $scope.getTemplatePath = getTemplatePath;
            $scope.getPrivacyErrorMessage = getPrivacyErrorMessage;
            $scope.canExchangeVariables = canExchangeVariables;
            $scope.exchangeVariables = exchangeVariables;
            $scope.extractSummaryInfo = extractSummaryInfo;
            $scope.lhsVariableCategory = lhsVariableCategory;
            $scope.rhsVariableCategory = rhsVariableCategory;
            $scope.clear = clear;
            $scope.submit = submit;
            $scope.download = download;
            $scope.searchCategoricalVariables = searchCategoricalVariables;
            $scope.searchVariables = searchVariables;
            $scope.DocType = {CSV: 'csv', EXCEL: 'excel'};
            $scope.StatType = {CPERCENT: 1, RPERCENT: 2, CHI: 3};
            $scope.routeParams = $routeParams;
            $scope.options = {
              showDetailedStats: Drupal.settings.angularjsApp.show_detailed_stats,
              showDetails: true,
              statistics: $scope.StatType.CPERCENT
            };

            initCrosstab();
            endProgress();

            DatasetResource.get({
                dsType: $routeParams.type,
                dsId: $routeParams.ds
              },
              function onSuccess(response) {
                $scope.dataset = response;
                $scope.datasetHarmo = $scope.dataset.hasOwnProperty('obiba.mica.HarmonizedDatasetDto.type');
              },
              onError
            );

            var varCount = 0;
            if ($routeParams.varId) {
              DatasetVariableResource.get({varId: $routeParams.varId},
                function onSuccess(response) {
                  $scope.crosstab.lhs.variable = response;
                  $scope.crosstab.lhs.variables = [response];
                  varCount ++;
                  if (varCount > 1) {
                    submit();
                  }
                },
                onError
              );
            }

            if ($routeParams.byId) {
              DatasetVariableResource.get({varId: $routeParams.byId},
                function onSuccess(response) {
                  $scope.crosstab.rhs.variable = response;
                  $scope.crosstab.rhs.variables = [response];
                  varCount ++;
                  if (varCount > 1) {
                    submit();
                  }
                },
                onError
              );
            }

          }]);
    }
  }
}(jQuery));
