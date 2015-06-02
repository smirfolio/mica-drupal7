/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
 */
(function ($) {
  Drupal.behaviors.obiba_angular_second_controllers = {
    attach: function (context, settings) {
      console.log(mica);
      'use strict';
      mica.secondApp.controller('AppSecondController', ['$scope', function ($scope) {
        console.log('exsecuted im app 2 controller loaded');
        $scope.firstName = "John";
        $scope.lastName = "Doe";
      } ]);

    }
  }
}(jQuery));