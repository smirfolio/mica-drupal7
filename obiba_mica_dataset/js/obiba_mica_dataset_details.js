/**
 * @file
 * JsScript to initialise dataTables widgets
 */

(function ($) {
  Drupal.behaviors.micaDataset_Datatable_detail = {
    attach: function (context, settings) {

      $('.dce-actions').each(function () {
        $(this).show();
      });


    }
  }
}(jQuery));