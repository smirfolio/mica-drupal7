(function ($) {
  Drupal.behaviors.mica_data_access_request_datatable_init = {

    attach: function (context, settings) {
      var user = Drupal.settings.user;
      var basePath = Drupal.settings.basePath + 'mica/data-access/request';
      var ACTIONS = {
        VIEW: 'glyphicon-eye-open',
        DELETE: 'glyphicon-trash',
        EDIT: 'glyphicon-edit'
      }, HREF_ACTIONS = {
        VIEW: basePath + '#/view/{}',
        DELETE: basePath + '/delete/{}/ws',
        EDIT: basePath + '#/edit/{}'
      };

      var hrefBuilder = function (action, id) {
        return HREF_ACTIONS[action].replace('{}', id);
      };

      if (context === document) {
        var divRequests = $('#table-requests'),
          colDefs = [
            {
              targets: 0,
              "visible": false,
              "searchable": false
            },
            {
              targets: -1,
              render: function (data, type, row) {
                return '<ul class="list-inline no-margin">' + data.map(function (action) {
                    if (action in ACTIONS) {
                      if (action === 'DELETE') {
                        var titleInMOdal = row[3] ? row[3] : row[row.length - 1];

                        return '<li><a  title="' + Drupal.t(action) + '"' +
                          'data-target="#delete-modal" id="' + action +
                          '" href="' + hrefBuilder(action, row[row.length - 1]) +
                          '" data-action="' + action +
                          '"data-access-applicant="' + row[0] +
                          '" data-access-title="' + titleInMOdal + '">' +
                          ' <i class="glyphicon ' + ACTIONS[action] + '"></i></a></li>';
                      }
                      else {
                        return '<li><a title="' + Drupal.t(action) + '" href="' + hrefBuilder(action, row[row.length - 1]) + '" data-action="' + action + '"><i class="glyphicon ' + ACTIONS[action] + '"></i></a></li>';
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
            "order": [[4, "desc"]],
            "responsive": true,
            "sDom": '<"table-var-wrapper" <<"md-top-margin pull-left" i><"pull-right" f>><"clear-fix" ><"no-float-tab" rt><"clear-fix" ><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
            "language": {
              "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
            },
            "fnInitComplete": function () {
              $('a', this.fnGetNodes()).tooltip({
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

        /* Add events on delete request*/
        $("body").on("click", "#table-requests tbody #DELETE", function (e) {
          e.preventDefault();
          var modal = $('#delete-modal').modal('show');
          modal.find('#data-access-title').text($(this).attr("data-access-title"));
          modal.find('#data-access-applicant').text($(this).attr("data-access-applicant"));
          modal.find('#clickedDelete').attr('data-delete-resource', $(this).attr("href"));
          return false;
        });
        /* Add events on view applicant profile */
        $("body").on("click", "#table-requests tbody #applicantProfile", function (e) {
          e.preventDefault();
          $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix +
            'mica/data-access/user/' + $(this).attr("data-id-applicant") + '/ws')
            .done(function (data) {
              modalProfile(this).find('#user-attributes').html(data.profile_html);
              return false;
            }.bind(this))
            .fail(function () {
              modalProfile(this);
              return false;
            }.bind(this));
        });

        function modalProfile(localProfile) {
          var modal = $('#UserDetailModal').modal('show');
          modal.find('#data-name-applicant').text($(localProfile).attr("data-name-applicant"));
          modal.find('span#data-email-applicant').text($(localProfile).attr("data-email-applicant"));
          modal.find('a#data-email-applicant').attr("href", 'mailto:' + $(localProfile).attr("data-email-applicant"));
          return modal;
        }

        $('#clickedDelete').on("click", function () {
          $.ajax({
            'async': true,
            'url': $(this).attr('data-delete-resource'),
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
