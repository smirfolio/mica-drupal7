(function ($) {
  Drupal.behaviors.mica_data_access_request_datatable_init = {

    attach: function (context, settings) {
      var ACTIONS = { VIEW: 'glyphicon-eye-open',
        DELETE: 'glyphicon-trash',
        EDIT: 'glyphicon-edit'
      }, HREF_ACTIONS = {VIEW: 'data-access-request#/view/{}',
        DELETE: 'data-access-request/delete/{}',
        EDIT: 'data-access-request#/edit/{}'
      };

      var hrefBuilder = function (action, id) {
        return HREF_ACTIONS[action].replace('{}', id);
      };

      if (context === document) {
        var divRequests = $('#table-requests'),
          colDefs = [
            {
              targets: -1,
              render: function (data, type, row) {
                return '<ul class="list-inline no-margin">' + data.map(function (action) {
                  if (action in ACTIONS) {
                    if (action === 'DELETE') {
                      return '<li><a  data-target="#delete-modal" id="' + action + '" href="' + hrefBuilder(action, row[row.length - 1]) + '" data-action="' + action + '"data-access-title="' + row[1] + '" data-access-status="' + row[3] + '"> <i class="glyphicon ' + ACTIONS[action] + '"></i></a></li>';
                    }
                    else {
                      return '<li><a href="' + hrefBuilder(action, row[row.length - 1]) + '" data-action="' + action + '"><i class="glyphicon ' + ACTIONS[action] + '"></i></a></li>';
                    }
                  }

                  return '';
                }).join(' ') + '</ul>';
              }
            }
          ];

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

        /* Add events */
        $("body").on("click", "#table-requests tbody #DELETE", function (e) {
          e.preventDefault();
          var modal = $('#delete-modal').modal('show');
          modal.find('#data_access_title').text($(this).attr("data-access-title"));
          modal.find('#data_access_status').text($(this).attr("data-access-status"));
          modal.find('#clickedDelete').attr('data-delete-resource', $(this).attr("href"));
          return false;
        });


        $('#clickedDelete').on("click", function () {
          $.ajax({
            'async': true,
            'url': Drupal.settings.basePath + $(this).attr('data-delete-resource'),
            'type': 'POST',
            'success': function (data) {
              $('#delete-modal').modal('toggle');
              location.reload();

            },
            'error': function (data) {
            }
          });

        });

      }
    }
  }

}(jQuery));
