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

mica.ObibaGraphicCharts = angular.module('mica.ObibaGraphicCharts', [
    'obiba.mica.graphics'
  ])
  .controller('GraphicNetworkMainController', [
    '$rootScope',
    '$scope',
    '$filter',
    function ($rootScope,
              $scope) {
      $scope.selectedTabGraphic = {
        geoCharts: false,
        studyDesign: false,
        bioSamples: false
      };

      var selectTab = function (id) {
        Object.keys($scope.selectedTabGraphic).forEach(function (key) {
          $scope.selectedTabGraphic[key] = false;
        });
        $scope.selectedTabGraphic[id] = true;
      };

      $scope.selectTab = selectTab;
      selectTab('geoCharts')
    }]);
