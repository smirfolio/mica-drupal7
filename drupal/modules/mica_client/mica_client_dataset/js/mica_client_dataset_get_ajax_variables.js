(function ($) {

  Drupal.behaviors.mica_datasets_variables_ajax_table = {
    attach: function (context, settings) {
      GetAjaxTable();
      /***********************************/
      function GetAjaxTable() {
        var message_div = $('#txtblnk');
        var param = $('#param-statistics');
        var var_id = param.attr('var-id');

        $.ajax({
          'url': 'variable-detail-statistics/' + var_id,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            message_div.empty();

            param.css({'padding-top': '0'});

            $(data).appendTo(param);
            console.log(data);
          },
          beforeSend: function () {
            blinkeffect('#txtblnk');
          },
          'error': function (data) {
            param.empty();
            var $errorMessage = Drupal.t('Error!');
            console.log($errorMessage);
            $().appendTo(param);
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

      /******************************************/

    }
  };

}(jQuery));