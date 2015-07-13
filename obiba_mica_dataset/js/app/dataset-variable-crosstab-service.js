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

(function ($) {
  Drupal.behaviors.obiba_mica_dataset_variable_crosstab_service = {
    attach: function (context, settings) {

      mica.DatasetVariableCrosstab
        .factory('DatasetCategoricalVariablesResource', ['$resource',
          function ($resource) {
            return $resource(':dsType/:dsId/variables/:query/categorical/ws', {}, {
              'get': {method: 'GET', errorHandler: true}
            });
          }])

        .factory('DatasetVariablesResource', ['$resource',
          function ($resource) {
            return $resource(':dsType/:dsId/variables/:query/ws', {}, {
              'get': {method: 'GET', errorHandler: true}
            });
          }])

        .factory('DatasetVariableResource', ['$resource',
          function ($resource) {
            return $resource('variable/:varId/ws', {}, {
              'get': {method: 'GET', errorHandler: true}
            });
          }])

        .factory('DatasetVariablesCrosstabResource', ['$resource',
          function ($resource) {
            return $resource(':dsType/:dsId/variables/cross/:v1/by/:v2/ws', {}, {
              'get': {method: 'GET', errorHandler: true}
            });
          }])

        .service('ContingencyService',
          function () {
            return {
              getName: function (contingency) {
                if (!variable && !variable.attributes && !names) return null;
                return variable.attributes.filter(
                  function (attribute) {
                    return names.indexOf(attribute.name) !== -1;
                  });
              }
            }
          })
    }
  }
}(jQuery));