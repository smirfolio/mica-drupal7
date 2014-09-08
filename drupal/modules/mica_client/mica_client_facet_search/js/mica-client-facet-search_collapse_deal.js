(function ($) {
  Drupal.behaviors.mica_client_dataset_collapse = {
    attach: function (context, settings) {
      var newst = {};
      var newst1 = {};
      var sectionid;
      var st = getCookieData();
      if (jQuery.isEmptyObject(st)) {
        $(".block-content").each(function (id, state) {
          var current_id = this.id;
          $("#" + current_id).collapse("show");
          newst1[current_id] = 'in';

        });

        saveCookieData(st);
      }
      else {
        $(".block-content").each(function (id, state) {
          var current_id = this.id;

          //show the last visible group
          if (st[current_id]) {
            $("#" + current_id).collapse("show");
            newst1[current_id] = 'in';
          }
          else {
            $("#" + current_id).collapse("hide");
            dealwithhrefico(current_id, 'collapsed');
            delete newst1[current_id];

          }

        });

        saveCookieData(newst1);
      }

//when a group is shown, save it as the active accordion group
      $(".block").on('shown.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';

          }
          else {
            delete newst[current_id];
          }
        });
        saveCookieData(newst);
      });

      //when a group is shown, save it as the active accordion group
      $(".block").on('hidden.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';
          }
          else {
            delete newst[current_id];
          }

        });
        saveCookieData(newst)
      });


      /********** Show more show less on search page********/

      $('.charts').on('shown.bs.collapse', function () {
        $('.text-button-field').html('Show less');
      });

      $('.charts').on('hidden.bs.collapse', function () {
        $('.text-button-field').html('Show all');
      });
      /********************/
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
          time: 1,
          path: window.location.pathname
        });
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

      function dealwithhrefico(current_id, collapse) {
        if (collapse && current_id) {
          sectionid = current_id.replace("collapse-", "");
          $("#" + sectionid + " h2.block-title a:first").addClass(collapse);
        }
      }

    }
  }
}(jQuery));