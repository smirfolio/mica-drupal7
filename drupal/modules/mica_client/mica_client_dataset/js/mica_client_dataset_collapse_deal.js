(function ($) {
  Drupal.behaviors.mica_client_dataset_collapse = {
    attach: function (context, settings) {
      var newst = {};
      var st = getCookieData();
      console.log(st);

      $(".block-content").each(function (id, state) {
        var current_id = this.id;
        $("#" + current_id).removeClass('in');
        //show the last visible group
        if (st[current_id]) {
          $("#" + current_id).collapse("show");
        }

      });

//when a group is shown, save it as the active accordion group
      $(".block").on('shown.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';
          }
        });
        saveCookieData(newst)
      });

      //when a group is shown, save it as the active accordion group
      $(".block").on('hidden.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';
          }
        });
        saveCookieData(newst)
      });

      function saveCookieData(newst) {
        // Stringify the object in JSON format for saving in the cookie.
        var cookieString = '{ ';
        var cookieParts = [];

        $.each(newst, function (id, setting) {

          cookieParts[cookieParts.length] = '"' + id + '": "' + setting + '"';
        });
        cookieString += cookieParts.join(', ') + ' }';
        // console.log(cookieString);
        $.cookie('activeAccordionGroup', cookieString, {
          time: 1
        });
        console.log($.cookie('activeAccordionGroup'));
      };

      function getCookieData() {
        if ($.cookie) {
          var cookieString = $.cookie('activeAccordionGroup');
          return cookieString ? $.parseJSON(cookieString) : {};
        }
        else {
          return '';
        }
      };

    }
  }
}(jQuery));