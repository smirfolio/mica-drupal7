/*
 * Copyright (c) 2017 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
'use strict';

function SortWidgetOptionsFactory() {
  var defaultOptions = {
    sortField: null,
    orderField: null
  };

  function SortWidgetOptionsProvider() {

  };
  this.$get = function () {
    return {
      getOptions: function () {
        return defaultOptions;
      }
    };
  };
  this.setOptions = function (value) {
    Object.keys(value).forEach(function (option) {
      if(option in defaultOptions){
        defaultOptions[option] = value[option];
      }
    });
  };


};

mica.ObibaLists
  .controller('listSortWidgetController', ['$scope', '$rootScope', 'sortWidgetService',
    function ($scope, $rootScope, sortWidgetService) {

      var emitter = $rootScope.$new();
      $scope.selectSort = sortWidgetService.getSortOptions();
      $scope.selectOrder = sortWidgetService.getOrderOptions();
      $scope.selectedSort =  $scope.selectSort.options[0];
      $scope.selectedOrder = $scope.selectOrder.options[0];

      var selectedOptions = sortWidgetService.getSortArg();
      if (selectedOptions) {
        $scope.selectedSort = selectedOptions.selectedSort ? selectedOptions.selectedSort : $scope.selectSort.options[0];
        $scope.selectedOrder = selectedOptions.slectedOrder ? selectedOptions.slectedOrder : $scope.selectOrder.options[0];
      }

      $scope.onChanged = function () {
        var sortParam = {
          sort: $scope.selectedSort.value,
          order: $scope.selectedOrder.value
        };
        emitter.$emit('ngObibaMicaSearch.sortChange', sortParam);
      };

    }])
  .directive('listSortWidget', [function () {
    return {
      restrict: 'EA',
      scope: {
        sortItm: '='
      },
      controller: 'listSortWidgetController',
      templateUrl: Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/list-sort-widget-template'
    };

    // <div list-sort-widget sort-item="
  }])
  .service('sortWidgetService', ['$filter', '$location', 'RqlQueryService', 'sortWidgetOptions', function ($filter, $location, RqlQueryService, sortWidgetOptions) {
    var newOptions = sortWidgetOptions.getOptions();
    var self = this;
    this.getOrderOptions = function () {
      newOptions.orderField.options.map(function (option) {
        return option.label = $filter('translate')(option.label);
      });
      return {
        options: newOptions.orderField.options
      }
    };
    this.getSortOptions = function () {
      newOptions.sortField.options.map(function (option) {

        return option.label = $filter('translate')(option.label);
      });
      return {
        options: newOptions.sortField.options
      }
    };
    this.getSelectedSort = function (rqlSort) {
      var selectedSortOption = null;
      var sortBy = rqlSort ? rqlSort : newOptions.sortField.default;
      angular.forEach(self.getSortOptions().options, function (option, key) {
        if (option.value === sortBy) {
          selectedSortOption = option;
        }
      });
      return selectedSortOption;
    };

    this.getSelectedOrder = function (order) {
      var selectedOption = '';
      var orderBy = order ? order : newOptions.orderField.default;
      angular.forEach(self.getOrderOptions().options, function (option, key) {
        if (option.value === orderBy) {
          selectedOption = option;
        }
      });
      return selectedOption;
    };

    this.getSortArg = function () {
      var order = null;
      var search = $location.search();
      var rqlQuery = RqlQueryService.parseQuery(search.query);
      if (rqlQuery) {
        var rqlSort = RqlQueryService.getTargetQuerySort(QUERY_TYPES.STUDIES, rqlQuery);
        if (rqlSort) {
          order = rqlSort.args[0].substring(0, 1) == '-' ? '-' :  self.getSelectedOrder(null);
          rqlSort = rqlSort.args[0].substring(0, 1) == '-' ? rqlSort.args[0].substring(1) : rqlSort.args[0];
          return {slectedOrder: self.getSelectedOrder(order), selectedSort: self.getSelectedSort(rqlSort)};
        }
      }
      return {
        slectedOrder: self.getSelectedOrder(null),
        selectedSort: self.getSelectedSort(null)
      };
    };

  }])
  .provider('sortWidgetOptions', SortWidgetOptionsFactory);
