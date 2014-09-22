(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {
      /*******************/
      var text_studies = Drupal.t('Studies');
      var text_study = Drupal.t('Study');
      $("#edit-studies-query").on("keyup", function () {
        $.ajax({
          url: 'refresh_list_studies/' + $(this).val() + '/' + $("#edit-studies-sort").val() + '/' + $("#edit-studies-sort-order").val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.list_studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refrech-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });

        $("#edit-studies-query").on("blur", function () {
            var data_url= $('#mica-client-study-create-form').serialize();
            window.location = '?' +data_url;
        });


      $("#edit-studies-sort-order").on("change", function () {
        var data_url = $('#mica-client-study-create-form').serialize();
        window.location = '?' + data_url;
      });

      $("#edit-studies-sort").on("change", function () {
        var data_url = $('#mica-client-study-create-form').serialize();
        window.location = '?' + data_url;
      });
      /*******************/
    }
  }
})(jQuery);
