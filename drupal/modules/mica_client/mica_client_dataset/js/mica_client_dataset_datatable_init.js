(function ($) {
  Drupal.behaviors.micaDataset_Datatable_init = {

    attach: function (context, settings) {
      /***********AjaxTable*******************/
      var divDataTableVar = $('#variables-table');
      var idDataset = divDataTableVar.attr('id-dataset');
      var typeDataset = divDataTableVar.attr('type-dataset');
      var headerTable = null;
      console.log(idDataset);
      console.log(typeDataset);
      /*****************/

      $.ajax({
        'async': false,
        'url': Drupal.settings.basePath + 'mica/variables-tab-header/' + typeDataset,
        'type': 'GET',
        'success': function (data) {
          setHeaderTab(data);
        },
        "dataType": "json",
        'error': function (data) {

        }
      });

      function setHeaderTab(data) {
        headerTable = data;
      }


      /**********************/
      console.log(headerTable["header"]);

      var table_data = $('#table-variables').dataTable({
        "processing": true,
        "bServerSide": true,
        "sAjaxSource": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
        "aoColumns": headerTable["header"],
        "searching": false,
        "ordering": false
      });

      /*******************************/
    }


  }
}(jQuery));

