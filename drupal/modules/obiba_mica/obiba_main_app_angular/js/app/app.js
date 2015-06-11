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
      mica.factory('ErrorTemplate', function () {
        return {
          getServerError: function (response) {
            if (angular.isObject(response.data)) {
              if (!response.data.messageTemplate) {
                response.data.messageTemplate = 'server.error.' + response.status;
              }
            } else {
              response.data = {messageTemplate: 'server.error.' + response.status};
            }
            return  response;
          }
        }


      });

      mica.factory('ForbiddenDrupalRedirect', function () {
        return {
          redirectDrupalMessage: function (response) {
            if (response.status && response.status == 403) {
              $.post('un-authorized-error');
              $(window).delay(200).queue(function () {
                window.location = Drupal.settings.basePath + 'user/login'
              });
            }
          }
        }


      });

    }
  }
}(jQuery));