(function ($) {
  Drupal.behaviors.obiba_mica_network_detail = {
    attach: function (context, settings) {
      if (context === document) {
        $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/network/' + settings.network_url + '/coverage')
          .done(function (data) {
            if (!data) {
              $('#coverage').remove();
              return;
            }

            $('#coverage').html(data).show();
            Drupal.attachBehaviors($('#coverage')[0], settings);
          })
          .fail(function () {
            $('#coverage').remove();
          });
      }
    }
  }
}(jQuery));