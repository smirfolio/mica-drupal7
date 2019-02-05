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
  $scope.obibaDataTableConfig = {};
  var drupalTableConfig = Drupal.settings.obibaDataTableConfig;
  switch (drupalTableConfig && drupalTableConfig.type) {
    case 'dataset':
      $scope.obibaDataTableConfig.showTable = drupalTableConfig.showTable;
      $scope.obibaDataTableConfig.resourceData = drupalTableConfig.resourceData; // "dataTableStudyDatasets"
      $scope.obibaDataTableConfig.parentEntityId = drupalTableConfig.parentEntityId; //"lbls"
      break;
  }
  }]);