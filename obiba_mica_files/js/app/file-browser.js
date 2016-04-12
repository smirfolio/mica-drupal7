mica.fileBrowser = angular.module('mica.fileBrowser', [
    'obiba.mica.fileBrowser'
  ])
  .run(['ngObibaMicaFileBrowserOptions', function (ngObibaMicaFileBrowserOptions) {
    ngObibaMicaFileBrowserOptions.downloadInline = false;
  }]);
