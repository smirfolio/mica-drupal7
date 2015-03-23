/**
 * @file
 * JavaScript ajax helper for Algorithm variables retrieving
 */

(function ($) {
  Drupal.behaviors.micaDataset_variable_harmo_algo_datable_init = {

    attach: function (context, settings) {
      /**************************/
      var TitleButtonVar = $('#harmo-algo').attr('title-button-var');
      $('#harmo-algo').on('click', function () {
        var idHarmonizationVariable = $(this).attr('var-id');


        var sectionContainer = $('div#harmo-algo');
        $(this).text(Drupal.t('Hide') + ' ' + TitleButtonVar);
        var $btn = $(this).button('loading');
        $('.collapse').collapse();
        $.ajax({
          'url': Drupal.settings.basePath + 'mica/variables-harmonization-algo/' + idHarmonizationVariable,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            try {
              var data_decoded = jQuery.parseJSON(data);
              sectionContainer.append(data_decoded['algo']);
            } catch (e) {

            }

          },
          'error': function (data) {
            console.log('Some errors....');
          }
        });
        $("#harmo-algo").unbind("click");
        $(this).removeAttr('id');
        $(this).attr('id', 'harmo-algo-toggle');

        $btn.button('reset')
      });
      $('.collapse').on('hidden.bs.collapse', function () {
        console.log('Show');
        $('#harmo-algo-toggle').text(Drupal.t('Show') + ' ' + TitleButtonVar);
      });
      $('.collapse').on('shown.bs.collapse', function () {
        console.log('Hide');
        $('#harmo-algo-toggle').text(Drupal.t('Hide') + ' ' + TitleButtonVar);
      });
      /***************************/
    }
  }
}(jQuery));

