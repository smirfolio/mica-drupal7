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
        'obiba.form',
        'obiba.comments',
        'angularUtils.directives.dirPagination',
        'pascalprecht.translate'
      ];

      'use strict';
      /* App Module */
      mica = angular.module('mica', modules.concat(Drupal.settings.angularjsApp.modules));
      mica.config(['$routeProvider', '$translateProvider',
        function ($routeProvider, $translateProvider) {
          $routeProvider
            .when('/', {
              controller: 'MainController'
            });

          $translateProvider.useLoader('DrupalTranslationLoader', {});
          $translateProvider.preferredLanguage('en');


        }]);

      mica.controller('MainController', [
        function () {
        }]);

      mica.factory('TranslationService', ['$resource',
        function ($resource) {
          return $resource(Drupal.settings.basePath + 'obiba_main_app_angular/translation', {}, {
            'get': {method: 'GET'}
          });
        }]);

      mica.factory('DrupalTranslationLoader',
        function ($http, $q) {
          return function (options) {
            var deferred = $q.defer();

            $http({
              method: 'GET',
              url: Drupal.settings.basePath + 'obiba_main_app_angular/translation'
            }).success(function (data) {
              deferred.resolve(data);
            }).error(function () {
              deferred.reject(options.key);
            });

            return deferred.promise;
          }
        });

    }
  }
}(jQuery));