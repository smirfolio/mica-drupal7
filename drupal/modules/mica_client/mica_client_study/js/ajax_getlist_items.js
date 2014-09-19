(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {
      /*******************/
      var text_studies = Drupal.t('Studies');
      var text_study = Drupal.t('Study');
      $("#edit-studies-query").on("keypress", function () {
        $.ajax({
          url: 'refresh_list_studies/' + $(this).val() + '/' + $("#edit-studies-sort").val() + '/' + $("#edit-studies-sort-order").val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refresh-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });

      $("#edit-studies-query").on("blur", function () {
        $.ajax({
          url: 'refresh_list_studies/' + $(this).val() + '/' + $("#edit-studies-sort").val() + '/' + $("#edit-studies-sort-order").val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refresh-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });

      $("#edit-studies-sort-order").on("change", function () {

        $.ajax({
          url: 'refresh_list_studies/' + $("#edit-studies-query").val() + '/' + $("#edit-studies-sort").val() + '/' + $(this).val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refresh-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });

      $("#edit-studies-sort").on("change", function () {
        $.ajax({
          url: 'refresh_list_studies/' + $("#edit-studies-query").val() + '/' + $(this).val() + '/' + $("#edit-studies-sort-order").val(),
          success: function (data) {
            if (data) {
              $('#refresh-list').empty().append(data.studies);
              var testStudy = (data.total > 1) ? text_studies : text_study;
              $('#refresh-count').empty().append(data.total + ' ' + testStudy);
            }
          }
        });
      });


      /*******************/
    }
  }
})(jQuery);
