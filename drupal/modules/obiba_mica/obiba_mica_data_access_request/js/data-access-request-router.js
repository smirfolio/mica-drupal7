/*
 * Copyright (c) 2014 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

(function ($) {
  Drupal.behaviors.obiba_mica_data_access_request_router = {
    attach: function (context, settings) {


      'use strict';

      mica.dataAccessRequest.config(['$routeProvider', '$locationProvider',
        function ($routeProvider, $locationProvider) {
          $routeProvider
            .when('/data-access-request-list', {
//                templateUrl: 'app/access/views/data-access-request-list.html',
              controller: 'DataAccessRequestListController'
            })
            .when('/new', {
              templateUrl: 'obiba_main_app_angular/obiba_mica_data_access_request/obiba_mica_data_access_request-form-page',
              controller: 'DataAccessRequestEditController'
            })
            .when('/data-access-request/:id/edit', {
//                templateUrl: 'app/access/views/data-access-request-form.html',
              controller: 'DataAccessRequestEditController'
            })
            .when('/data-access-request/:id', {
//                templateUrl: 'app/access/views/data-access-request-view.html',
              template: '<div> hello word</div>',
              controller: 'DataAccessRequestViewController'
            });

        }]);


    }
  }
}(jQuery));