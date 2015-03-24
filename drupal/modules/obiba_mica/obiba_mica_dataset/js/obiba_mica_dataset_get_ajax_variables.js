/**
 * @file
 * JavaScript ajax helper for Statistics variables retrieving
 */

(function ($) {

  Drupal.behaviors.obiba_mica_variable = {
    attach: function (context, settings) {
      if (context === document) getAjaxTable();
      /************************************/
      var alertMEssage = '<div class="alert alert-warning alert-dismissible" role="alert">' +
        '<button type="button" class="close" data-dismiss="alert"><span aria-hidden="true">&times;</span>' +
        '<span class="sr-only">Close</span></button> ' + Drupal.t('Unable to retrieve statistics...') + '</div>';


      /***********************************/
      function getAjaxTable() {
        var message_div_stat_tab = $('#toempty');
        var param_stat_tab = $('#param-statistics');

        var message_div_stat_chart = $('#toemptychart');
        var param_stat_chart = $('#param-statistics-chart');

        var var_id = param_stat_tab.attr('var-id');

        $.ajax({
          'url': Drupal.settings.basePath + 'variable-detail-statistics/' + var_id,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            try {
              var data_decoded = jQuery.parseJSON(data);
            } catch (e) {
              console.log(e.message);
            }

            if (typeof data_decoded == 'object') {
              console.log(data_decoded);
            }
            if (!data_decoded) {
              param_stat_tab.empty();
              param_stat_chart.empty();

              $(alertMEssage).appendTo(param_stat_tab);
            }
            else {
              if (data_decoded.table) {
                message_div_stat_tab.empty();
                param_stat_tab.css({'padding-top': '0'});
                $(data_decoded.table).appendTo(param_stat_tab);
              }
              if (data_decoded.chart) {
                message_div_stat_chart.empty();
                param_stat_chart.css({'padding-top': '0'});
                $(data_decoded.chart).appendTo(param_stat_chart);

                if (Drupal.settings.obiba_mica_variable.library == 'google') {
                  Drupal.behaviors.chartsGoogle.attach();
                }
                if (Drupal.settings.obiba_mica_variable.library == 'highcharts') {
                  Drupal.behaviors.chartsHighcharts.attach();
                }
              }
              else {
                message_div_stat_chart.empty();
              }

              Drupal.attachBehaviors(param_stat_tab, settings);
            }
          },
          'error': function (data) {
            param_stat_tab.empty();
            param_stat_chart.empty();
            var $errorMessage = Drupal.t('Error!');
            console.log($errorMessage);
            $($errorMessage).appendTo(param_stat_tab);
          }
        });
      }
    }
  };

}(jQuery));