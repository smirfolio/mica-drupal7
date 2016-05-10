(function ($) {
  Drupal.behaviors.obiba_mica_study_detail = {
    attach: function (context, settings) {
      if (context === document) {
        var qCoverage, qNetworks, qDatasets;
        var optionsStudyContent = settings.optionsStudyContent;


        if (optionsStudyContent) {

          if (optionsStudyContent.showCoverage) {
            qCoverage = $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/study/' + settings.study_url + '/coverage')
              .done(function (data) {
                if (! data) {
                  $('#coverage').remove();
                  return;
                }

                $('#coverage').html(data).show();
                Drupal.attachBehaviors($('.main-container')[0], settings);
              })
              .fail(function () {
                $('#coverage').remove();
              });
          }
          else {
            $('#coverage').remove();
          }
          if (optionsStudyContent.showNetwork) {
            qNetworks = $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/study/' + settings.study_url + '/networks')
              .done(function (data) {
                if (! data) {
                  $('#networks').remove();
                  return;
                }

                $('#networks').html(data).show();
              })
              .fail(function () {
                $('#networks').remove();
              });
          }
          else {
            $('#networks').remove();
          }
          if (optionsStudyContent.showDatasets) {
            qDatasets = $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/study/' + settings.study_url + '/datasets')
              .done(function (data) {
                if (! data) {
                  $('#datasets').remove();
                  return;
                }
                $('#datasets').html(data).show();
                var datasets = $('#datasetsDisplay').data();
                $('.dce-actions').each(function () {
                  if (datasets && ($(this).data().dceName in datasets.dceVariables)) {
                    $(this).show();
                  }
                });
              })
              .fail(function () {
                $('#datasets').remove();
              });
          }
          else {
            $('#datasets').remove();
          }
        } else {
          $('#coverage').remove();
          $('#networks').remove();
          $('#datasets').remove();
        }

        $.when(qCoverage, qDatasets).then(function () {
          var datasets = $('#datasetsDisplay').data();

          if (datasets && datasets.totalVariables > 0) {
            $('#study-actions').removeClass('hidden');
          }

          if ($('#coverage').is(':visible')) {
            $('.show-coverage').removeClass('hidden');
          }
        });

        var anchor = location.hash.substr(1)? location.hash.substr(1).replace(/^\//, '') :null;
        if(anchor) {
          $('#tab-pane a[href="#' + anchor + '"]').tab('show');
          $('html, body').animate({
            scrollTop: $('#'+ anchor).offset().top
          }, 'slow');
        }
      }
    }
  }
}(jQuery));