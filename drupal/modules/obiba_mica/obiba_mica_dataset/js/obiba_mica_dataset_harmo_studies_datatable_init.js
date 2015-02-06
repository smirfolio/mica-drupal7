(function ($) {
  Drupal.behaviors.micaDataset_studies_datatable_init = {

    attach: function (context, settings) {

      var divStudies = $('#table-studies');
      divStudies.dataTable(
        {
          "data": settings.table_data,
          "columns": settings.table_headers,
          "iDisplayLength": 25,
          "responsive": true,
          "scrollX": true,
          "scrollCollapse": true,
          "sDom": '<"table-var-wrapper" <"md-top-margin pull-left" i><"pull-right" f>rt<"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
          "language": {
            "url": Drupal.settings.basePath + 'mica/datatable-international'
          },
          "fnDrawCallback": function(oSettings) {
            if (oSettings._iDisplayLength > oSettings.aoData.length) {
              $('.dataTables_paginate').hide();
              $('.dataTables_length').hide();
            } else {
              $('.dataTables_paginate').show();
              $('.dataTables_length').show();
            }
          }
        }
      );
    }
  }

}(jQuery));
