(function ($) {
  Drupal.behaviors.micaDataset_variable_harmo_algo_datable_init = {

    attach: function (context, settings) {
      /**************************/

      $('#harmo-algo').on('click', function () {
        console.log('hiiiihaaa');
        var $btn = $(this).button('loading');
        $('.collapse').collapse();
        // business logic...
        //$btn.button('reset')
      });

      /***************************/
    }
  }
}(jQuery));

