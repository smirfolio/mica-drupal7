/**
 * @file
 * JsScript to initialise dataTables widgets
 */

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
        headerTable = data["header"];
      }

      /**********************/
      if (headerTable) {
        $("#download-btn").show();
        var divTableVariable = $('#table-variables');
        divTableVariable.on('xhr.dt', function (e, settings, json) {
          if (json.iTotalRecords === 0) {
            $(".table-variables").hide();
          }
          else {
            $("#download-btn > a").on('click', function (event) {
              // create a form for the file upload
              var form = $("<form action='" + idDataset + '/download' + "' method='post'>");
              $(this).after(form);
              form.submit().remove();
              return false;
            });
          }
        });
        var dataTable = divTableVariable.dataTable({
          //  "scrollY": "100%",
          "responsive": true,
          "scrollX": true,
          "scrollCollapse": true,
          "processing": true,
          //  "sDom": '<"pull-left" i><"pull-right" f>t<"pull-left" l><"pull-right" p>',
          "sDom": '<"table-var-wrapper" <"md-top-margin" i>rt<"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
          "bServerSide": true,
          "sAjaxSource": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
          "aoColumns": headerTable,
          "searching": true,
          "ordering": true,
          "iDisplayLength": 25,
          "stateSave": true,
          "language": {
            "url": Drupal.settings.basePath + 'mica/datatable-international'
          }
//          ,
//          "fnInitComplete": function() {
//
//            divTableVariable.css("width","100%");
//          }

        });

        new $.fn.dataTable.FixedColumns(dataTable, {
          leftColumns: 2
        });
      }

      /*******************************/
    }
  }
}(jQuery));

