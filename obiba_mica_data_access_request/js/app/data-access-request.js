/*
 * Copyright (c) 2015 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

mica.DataAccessRequest = angular.module('mica.DataAccessRequest', [
  'obiba.mica.access',
  'sfObibaFileUpload',
  'sfCheckboxgroup',
  'schemaForm-datepicker'
])
  .config(['ngObibaMicaAccessTemplateUrlProvider',
    function (ngObibaMicaAccessTemplateUrlProvider) {
      ngObibaMicaAccessTemplateUrlProvider.setHeaderUrl('view',Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/obiba_mica_data_access_request-view-header');
      ngObibaMicaAccessTemplateUrlProvider.setHeaderUrl('form', Drupal.settings.basePath + 'obiba_mica_app_angular_view_template/obiba_mica_data_access_request-form-header');
    }])
  .run(['DataAccessRequestConfig', function(DataAccessRequestConfig){
    DataAccessRequestConfig.setOptions(Drupal.settings.angularjsApp.data_access_config);
  }]);
