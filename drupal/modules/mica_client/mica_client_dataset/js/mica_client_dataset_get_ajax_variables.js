(function ($) {

  Drupal.behaviors.mica_datasets_variables_ajax_table = {
    attach: function (context, settings) {
      GetAjaxTable();
      /***********************************/
      function GetAjaxTable() {
        var message_div_stat_tab = $('#txtblnk');
        var param_stat_tab = $('#param-statistics');

        var message_div_stat_chart = $('#txtblnkChart');
        var param_stat_chart = $('#param-statistics-chart');

        var var_id = param_stat_tab.attr('var-id');

        $.ajax({
          'url': 'variable-detail-statistics/' + var_id,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            console.log(data);
            var data_decoded = jQuery.parseJSON(data);

            console.log(data_decoded);
            if (!data_decoded) {
              console.log('error');
              param_stat_tab.empty();
              param_stat_chart.empty();
              var $errorMessage = Drupal.t('Error!');
              console.log($errorMessage);
              $('<p>' + $errorMessage + '</p>').appendTo(param_stat_tab);
              $('<p>' + $errorMessage + '</p>').appendTo(param_stat_chart);
            }
            else {
              message_div_stat_tab.empty();
              param_stat_tab.css({'padding-top': '0'});
              $(data_decoded.table).appendTo(param_stat_tab);
              console.log(data_decoded.chart);
              message_div_stat_chart.empty();
              param_stat_chart.css({'padding-top': '0'});
              $(data_decoded.chart).appendTo(param_stat_chart);

              $('.charts-highchart').once('charts-highchart', function () {
                if ($(this).attr('data-chart')) {
                  var config = $.parseJSON($(this).attr('data-chart'));
                  $(this).highcharts(config);
                }
              });

            }
          },
          beforeSend: function () {
            blinkeffect('#txtblnk');
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