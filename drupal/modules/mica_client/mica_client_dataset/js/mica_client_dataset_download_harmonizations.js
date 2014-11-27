(function ($) {
  Drupal.behaviors.download_harmonization_table = {

    attach: function (context, settings) {

      $("#download-harmo-table").on('click', function (event) {
        // create a form for the file upload
        var form = $("<form action='" + Drupal.settings.resource_url + "' method='post'>");
        $(this).after(form);
        form.submit().remove();
        return false;
      });


      /***********AjaxTable*******************/
      var divDataTableVar = $('#variables-table');
      var idDataset = divDataTableVar.attr('id-dataset');
      var typeDataset = divDataTableVar.attr('type-dataset');
      var loadedHead = null;
      var loadedData = null;

      console.log(idDataset);
      console.log(typeDataset);

      getheaderTable();

      cloneAppenededTable();

      function getheaderTable() {
        $.ajax({
          'async': false,
          'url': Drupal.settings.basePath + 'mica/variables-tab/' + typeDataset + '/' + idDataset,
          'type': 'GET',
          'dataType': 'html',
          'data': '',
          'success': function (data) {
            var response = $.parseJSON(data);
            var VariablesList = response['html_data_variable'];
            console.log(JSON.stringify(VariablesList));
            appendHeaderTable(response['html_header']);
            dataTableConstruct(JSON.stringify(VariablesList));
          },
          'error': function (data) {
          }
        });

      }

      function appendHeaderTable(htmlHeader) {
        //console.log($.parseJSON(data));
        loadedHead = htmlHeader;
        divDataTableVar.append(loadedHead);

      }

      function dataTableConstruct($variable_data) {
        loadedData = $variable_data;
      }

      function cloneAppenededTable() {

        if (loadedHead) {

          $('#table-variables').dataTable({
            "processing": true,
            "serverSide": true,
            "ajax": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset
          });


        }
      }

      /*******************************/
    }


  }
}(jQuery));

