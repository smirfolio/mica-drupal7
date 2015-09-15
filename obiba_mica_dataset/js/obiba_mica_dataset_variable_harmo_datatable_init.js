/**
 * @file
 * JavaScript ajax helper for Algorithm variables retrieving
 */

(function ($) {
  Drupal.behaviors.micaDataset_variable_harmo_datatable_init = {

    invalidate: function (context, parent) {
      if (context === document && $('#table-variable-harmonization').parents(parent.selector).length > 0) {
        var table = $('#table-variable-harmonization').dataTable();
        if (table) {
          table.fnAdjustColumnSizing();
        }
      }
    },

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
            "bFilter": false,
            "bInfo": false,
            "scrollCollapse": true,
            "order": [[1, "asc"]],
            "sDom": '<"table-var-wrapper" <<"md-top-margin pull-left" i><"pull-right" f>><"clear-fix" ><"no-float-tab" rt><"clear-fix" ><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
            "language": {
              "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
            },
            "fnInitComplete": function () {
              $('span', this.fnGetNodes()).tooltip({
                "delay": 0,
                "track": true,
                "fade": 250
              });
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
