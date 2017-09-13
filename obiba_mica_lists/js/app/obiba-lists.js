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
  .config(['ngObibaMicaSearchProvider', 'markedProvider', 'sortWidgetOptionsProvider', function (ngObibaMicaSearchProvider, markedProvider, sortWidgetOptionsProvider) {
    if(Drupal.settings.obibaListOptions.studies){
      sortWidgetOptionsProvider.setOptions(Drupal.settings.obibaListOptions.studies);
    }
    if(Drupal.settings.obibaListOptions.networks){
      sortWidgetOptionsProvider.setOptions(Drupal.settings.obibaListOptions.networks);
    }
    if(Drupal.settings.obibaListOptions.datasets){
      sortWidgetOptionsProvider.setOptions(Drupal.settings.obibaListOptions.datasets);
    }

    markedProvider.setOptions({
      gfm: true,
      tables: true,
      sanitize: false
    });

    Drupal.settings.angularjsApp.obibaSearchOptions = angular.extend({},
      Drupal.settings.angularjsApp.obibaSearchOptions,
      Drupal.settings.obibaListSearchOptions);
      Drupal.settings.angularjsApp.obibaSearchOptions.obibaListOptions = Drupal.settings.obibaListOptions;
    ngObibaMicaSearchProvider.setOptions(Drupal.settings.angularjsApp.obibaSearchOptions);
  }])
  .config(['ngObibaMicaSearchTemplateUrlProvider',
    function (ngObibaMicaSearchTemplateUrlProvider) {
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchStudiesResultTable', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/studies-search-result-table-template');
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchNetworksResultTable', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/networks-search-result-table-template');
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchDatasetsResultTable', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/datasets-search-result-table-template');
      ngObibaMicaSearchTemplateUrlProvider.setTemplateUrl('searchResultList', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/search-result-list-template');
    }])
  .filter('getBaseUrl', function () {
    return function (param) {
      return Drupal.settings.basePath + 'mica/' + param;
    }
  }).filter('doSearchQuery', function () {
    return function (type, query) {
      return Drupal.settings.basePath + 'mica/repository#/search?type=' + type + '&query=' + query + '&display=list'
    }
  })
  .filter('getLabel', function () {
    return function (SelectSort, valueSort) {
      var result = null;
      angular.forEach(SelectSort.options, function (value, key) {
        if (value.value.indexOf(valueSort) !== -1) {
          result = value.label;
        }
      });
      return result;
    }
  });
