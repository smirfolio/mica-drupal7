/*
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

mica.dataTable = angular.module('mica.obibaDataTable', [
  'obiba.mica.obibaDataTable'
]).controller('DataTabaleController', ['$scope', function($scope){
  $scope.datasetsDataTableConfig = {};
  var drupalTableConfig = Drupal.settings.datasetsDataTableConfig;
  switch (drupalTableConfig.type) {
    case 'dataset':
      $scope.datasetsDataTableConfig.showTable = drupalTableConfig.showTable;
      $scope.datasetsDataTableConfig.resourceData = drupalTableConfig.resourceData; // "dataTableStudyDatasets"
      $scope.datasetsDataTableConfig.parentEntityId = drupalTableConfig.parentEntityId; //"lbls"
      console.log($scope.datasetsDataTableConfig);
      break;
  }
  }]);