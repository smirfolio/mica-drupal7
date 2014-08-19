(function ($) {
  Drupal.behaviors.queries = {
    attach: function (context, settings) {

      /*******************/
      $.extend({
        getUrlVars: function () {
          var vars = [], hash;
          var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
          for (var i = 0; i < hashes.length; i++) {
            hash = hashes[i].split('=');
            //console.log(decodeURIComponent(hash[1]));
            vars.push(decodeURIComponent(hash[1]));
          }

          return vars;
        },
        sendCheckboxCheckedValues: function (idcheckbox) {
          var serializedData = "";
          $('form').each(function () {
            var SerilizedForm = ($(this).serialize());
            if (SerilizedForm && $(this).attr('id').match(/facet-search/g)) {

              serializedData = serializedData.concat(SerilizedForm).concat('&');
            }
          });
//          if (idcheckbox) {
//            console.log(serializedData);
//            console.log(idcheckbox);
//          }
          return serializedData;
        }
      });


      /**********************/
      var allVars = $.getUrlVars();
      $('input[type="checkbox"]').each(function () {
        var currInputValue = $(this).attr('value');
        if ($.inArray(currInputValue, allVars) !== -1) {
          $(this).attr('checked', true);
          $(this).parent().addClass("selected_item");
        }
      });

      $("div#checkthebox").on("click", function () {
        var idcheckbox = $(this).attr("term");

        $('#' + idcheckbox).change(function () {

          console.log($('#' + idcheckbox).is(":checked"));
          if ($('#' + idcheckbox).is(":checked")) {

            $('#' + idcheckbox).attr('checked', true);
            $.sendCheckboxCheckedValues();
            window.location = '?' + $.sendCheckboxCheckedValues();

          }

          else {
            $.sendCheckboxCheckedValues(idcheckbox);
            window.location = '?' + $.sendCheckboxCheckedValues(idcheckbox);
          }

        });


      });
      ///her we goo
      if (Drupal.settings.mica_client_study.queries) {
        // console.log(Drupal.settings.mica_client_study.queries);

      }


    }
  }
})(jQuery);