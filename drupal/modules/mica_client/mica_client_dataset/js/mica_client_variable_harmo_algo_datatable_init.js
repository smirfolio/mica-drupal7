(function ($) {
  Drupal.behaviors.micaDataset_variable_harmo_algo_datable_init = {

    attach: function (context, settings) {
      /**************************/

      $('#harmo-algo').on('click', function () {
        var idHarmonizationVariable = $(this).attr('var-id');
        var sectionContainer = $('section#harmo-algo');

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
        $(this).removeAttr('id');
        $btn.button('reset')
      });

      /***************************/
    }
  }
}(jQuery));

