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
                  $log.debug('Succeeded', response);
                  $scope.crosstab.lhs.variables = response.variables;
                },
                onError
              );
            };

            var searchVariables = function(queryString) {
              if (!queryString) return;
              DatasetVariablesResource.get({dsType: $routeParams.type, dsId: $routeParams.ds, query: queryString},
                function onSuccess(response) {
                  $log.debug('Succeeded', response);
                  $scope.crosstab.rhs.variables = response.variables;
                },
                function onFail(response) {
                  $log.debug('Failed', response);
                });
            };

            var clear = function() {
              initCrosstab();
            };

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

                    $scope.crosstab.contingencies = response.contingencies ? response.contingencies : [response];
                    $scope.crosstab.all = response.all;
                  },
                  onError
                );
              }
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