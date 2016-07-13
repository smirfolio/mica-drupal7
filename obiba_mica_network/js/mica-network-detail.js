(function ($) {
  Drupal.behaviors.obiba_mica_network_detail = {
    attach: function (context, settings) {
      if (context === document) {
        if (settings.study_ids.length>0) {
          var resource_url = Drupal.settings.basePath
            + Drupal.settings.pathPrefix
            + 'mica/coverage/network/'
            + encodeURIComponent(JSON.stringify(settings.study_ids ? settings.study_ids : []));

          $.ajax(resource_url)
            .done(function (data) {
              if (! data) {
                $('#coverage').remove();
                return;
              }

              $('#coverage').html(data).show();
              Drupal.attachBehaviors($('#coverage')[0], settings);
            })
            .fail(function () {
              $('#coverage').remove();
            });

          $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + settings.currentPath + '/datasets')
              .done(function (data) {
                if (!data) {
                  $('#datasets').remove();
                  return;
                }
                $('#datasets').html(data).show();
                var datasets = $('#datasetsDisplay').data();
              })
              .fail(function () {
                $('#datasets').remove();
              });
              
        }
        else{
          $('#coverage').remove();
          $('#datasets').remove();
        }
      }
    }
  }
}(jQuery));