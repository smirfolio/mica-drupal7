/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
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


