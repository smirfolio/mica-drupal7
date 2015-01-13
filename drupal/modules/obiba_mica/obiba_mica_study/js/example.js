/**
 * @file
 * code to initialise Timeline
 */

(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {
      if (Drupal.settings.obiba_mica_study.study_json) {
        new $.MicaTimeline(new $.StudyDtoParser()).create("#vis", JSON.parse(Drupal.settings.obiba_mica_study.study_json)).addLegend();
      }
    }
  }
})(jQuery);
