(function ($) {
  Drupal.behaviors.micaNetwork_studies_datatable_init = {

    attach: function (context, settings) {

      if (context === document) {
        var divStudies = $('#table-variable-harmonization');
        divStudies.dataTable(
          {
            "data": settings.table_data,
            "columns": settings.table_headers,
            "iDisplayLength": 25,
            "responsive": true,
            "scrollX": true,
            "scrollCollapse": true,
            "order": [[ 1, "asc" ]],
            "sDom": '<"table-var-wrapper" <<"md-top-margin pull-left" i><"pull-right" f>><"clear-fix" ><"no-float-tab" rt><"clear-fix" ><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
            "language": {
              "url": Drupal.settings.basePath + 'mica/datatable-international'
            },
            "fnInitComplete": function () {
              $('span', this.fnGetNodes() ).tooltip( {
                "delay": 0,
                "track": true,
                "fade": 250
              } );
            },
            "fnDrawCallback": function (oSettings) {
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
  }

}(jQuery));
