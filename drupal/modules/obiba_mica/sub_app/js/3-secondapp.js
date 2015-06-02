/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
 */
(function ($) {
  Drupal.behaviors.obiba_angular_secondapp = {
    attach: function (context, settings) {

      'use strict';
      /* App Module */

      mica.secondApp =
        angular.module('mica.subApp', [
          'ngResource',
          'ngRoute'
        ]);

      mica.secondApp
        .config(['$routeProvider',
          function ($routeProvider) {
            $routeProvider
              .when('/controlle2', {
                templateUrl: 'obiba_main_app_angular/sub_app/sub_app_ng_template_controller',
                //    template: '<div>Second controller</div>',
                controller: 'AppSecondController'
              })

          }]);


    }
  }
}(jQuery));