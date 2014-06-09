(function ($) {
    Drupal.behaviors.datatables_add_head = {
        attach: function (context, settings) {
            if (Drupal.settings.mica_study.study_json){
            }
    new $.MicaTimeline(new $.StudyDtoParser()).create("#vis", JSON.parse(Drupal.settings.mica_study.study_json)).addLegend();
        }
    }
})(jQuery);
