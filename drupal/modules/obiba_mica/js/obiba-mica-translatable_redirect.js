/**
 * @file
 * JsScript ajax helper for Search widget : in dataset, network, study list
 */

(function ($) {
  Drupal.behaviors.obiba_translatable_path = {
    attach: function (context, settings) {
      /*******************/
      if (Drupal.settings.obiba_mica) {
        var disabledPathTranslation = window.location.pathname.replace(Drupal.settings.basePath, '').replace(Drupal.settings.obiba_mica.currentLang, '');
//check if current path must be not translated
        if ($.inArray(disabledPathTranslation, Drupal.settings.obiba_mica.paths) > -1) {
// redirect to default page
          window.location.href = window.location.href.replace(Drupal.settings.obiba_mica.currentLang, '');
        }
      }

    }
  }
})(jQuery);
