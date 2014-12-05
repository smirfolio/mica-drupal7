(function ($) {
  Drupal.behaviors.mica_client_commons_fixed_sidebar = {
    attach: function (context, settings) {
      var template = Drupal.settings.template;
      $.ajax({
        'async': false,
        'url': Drupal.settings.basePath + 'mica/get_fixed_sidebar/' + template,
        'type': 'GET',
        'success': function (data) {
          var content_fixed_sidebar = data['fixed_menu'];
          console.log(template);
          $(".sideBarContent").html(content_fixed_sidebar);
        },
        "dataType": "json",
        'error': function (data) {
        }
      });
    }

  }

}(jQuery));