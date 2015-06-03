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
  Drupal.behaviors.obiba_mica_data_access_request_controller = {
    attach: function (context, settings) {

      'use strict';
      var user = Drupal.settings.angularjsApp.user;
      mica.DataAccessRequest
        .controller('DataAccessRequestViewController', ['$rootScope', '$scope', '$routeParams',
          'DataAccessRequestResource',
          'DataAccessRequestService',
          'DataAccessRequestStatusResource',
          'DataAccessFormResource',
          'DataAccessRequestCommentsResource',
          'DataAccessRequestCommentResource',
          'NOTIFICATION_EVENTS',

          function ($rootScope,
                    $scope,
                    $routeParams,
                    DataAccessRequestResource,
                    DataAccessRequestService,
                    DataAccessRequestStatusResource,
                    DataAccessFormResource,
                    DataAccessRequestCommentsResource,
                    DataAccessRequestCommentResource,
                    NOTIFICATION_EVENTS) {

            var onError = function (response) {
              AlertService.alert({
                id: 'DataAccessRequestViewController',
                type: 'danger',
                msg: ServerErrorUtils.buildMessage(response)
              });
            };

            var retrieveComments = function() {
              console.log('retrieveComments()');
              $scope.form.comments = DataAccessRequestCommentsResource.get({id: $routeParams.id});
            };

            var submitComment = function(comment) {
              console.log('submitComment()');
              DataAccessRequestCommentsResource.save({id: $routeParams.id}, comment.message, retrieveComments, onError);
            };

            var updateComment = function(comment) {
              console.log('updateComment()');
              DataAccessRequestCommentResource.update({id: $routeParams.id, commentId: comment.id}, comment.message, retrieveComments, onError);
            };

            var deleteComment = function(comment) {
              console.log('deleteComment()', NOTIFICATION_EVENTS);
              $scope.commentToDelete = comment.id;
              $rootScope.$broadcast(NOTIFICATION_EVENTS.showConfirmDialog,
                {
                  titleKey: 'comment.delete-dialog.title',
                  messageKey:'comment.delete-dialog.message',
                  messageArgs: [comment.createdBy]
                }, comment.id
              );
            };

            $scope.$on(NOTIFICATION_EVENTS.confirmDialogAccepted, function (event, id) {
              if ($scope.commentToDelete === id) {
                console.log('retrieveComments() EVENT');
                DataAccessRequestCommentResource.delete({id: $routeParams.id, commentId: id}, {}, retrieveComments, onError);
              }
            });

            $scope.form = {
              schema: {},
              definition: {},
              model: {},
              comments: null
            };

            $scope.retrieveComments = retrieveComments;
            $scope.submitComment = submitComment;
            $scope.updateComment = updateComment;
            $scope.deleteComment = deleteComment;
            $scope.actions = DataAccessRequestService.actions;
            $scope.nextStatus = DataAccessRequestService.nextStatus;
            var getRequest = function () {
              return DataAccessRequestResource.get({id: $routeParams.id}, function onSuccess(request) {
                $scope.form.model = request.content ? JSON.parse(request.content) : {};

                // Retrieve form data
                DataAccessFormResource.get(
                  function onSuccess(dataAccessForm) {
                    $scope.form.definition = JSON.parse(dataAccessForm.definition);
                    $scope.form.schema = JSON.parse(dataAccessForm.schema);
                    $scope.form.schema.readonly = true;
                    $("a.download-btn").on('click', function (event) {
                      // create a form for the file upload
                      var form = $("<form action='data-access-request/" + request.id + '/_pdf' + "' method='get'>");
                      $(this).after(form);
                      form.submit().remove();
                      return false;
                    });
                    // $scope.$broadcast('schemaFormRedraw');
                  },
                  onError
                );

                request.attachments = request.attachments || [];

                return request;
              });
            };

            $scope.dataAccessRequest = $routeParams.id ? getRequest() : {};

            $scope.delete = function () {
              DataAccessRequestResource.delete({id: $scope.dataAccessRequest.id});
            };

            var onUpdatStatusSuccess = function () {
              $scope.dataAccessRequest = getRequest();
            };

            $scope.submit = function () {
              $scope.$broadcast('schemaFormValidate');
              if ($scope.forms.requestForm.$valid) {
                DataAccessRequestStatusResource.update({
                  id: $scope.dataAccessRequest.id,
                  status: "SUBMITTED"
                }, onUpdatStatusSuccess, onError);
              } else {
                AlertService.alert({
                  id: 'DataAccessRequestViewController',
                  type: 'danger',
                  msgKey: 'data-access-request.submit.invalid'
                });
              }
            };
            $scope.reopen = function () {
              DataAccessRequestStatusResource.update({
                id: $scope.dataAccessRequest.id,
                status: "OPENED"
              }, onUpdatStatusSuccess, onError);
            };
            $scope.review = function () {
              DataAccessRequestStatusResource.update({
                id: $scope.dataAccessRequest.id,
                status: "REVIEWED"
              }, onUpdatStatusSuccess, onError);
            };
            $scope.approve = function () {
              DataAccessRequestStatusResource.update({
                id: $scope.dataAccessRequest.id,
                status: "APPROVED"
              }, onUpdatStatusSuccess, onError);
            };
            $scope.reject = function () {
              DataAccessRequestStatusResource.update({
                id: $scope.dataAccessRequest.id,
                status: "REJECTED"
              }, onUpdatStatusSuccess, onError);
            };

            $scope.forms = {};

          }])

        .controller('DataAccessRequestEditController', ['$log', '$scope', '$routeParams', '$location',
          'DataAccessRequestsResource',
          'DataAccessRequestResource',
          'DataAccessFormResource',
          'AlertService',
          'ServerErrorUtils',
          //'Session',
          'DataAccessRequestService',

          function ($log, $scope, $routeParams, $location, DataAccessRequestsResource, DataAccessRequestResource, DataAccessFormResource, AlertService, ServerErrorUtils, //Session,
                    DataAccessRequestService) {
            var onSuccess = function (response, getResponseHeaders) {
//              var parts = getResponseHeaders().location.split('/');
//              $location.path('/view/' + parts[parts.length - 1]).replace();

              console.log(getResponseHeaders());
            };

            var onError = function (response) {
              AlertService.alert({
                id: 'DataAccessRequestEditController',
                type: 'danger',
                msg: ServerErrorUtils.buildMessage(response)
              });
            };

            var submit = function () {
              $scope.$broadcast('schemaFormValidate');
            };

            var cancel = function () {
              $location.path('/view' + ($scope.dataAccessRequest.id ? '/' + $scope.dataAccessRequest.id : 's')).replace();
            };

            var save = function () {
              $scope.dataAccessRequest.content = JSON.stringify($scope.form.model);

              if ($scope.newRequest) {
                DataAccessRequestsResource.save($scope.dataAccessRequest, function () {
                  console.log(Drupal.settings);
                  window.location = Drupal.settings.basePath + 'data-access-request-list'
                }, onError);
              } else {
                DataAccessRequestResource.save($scope.dataAccessRequest, function () {
                  $location.path('/view' + ($scope.dataAccessRequest.id ? '/' + $scope.dataAccessRequest.id : 's')).replace();
                }, onError);
              }
            };

            // Retrieve form data
            DataAccessFormResource.get(
              function onSuccess(dataAccessForm) {
                $scope.form.definition = JSON.parse(dataAccessForm.definition);
                $scope.form.schema = JSON.parse(dataAccessForm.schema);

                $scope.dataAccessRequest = $routeParams.id ?
                  DataAccessRequestResource.get({id: $routeParams.id}, function onSuccess(request) {
                    $scope.form.model = request.content ? JSON.parse(request.content) : {};
                    $scope.canEdit = DataAccessRequestService.actions.canEdit(request);
                    $scope.form.schema.readonly = !$scope.canEdit;
                    $scope.$broadcast('schemaFormRedraw');
                    request.attachments = request.attachments || [];
                    return request;
                  }) : {
                  applicant: user.name,
                  status: DataAccessRequestService.status.OPENED,
                  attachments: []
                };
              },
              onError
            );

            $scope.form = {
              schema: {},
              definition: {},
              model: {}
            };

            $scope.requestId = $routeParams.id;
            $scope.newRequest = $routeParams.id ? false : true;
            $scope.cancel = cancel;
            $scope.save = save;
            $scope.editable = true;
            $scope.submit = submit;

          }]);


    }
  }
}(jQuery));