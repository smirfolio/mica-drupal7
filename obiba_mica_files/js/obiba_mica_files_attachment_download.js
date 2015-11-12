/**
 * @file
 * JsScript to deal with  attachment files
 */

(function ($) {
  Drupal.behaviors.attachement_download = {
    attach: function (context, settings) {
      $('a#download-attachment').each(function () {
        //console.log($(this));

        $(this).on('click', function (event) {
          // create a form for the file upload
          var entityType = $(this).attr('entity');
          var idEntity = $(this).attr('id_entity');
          var fileName = $(this).attr('file_name');
          var filepath = $(this).attr('file_path');
          var form = $("<form action='" + Drupal.settings.basePath + 'download/' + idEntity + '/' + entityType + '/' + fileName + "' method='post'><input name='file_path' type='hidden' value='" + filepath + "'>");
          $(this).after(form);
          console.log(form);
          form.submit().remove();
          return false;
        });

      });

    }
  }
})(jQuery);
