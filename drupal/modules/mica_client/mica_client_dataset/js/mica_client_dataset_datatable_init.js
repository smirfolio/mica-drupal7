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
        $(".download-table").show();
        var dataTable = $('#table-variables').on('xhr.dt', function (e, settings, json) {
          if (json.iTotalRecords === 0) {
            $(".table-variables").hide();
          }
          else {
            $("#download-harmo-table").on('click', function (event) {
              // create a form for the file upload
              var form = $("<form action='" + idDataset + '/download' + "' method='post'>");
              $(this).after(form);
              form.submit().remove();
              return false;
            });
          }
        })
          .dataTable({
            "processing": true,
            //  "sDom": '<"pull-left" i><"pull-right" f>t<"pull-left" l><"pull-right" p>',
            "sDom": '<"pull-left" i>t<"pull-left" l><"pull-right" p>',
            "bServerSide": true,
            "sAjaxSource": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
            "aoColumns": headerTable,
            "searching": true,
            "ordering": false,
            "language": {
              "url": Drupal.settings.basePath + 'mica/datatable-international'
            }

          });

        //console.log(tableData.sAjaxSource);
      }
      /*******************************/
    }
  }
}(jQuery));

