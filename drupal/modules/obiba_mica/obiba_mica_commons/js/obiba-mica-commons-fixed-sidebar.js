/**
 * @file
 * JsScript to deal with FixSidebar
 */

(function ($) {
  Drupal.behaviors.obiba_mica_commons_fixed_sidebar = {
    attach: function (context, settings) {
      var template = Drupal.settings.template;
      var sidebar = $('div.fixed-sidebar-div');
      var content = $("div.main-container > div.row > section.col-sm-12");
      hide();
      updatePosition();

      $.ajax({
        'async': false,
        'url': Drupal.settings.basePath + 'mica/get_fixed_sidebar/' + template,
        'type': 'GET',
        'success': function (data) {
          // console.log("DATA", JSON.stringify(data));
          show();
          $(".side-bar-content").html(data['fixed_menu']);
        },
        "dataType": "json",
        'error': function (data) {
        }
      });

      function hide() {
        sidebar && $(sidebar).css('z-index', '-1000');
      }

      function show() {
        sidebar && $(sidebar).css('z-index', '1000');
      }

      function updatePosition() {
        if (!content || !sidebar) return;

        "col-sm-12" === $(content).attr('class')
          ? $(content).toggleClass('col-sm-12 col-sm-10 col-xs-12') && $(sidebar).addClass("pull-right col-sm-2 hidden-xs")
          : $(content).toggleClass('col-sm-10 col-sm-12 col-xs-12') && $(sidebar).removeClass("pull-right col-sm-2 hidden-xs");
      }
    }

  }

}(jQuery));