/*
 * Copyright (c) 2017 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

mica.ObibaLists = angular.module('mica.ObibaSearch', [
    'obiba.mica.search'
  ])
  .run()
  .config(['ngObibaMicaSearchProvider','markedProvider', function(ngObibaMicaSearchProvider,markedProvider){
    markedProvider.setOptions({
      gfm: true,
      tables: true,
      sanitize: false
    });

    Drupal.settings.angularjsApp.obibaSearchOptions = angular.extend({},
      Drupal.settings.angularjsApp.obibaSearchOptions,
      Drupal.settings.obibaListOptions);
    ngObibaMicaSearchProvider.setOptions(Drupal.settings.angularjsApp.obibaSearchOptions);
  }])
  .config(['ngObibaMicaSearchTemplateUrlProvider',
    function (ngObibaMicaSearchTemplateUrlProvider) {
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchStudiesResultTable', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/studies-search-result-table-template');
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchResultList', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/search-result-list-template');
    }])
  .filter('getBaseUrl', function(){
      return function (param) {
       return Drupal.settings.basePath + 'mica/' + param;
      }
  }).filter('doSearchQuery', function(){
    return function(type, query){
      return Drupal.settings.basePath + 'mica/repository#/search?type='+type+'&query='+query+'&display=list'
    }
  })
  .controller('listSortWidgetController', ['$scope', '$rootScope', 'sortWidgetService',
    function ($scope, $rootScope, sortWidgetService) {

    var emitter = $rootScope.$new();
    $scope.selectSort = sortWidgetService.getSortOptions();
    $scope.selectOrder = sortWidgetService.getOrderOptions();
    $scope.selectedSort =  $scope.selectSort.options[0];
    $scope.selectedOrder = $scope.selectOrder.options[0];

    var selectedOptions = sortWidgetService.getSortArg();
    if(selectedOptions){
      $scope.selectedSort = selectedOptions.selectedSort ? selectedOptions.selectedSort: $scope.selectSort.options[0];
      $scope.selectedOrder = selectedOptions.slectedOrder? selectedOptions.slectedOrder : $scope.selectOrder.options[0];
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
        sortItm: '=',
      },
      controller: 'listSortWidgetController',
      templateUrl: Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/list-sort-widget-template'
    };

    // <div list-sort-widget sort-item="
  }])
  .service('sortWidgetService', ['$filter', '$location', 'RqlQueryService', function($filter, $location, RqlQueryService){
    var self = this;
    this.getOrderOptions = function() {
     return  {
      options: [
        {
          value: '',
          label: $filter('translate')('asc')
        },
        {
          value: '-',
          label: $filter('translate')('desc')
        }
      ]
    }
    };
    this.getSortOptions = function(){
      return {
      options: [
        {
          value: 'name',
          label: $filter('translate')('name')
        },
        {
          value: 'acronym',
          label: $filter('translate')('acronym')
        },
        {
          value: 'numberOfParticipants-participant-number',
          label: $filter('translate')('study_taxonomy.vocabulary.numberOfParticipants-participant-number.title')
        }
      ]
    }
    };
    this.getSelectedSort = function (rqlSort){
      var selectedSortOption = null;
      angular.forEach(self.getSortOptions().options, function(option, key){
        if(option.value === rqlSort){
          selectedSortOption = option;
        }
      });
      return selectedSortOption;
    };

    this.getSelectedOrder = function (order){
      var selectedOption = null;
      angular.forEach(self.getOrderOptions().options, function(option, key){
        if(option.value === order){
          selectedOption =option;
        }
      });
      return selectedOption;
    };

    this.getSortArg = function(){
      var order = '';
      var search = $location.search();
      var rqlQuery = RqlQueryService.parseQuery(search.query);
      if(rqlQuery){
        var rqlSort =  RqlQueryService.getTargetQuerySort(QUERY_TYPES.STUDIES, rqlQuery);
        if(rqlSort){
          order = rqlSort.args[0].substring(0, 1) == '-' ? '-' : '';
          rqlSort = rqlSort.args[0].substring(0, 1) == '-' ? rqlSort.args[0].substring(1) : rqlSort.args[0];
          return {slectedOrder: self.getSelectedOrder(order), selectedSort: self.getSelectedSort(rqlSort)};
        }
      }
      return null;
    };
  }]);
