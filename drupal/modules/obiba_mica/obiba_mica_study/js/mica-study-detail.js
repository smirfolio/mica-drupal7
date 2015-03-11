(function ($) {
  Drupal.behaviors.obiba_mica_study_detail = {
    attach: function (context, settings) {
      if(context === document) {
        var qCoverage = $.ajax(settings.study_url + '/coverage')
          .done(function (data) {
            if (!data) {
              $('#coverage').remove();
              return;
            }

            $('#coverage').html(data).show();
            Drupal.attachBehaviors($('.main-container')[0], settings);
          })
          .fail(function () {
            $('#coverage').remove();
          });

        var qNetworks = $.ajax(settings.study_url + '/networks')
          .done(function(data) {
            if (!data) {
              $('#networks').remove();
              return;
            }

            $('#networks').html(data).show();
          })
          .fail(function () {
            $('#networks').remove();
          });

        var qDatasets = $.ajax(settings.study_url + '/datasets')
          .done(function(data) {
            if (!data) {
              $('#datasets').remove();
              return;
            }
            $('#datasets').html(data).show();
            var datasets = $('#datasetsDisplay').data();
            $('.dce-actions').each(function(){
              if(datasets && ($(this).data().dceName in datasets.dceVariables)) {
                $(this).show();
              }
            });
          })
          .fail(function() {
            $('#datasets').remove();
          });

        $.when(qCoverage, qDatasets).then(function() {
          var datasets = $('#datasetsDisplay').data();

          if(datasets && datasets.totalVariables > 0) {
            $('#study-actions').removeClass('hidden');
          }

          if($('#coverage').is(':visible')) {
            $('.show-coverage').removeClass('hidden');
          }
        });
      }
    }
  }
}(jQuery));