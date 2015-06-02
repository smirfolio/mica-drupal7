(function ($) {
  Drupal.behaviors.mica_data_access_request_datatable_init = {

    attach: function (context, settings) {
      var ACTIONS = { VIEW: 'glyphicon-eye-open',
        DELETE: 'glyphicon-trash',
        EDIT: 'glyphicon-edit'
      }, HREF_ACTIONS = {VIEW: '/data-access-request/{}',
        DELETE: '/data-access-request/{}',
        EDIT: '/data-access-request/{}'
      };

      var hrefBuilder = function(action, id) {
        return HREF_ACTIONS[action].replace('{}', id);
      };

      if (context === document) {
        var divRequests = $('#table-requests'),
          colDefs = [
          {
            targets: -1,
            render: function (data, type, row) {
              return data.map(function (action) {
                if (action in ACTIONS) {
                  return '<a href="' + hrefBuilder(action, row[row.length - 1]) + '" data-action="' + action + '"><i class="glyphicon ' + ACTIONS[action] + '"></i></a>';
                }

                return '';
              }).join(' ');
            }
          }];

        divRequests.dataTable(
          {
            "data": settings.table_data,
            "columns": settings.table_headers,
            "columnDefs": colDefs,
            "iDisplayLength": 25,
            "responsive": true,
            "scrollX": true,
            "sDom": '<"table-var-wrapper" <<"md-top-margin pull-left" i><"pull-right" f>><"clear-fix" ><"no-float-tab" rt><"clear-fix" ><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
            "language": {
              "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
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
