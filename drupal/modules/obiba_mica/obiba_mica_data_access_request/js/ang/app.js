/*
 * Copyright (c) 2015 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

(function ($) {
  Drupal.behaviors.obiba_mica_data_access_request = {
    attach: function (context, settings) {
      console.log('im in angular');
      'use strict';
      /* App Module */
      var DataAccessRequest = angular.module('DataAccessRequest', [
        'ngResource',
        'ngSanitize',
        'ui.bootstrap',
        'schemaForm'
      ]);


      DataAccessRequest.controller('DataAccessRequestForm', ['$scope', '$log', function ($scope, $log) {
        $scope.model = {};
        $scope.form = angular.fromJson(settings.form);
        $scope.schema = angular.fromJson(settings.schema);
        console.log($scope.form);
        $scope.model = {
          'mytest': "variable test"
        }


        $scope.onSubmit = function (theForm) {
          // First we broadcast an event so all fields validate themselves
          $scope.$broadcast('schemaFormValidate');
          // Then we check if the form is valid
          if (theForm.$valid) {

          }
          $scope.closeAlert = function () {
            $scope.alert = [];
          };
        };

      }]);


//      DataAccessRequest.factory('UserResource', ['$http',
//        function ($http) {
//          return {
//            post: function (data) {
//              return $http.post('/drupal/agate_user_join', $.param(data), {
//                headers: {'Content-Type': 'application/x-www-form-urlencoded'}
//              });
//            }
//          };
//        }]);


    }
  }
}(jQuery));


