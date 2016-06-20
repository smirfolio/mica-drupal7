/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
 */

'use strict';

var modules = [
  'ngObiba',
  'ngRoute',
  'ngSanitize',
  'ngResource',
  'ui.bootstrap',
  'obiba.form',
  'obiba.comments',
  'angularUtils.directives.dirPagination',
  'pascalprecht.translate',
  'ngObibaMica'
];
var sanitizeModules = function (origArr) {
  var newArr = [],
    origLen = origArr.length,
    found, x, y;

  for (x = 0; x < origLen; x ++) {
    found = undefined;
    for (y = 0; y < newArr.length; y ++) {
      if (origArr[x] === newArr[y]) {
        found = true;
        break;
      }
    }
    if (! found && origArr[x] !== false) {
      newArr.push(origArr[x]);
    }
  }
  return newArr;
}
var drupalModules = sanitizeModules(Drupal.settings.angularjsApp.modules);

/* App Module */
if (drupalModules) {
  modules = modules.concat(drupalModules);
}
var mica = angular.module('mica', modules);

/**
 * Data Access Request related provider configuration
 */
mica.config(['ngObibaMicaSearchProvider', 'ngObibaMicaUrlProvider',
  function (ngObibaMicaSearchProvider, ngObibaMicaUrlProvider) {
    ngObibaMicaUrlProvider.setUrl('DataAccessFormConfigResource', 'data-access-form/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestsResource', 'requests/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestResource', 'request/:id/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestAttachmentDownloadResource', 'request/:id/attachments/:attachmentId/_download/ws');
    ngObibaMicaUrlProvider.setUrl('SchemaFormAttachmentDownloadResource', 'request/form/attachments/:attachmentName/:attachmentId/_download/ws?path=:path');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestDownloadPdfResource', 'request/:id/_pdf/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestCommentsResource', 'request/:id/comments/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestCommentResource', 'request/:id/comment/:commentId/ws');
    ngObibaMicaUrlProvider.setUrl('DataAccessRequestStatusResource', 'request/:id/_status/:status/ws');
    ngObibaMicaUrlProvider.setUrl('TempFileUploadResource', 'request/upload-file');
    ngObibaMicaUrlProvider.setUrl('TempFileResource', 'request/file/:id');
    ngObibaMicaUrlProvider.setUrl('TaxonomiesSearchResource', Drupal.settings.basePath + 'mica/repository/taxonomies/_search/ws');
    ngObibaMicaUrlProvider.setUrl('TaxonomiesResource', Drupal.settings.basePath + 'mica/repository/taxonomies/_filter/ws');
    ngObibaMicaUrlProvider.setUrl('TaxonomyResource', Drupal.settings.basePath + 'mica/repository/taxonomy/:taxonomy/_filter/ws');
    ngObibaMicaUrlProvider.setUrl('VocabularyResource', Drupal.settings.basePath + 'mica/repository/taxonomy/:taxonomy/vocabulary/:vocabulary/_filter/ws');
    ngObibaMicaUrlProvider.setUrl('JoinQuerySearchResource', Drupal.settings.basePath + 'mica/repository/:type/_rql/:query/ws');
    ngObibaMicaUrlProvider.setUrl('JoinQueryCoverageResource', Drupal.settings.basePath + 'mica/repository/variables/_coverage/:query/ws');
    ngObibaMicaUrlProvider.setUrl('JoinQueryCoverageDownloadResource',  Drupal.settings.basePath + 'mica/repository/variables/_coverage_download/:query/ws');
    ngObibaMicaUrlProvider.setUrl('VariablePage', Drupal.settings.basePath + 'mica/variable/:variable');
    ngObibaMicaUrlProvider.setUrl('NetworkPage', Drupal.settings.basePath + 'mica/network/:network');
    ngObibaMicaUrlProvider.setUrl('StudyPage', Drupal.settings.basePath + 'mica/study/:study');
    ngObibaMicaUrlProvider.setUrl('StudyPopulationsPage', Drupal.settings.basePath + 'mica/study/:study/#population-:population');
    ngObibaMicaUrlProvider.setUrl('DatasetPage', Drupal.settings.basePath + 'mica/:type/:dataset');
    ngObibaMicaUrlProvider.setUrl('BaseUrl', Drupal.settings.basePath);
    ngObibaMicaUrlProvider.setUrl('FileBrowserFileResource', Drupal.settings.basePath + 'mica/file');
    ngObibaMicaUrlProvider.setUrl('FileBrowserSearchResource', Drupal.settings.basePath + 'mica/files/search');
    ngObibaMicaUrlProvider.setUrl('FileBrowserDownloadUrl', Drupal.settings.basePath + 'mica/file/download?path=:path&inline=:inline');
    ngObibaMicaUrlProvider.setUrl('GraphicsSearchRootUrl', 'mica/repository#/search');

    ngObibaMicaSearchProvider.setOptions(Drupal.settings.angularjsApp.obibaSearchOptions);
  }]);

mica.provider('SessionProxy',
  function () {
    function Proxy(user) {
      var roles = Object.keys(user.roles).map(function (key) {
        return user.roles[key];
      });
      var real = {login: user.name, roles: roles, profile: null};

      this.login = function () {
        return real.login;
      };

      this.roles = function () {
        return real.roles;
      };

      this.profile = function () {
        return real.profile;
      };
    }

    this.$get = function () {
      return new Proxy(Drupal.settings.angularjsApp.user);
    };
  });

mica.controller('MainController', [
  function () {
  }]);

mica.factory('TranslationService', ['$resource',
  function ($resource) {
    return $resource(Drupal.settings.basePath + 'obiba_mica_app_angular/translation', {}, {
      'get': {method: 'GET'}
    });
  }]);

mica.config(['$routeProvider', '$translateProvider',
  function ($routeProvider, $translateProvider) {
    $routeProvider
      .when('/', {
        controller: 'MainController'
      });
    $translateProvider.preferredLanguage(Drupal.settings.angularjsApp.locale)
      .useLoader('DrupalTranslationLoader', {lang: Drupal.settings.angularjsApp.locale})
      .fallbackLanguage('en')
      .useSanitizeValueStrategy('escaped');
  }]);

mica.factory('DrupalTranslationLoader',
  function ($http, $q) {
    return function (options) {
      var deferred = $q.defer();

      $http({
        method: 'GET',
        url: Drupal.settings.basePath + 'obiba_mica_app_angular/translation/' + options.lang
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
        if (! response.data.messageTemplate) {
          response.data.messageTemplate = 'server.error.' + response.status;
        }
      } else {
        response.data = {messageTemplate: 'server.error.' + response.status};
      }
      return response;
    }
  }

});

mica.factory('ForbiddenDrupalRedirect', function () {

  var createDestinationPath = function (path) {
    if (angular.isDefined(path)) {
      var regExp = new RegExp('(view|edit)\/(.*)$');
      var results = regExp.exec(path);
      if (results && results.length > 1) {
        return '?destination=mica/data-access/request/redirect/' + results[1] + '/' + results[2];
      }

      return '';
    }
  };

  return {
    redirectDrupalMessage: function (response) {
      if (response.status && response.status == 403 && ! Drupal.settings.angularjsApp.authenticated) {
        $.post('un-authorized-error');
        $(window).delay(200).queue(function () {
          window.location = Drupal.settings.basePath + 'user/login' + createDestinationPath(window.location.hash);
        });
      }
    }
  }

});

/**
 * A N G U L A R     G L O B A L     S E R V I C E S
 */

mica.service('ServerErrorAlertService', ['AlertService', 'ServerErrorUtils', 'ErrorTemplate',
  function (AlertService, ServerErrorUtils, ErrorTemplate) {
    this.alert = function (id, response) {
      if (angular.isDefined(response.data)) {
        var errorDto = JSON.parse(response.data);
        if (angular.isDefined(errorDto) && angular.isDefined(errorDto.messageTemplate)) {
          AlertService.alert({
            id: id,
            type: 'danger',
            msgKey: errorDto.messageTemplate,
            msgArgs: errorDto.arguments
          });
          return;
        }
      }

      AlertService.alert({
        id: id,
        type: 'danger',
        msg: ServerErrorUtils.buildMessage(ErrorTemplate.getServerError(response))
      });
    };

    return this;
  }]);

mica.service('AttributeService',
  function () {
    return {
      getAttributes: function (container, names) {
        if (! container && ! container.attributes && ! names) {
          return null;
        }
        return container.attributes.filter(
          function (attribute) {
            return names.indexOf(attribute.name) !== - 1;
          });
      },

      getValue: function (attribute) {
        if (! attribute) {
          return null;
        }
        var value = attribute.values.filter(
          function (value) {
            return value.lang === Drupal.settings.angularjsApp.locale || value.lang === 'und';
          });

        return value.length > 0 ? value[0].value : null;
      }
    }
  });

mica.service('LocalizedStringService',
  function () {
    return {
      getValue: function (localized) {
        if (! localized) {
          return null;
        }
        var value = localized.filter(
          function (locale) {
            return locale.lang === Drupal.settings.angularjsApp.locale || locale.lang === 'und';
          });

        return value.length > 0 ? value[0].value : null;
      },
      getLocal: function () {
        return Drupal.settings.angularjsApp.locale;
      }
    }
  })
  .service('LocalizedValues',
    function () {
      this.for = function (values, lang, keyLang, keyValue) {
        if (angular.isArray(values)) {
          var result = values.filter(function (item) {
            return item[keyLang] === lang;
          });

          if (result && result.length > 0) {
            return result[0][keyValue];
          }
        }
        return '';
      };

      this.forLocale = function (values, lang) {
        var rval = this.for(values, lang, 'locale', 'text');
        if (rval === '') {
          rval = this.for(values, 'und', 'locale', 'text');
        }
        return rval;
      };

      this.forLang = function (values, lang) {
        var rval = this.for(values, lang, 'lang', 'value');
        if (rval === '') {
          rval = this.for(values, 'und', 'lang', 'value');
        }
        return rval;
      };

      this.getLocal = function () {
        return Drupal.settings.angularjsApp.locale;
      };

      this.formatNumber = function (number){
        return number.toLocaleString(this.getLocal());
      };

    })
  .service('GraphicChartsConfigurations', ['GraphicChartsConfig', function (GraphicChartsConfig) {
    this.setClientConfig = function () {
      GraphicChartsConfig.setOptions(Drupal.settings.GraphicChartsOptions);
    };
    this.getClientConfig = function () {
      return Drupal.settings.GraphicChartsOptions;
    };
  }]);
