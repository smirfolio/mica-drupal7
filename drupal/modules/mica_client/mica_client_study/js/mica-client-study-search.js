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
            vars.push(hash[1]);
          }

          return vars;
        },
        sendCheckboxCheckedValues: function () {
          var serializedData = "";
          $('form').each(function () {
            var SerilizedForm = ($(this).serialize());
            console.log(SerilizedForm);
            if (SerilizedForm) {
              serializedData = serializedData.concat(SerilizedForm).concat('&');
            }
          });
          return serializedData;
        }
      });


      /**********************/
      var allVars = $.getUrlVars();
      $('input[type="checkbox"]').each(function () {
        var currInputValue = $(this).attr('value');
        if ($.inArray(currInputValue, allVars) !== -1) {
          $(this).prop("checked", true);
          $(this).parent().addClass("selected_item");
        }
      });

      $("div#checkthebox").click(function () {
        var idcheckbox = $(this).attr("term");

        if ($('#' + idcheckbox).is(':checked')) {
          $('#' + idcheckbox).attr('checked', false);
          window.location = '?' + $.sendCheckboxCheckedValues();
        }
        else {
          $('#' + idcheckbox).attr('checked', true);
          console.log($.sendCheckboxCheckedValues());
          window.location = $.sendCheckboxCheckedValues();
        }
      });
      ///her we goo
      if (Drupal.settings.mica_client_study.queries) {
        console.log(Drupal.settings.mica_client_study.queries);

      }


    }
  }
})(jQuery);