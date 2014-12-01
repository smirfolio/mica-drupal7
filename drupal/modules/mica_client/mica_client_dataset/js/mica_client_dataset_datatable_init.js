(function ($) {
  Drupal.behaviors.micaDataset_Datatable_init = {

    attach: function (context, settings) {
      /***********AjaxTable*******************/
      var divDataTableVar = $('#variables-table');
      var idDataset = divDataTableVar.attr('id-dataset');
      var typeDataset = divDataTableVar.attr('type-dataset');
      var headerTable = null;
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
      if (headerTable) {
        $(".download-table").show();
        $('#table-variables').on('xhr.dt', function (e, settings, json) {
          if (json.iTotalRecords === 0) {
            $(".table-variables").hide();
          }
          // Note no return - manipulate the data directly in the JSON object.
        })
          .dataTable({
            "processing": true,
            "sDom": '<"pull-left" l><"pull-right" p>tp',
            "bServerSide": true,
            "sAjaxSource": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
            "aoColumns": headerTable["header"],
            "searching": false,
            "ordering": false
          });

        //console.log(tableData.sAjaxSource);
      }
      /*******************************/
    }
  }
}(jQuery));

