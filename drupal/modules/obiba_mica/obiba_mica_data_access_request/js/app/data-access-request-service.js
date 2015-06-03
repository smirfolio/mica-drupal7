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
  Drupal.behaviors.obiba_mica_data_access_request_service = {
    attach: function (context, settings) {
      var localPath = Drupal.settings.basePath;
      'use strict';

      mica.DataAccessRequest
        .factory('DataAccessFormResource', ['$resource',
          function ($resource) {
            return $resource('data-access-form', {}, {
              'get': {method: 'GET', errorHandler: true},
              'save': {method: 'PUT', errorHandler: true}
            });
          }])

        .factory('DataAccessRequestsResource', ['$resource',
          function ($resource) {
            return $resource(localPath + 'data-access-requests-action', {}, {
              'save': {method: 'POST', errorHandler: true},
              'get': {method: 'GET'}
            });
          }])

        .factory('DataAccessRequestCommentsResource', ['$resource',
          function ($resource) {
            return $resource(localPath + 'data-access-request-comments-action/:id/comments', {}, {
              //'save': {
              //  method: 'POST',
              //  params: {id: '@id'},
              //  headers: {'Content-Type': 'text/plain'},
              //  errorHandler: true
              //},
              'get': {method: 'GET', params: {id: '@id'}, errorHandler: true}
            });
          }])

        //.factory('DataAccessRequestCommentResource', ['$resource',
        //  function ($resource) {
        //    return $resource('ws/data-access-request/:id/comment/:commentId', {}, {
        //      'delete': {
        //        method: 'DELETE',
        //        params: {id: '@id', commentId: '@commentId'},
        //        errorHandler: true
        //      },
        //      'update': {
        //        method: 'PUT',
        //        params: {id: '@id', commentId: '@commentId'},
        //        headers: {'Content-Type': 'text/plain'},
        //        errorHandler: true
        //      }
        //    });
        //  }])

        .factory('DataAccessRequestResource', ['$resource',
          function ($resource) {
            return $resource(localPath + 'data-access-request-action/:id', {}, {
              'save': {method: 'PUT', params: {id: '@id'}, errorHandler: true},
              'get': {method: 'GET'},
              'delete': {method: 'DELETE'}
            });
          }])

        .factory('DataAccessRequestStatusResource', ['$resource',
          function ($resource) {
            return $resource('ws/data-access-request/:id/_status?to=:status', {}, {
              'update': {method: 'PUT', params: {id: '@id', status: '@status'}, errorHandler: true}
            });
          }])

        .factory('DataAccessRequestService',
        function () {
          this.status = {
            OPENED: 'OPENED',
            SUBMITTED: 'SUBMITTED',
            REVIEWED: 'REVIEWED',
            APPROVED: 'APPROVED',
            REJECTED: 'REJECTED'
          };

          var canDoAction = function (request, action) {
            return request.actions ? request.actions.indexOf(action) !== -1 : null;
          };

          this.actions = {
            canView: function (request) {
              return canDoAction(request, 'VIEW');
            },

            canEdit: function (request) {
              return canDoAction(request, 'EDIT');
            },

            canEditStatus: function (request) {
              return canDoAction(request, 'EDIT_STATUS');
            },

            canDelete: function (request) {
              return canDoAction(request, 'DELETE');
            }
          };

          var canChangeStatus = function (request, to) {
            return request.nextStatus ? request.nextStatus.indexOf(to) !== -1 : null;
          };

          this.nextStatus = {
            canSubmit: function (request) {
              return canChangeStatus(request, 'SUBMITTED');
            },

            canReopen: function (request) {
              return canChangeStatus(request, 'OPENED');
            },

            canReview: function (request) {
              return canChangeStatus(request, 'REVIEWED');
            },

            canApprove: function (request) {
              return canChangeStatus(request, 'APPROVED');
            },

            canReject: function (request) {
              return canChangeStatus(request, 'REJECTED');
            }

          };

          return this;
        });

    }
  }
}(jQuery));