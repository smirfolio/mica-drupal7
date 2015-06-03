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
        'obiba.comments',
        'angularUtils.directives.dirPagination'
      ];

      'use strict';
      /* App Module */
      mica = angular.module('mica', modules.concat(Drupal.settings.angularjsApp.modules));
      mica.config(['$routeProvider',
        function ($routeProvider) {
          $routeProvider
            .when('/', {
              controller: 'MainController'
            });
        }]);

      mica.controller('MainController', [ function () {
      }]);
    }
  }
}(jQuery));