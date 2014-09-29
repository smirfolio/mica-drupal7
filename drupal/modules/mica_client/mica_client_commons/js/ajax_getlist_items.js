(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {
      /*******************/
      var captions = Drupal.settings.context.captions;
      var text_studies = Drupal.t(captions.plural);
      var text_study = Drupal.t(captions.default);
      $("#edit-search-query").on("keyup", function () {
        $.ajax({
          url: Drupal.settings.context.url + '/' + $(this).val() + '/' + $("#edit-search-sort").val() + '/' + $("#edit-search-sort-order").val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.list_studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refrech-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });

      $("#edit-search-query").on("blur", function () {
          var data_url= $('#mica-client-search-form').serialize();
          window.location = '?' +data_url;
      });

      $("#edit-search-sort-order").on("change", function () {
        var data_url = $('#mica-client-search-form').serialize();
        window.location = '?' + data_url;
      });

      $("#edit-search-sort").on("change", function () {
        var data_url = $('#mica-client-search-form').serialize();
        window.location = '?' + data_url;
      });
      /*******************/
    }
  }
})(jQuery);
