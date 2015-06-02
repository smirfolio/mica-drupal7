/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
 */
var mica;
(function ($) {
  Drupal.behaviors.obiba_angular_app = {
    attach: function (context, settings) {

      var modules = [
        'ngObiba',
        'ngRoute',
        'ngSanitize',
        'ngResource',
        'ui.bootstrap',
        'obiba.notification',
        'obiba.form',
        'angularUtils.directives.dirPagination'
      ];

      'use strict';
      /* App Module */
      mica = angular.module('mica', modules.concat(Drupal.settings.angularjsApp.modules));
      mica.config(['$routeProvider',
        function ($routeProvider) {
          $routeProvider
            .when('/', {
              //   templateUrl: 'obiba_angular/obiba_angular/main.html',
              controller: 'MainController'
            });
        }]);

      mica.controller('MainController', ['$location', function ($location) {
        console.log('im loaded');
      }]);
    }
  }
}(jQuery));