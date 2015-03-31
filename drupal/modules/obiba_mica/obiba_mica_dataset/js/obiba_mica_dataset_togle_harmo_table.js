/**
 * @file
 * JavaScript ajax helper for Algorithm variables retrieving
 */

(function ($) {
  Drupal.behaviors.obiba_mica_dataset_togle_harmo_table = {

    attach: function (context, settings) {

      if (context === document) {
        var TitleButtonVar = $('#harmo-table-btn').attr('title-button-var');
        $('#harmo-table-btn').on('click', function () {
          $(this).text(Drupal.t('Hide') + ' ' + TitleButtonVar);
          var $btn = $(this).button('loading');
          $('.collapse').collapse();

          // WORKAROUND: When the harmonization table is a child, the DataTable is not drawn properly
          Drupal.behaviors.micaDataset_Datatable_init.invalidate(context, $('#harmo-table'));

          $("#harmo-table-btn").unbind("click");
          $(this).removeAttr('id');
          $(this).attr('id', 'harmo-table-toggle');

          $btn.button('reset')
        });
        $('.collapse').on('hidden.bs.collapse', function () {

          $('#harmo-table-toggle').text(Drupal.t('Show') + ' ' + TitleButtonVar);
        });
        $('.collapse').on('shown.bs.collapse', function () {

          $('#harmo-table-toggle').text(Drupal.t('Hide') + ' ' + TitleButtonVar);
        });
      }
    }
  }
}(jQuery));

