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

mica.ObibaGraphicCharts = angular.module('mica.ObibaGraphicCharts', [
    'obiba.mica.graphics'
  ])
  .constant('ChartType', {
    GEO_CHARTS: 0,
    STUDY_DESIGN: 1,
    NUMBER_PARTICIPANTS: 2,
    BIO_SAMPLES: 3
  })
  .controller('GraphicNetworkMainController', ['$scope', 'ChartType',
    function ($scope, ChartType) {
      $scope.activeTab = ChartType.GEO_CHARTS;
    }])
    .factory('CoverageResource', ['$resource', function ($resource) {
      return $resource(Drupal.settings.basePath + 'mica/ng/coverage/:type/:id', {}, {'get': {method: 'GET'}});
    }]);
