/*
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

mica.ObibaSearch = angular.module('mica.ObibaSearch', [
    'obiba.mica.search'
  ])
  .run([
    'GraphicChartsConfig',
    function (GraphicChartsConfig) {
      GraphicChartsConfig.setOptions(Drupal.settings.GraphicChartsOptions);
  }])
  .config(['ngObibaMicaSearchTemplateUrlProvider','ngObibaMicaSearchProvider',
    function (ngObibaMicaSearchTemplateUrlProvider, ngObibaMicaSearchProvider) {
      ngObibaMicaSearchProvider.setOptions(Drupal.settings.angularjsApp.obibaSearchOptions);
      ngObibaMicaSearchTemplateUrlProvider.setHeaderUrl('search', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/obiba_mica_repository_search-view-header');
      ngObibaMicaSearchTemplateUrlProvider.setHeaderUrl('classifications', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/obiba_mica_repository_classifications-view-header');
    }]);
