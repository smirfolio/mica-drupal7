(function ($) {

  Drupal.behaviors.mica_client_variable = {
    attach: function (context, settings) {
      GetAjaxTable();
      /***********************************/
      function GetAjaxTable() {
        var message_div_stat_tab = $('#toempty');
        var param_stat_tab = $('#param-statistics');

        var message_div_stat_chart = $('#toemptychart');
        var param_stat_chart = $('#param-statistics-chart');

        var var_id = param_stat_tab.attr('var-id');

        $.ajax({
          'url': 'variable-detail-statistics/' + var_id,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            var data_decoded = jQuery.parseJSON(data);
            if (typeof data_decoded == 'object') {
              console.log(data_decoded);

            }
            if (!data_decoded) {
              param_stat_tab.empty();
              param_stat_chart.empty();
              var $errorMessage = Drupal.t('Error!');
              console.log($errorMessage);
              $('<p>' + $errorMessage + '</p>').appendTo(param_stat_tab);
              $('<p>' + $errorMessage + '</p>').appendTo(param_stat_chart);
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

                if (Drupal.settings.mica_client_variable.library == 'google') {
                  Drupal.behaviors.chartsGoogle.attach();
                }
                if (Drupal.settings.mica_client_variable.library == 'highcharts') {
                  Drupal.behaviors.chartsHighcharts.attach();
                }
              }
              else {
                message_div_stat_chart.empty();
              }


            }
          },
          beforeSend: function () {
            blinkeffect('#txtblnk');
            blinkeffect('#txtblnkChart');
          },
          'error': function (data) {

            param_stat_tab.empty();
            param_stat_chart.empty();
            var $errorMessage = Drupal.t('Error!');
            console.log($errorMessage);
            $($errorMessage).appendTo(param_stat_tab);
            $($errorMessage).appendTo(param_stat_chart);
          }
        });
      }

      function blinkeffect(selector) {
        $(selector).fadeOut('slow', function () {
          $(this).fadeIn('slow', function () {
            blinkeffect(this);
          });
        });
      }
    }
  };

}(jQuery));