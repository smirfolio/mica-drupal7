(function ($) {

  Drupal.behaviors.download_harmonization_table = {
    attach: function (context, settings) {

      $("#download-harmo-table").on('click', function (event) {
        // create a form for the file upload
        var form = $("<form action='"+Drupal.settings.resource_url+"' method='post'>");
        $(this).after(form);
        form.submit().remove();
        return false;
      });

    }
  }
}(jQuery));

