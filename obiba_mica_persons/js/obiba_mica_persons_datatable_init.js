/**
 * @file
 * JsScript dataTable initialization of associated persons
 */

(function ($) {
  Drupal.behaviors.micaPersons_Datatable_init = {
    attach: function (context, settings) {
      if (context === document) {
        $('#associated-people').on('show.bs.modal', function (event) {
          createDataTable(Drupal.settings.table_header, Drupal.settings.studies_id);
        });
      }

      $("button#download-csv-person").on('click', function (event) {
        // create a form for the file upload
        var form = $("<form action='" + Drupal.settings.basePath + Drupal.settings.pathPrefix + Drupal.settings.resourcePathPersons + Drupal.settings.studies_id + '/download/ws' + "' method='post'>");
        $(this).after(form);
        form.submit().remove();
        return false;
      });
    }
  };

  function createDataTable(headerTable, studies_id) {
    var divTablePersons = $('#person-table');
    if ($.fn.dataTable.isDataTable('#person-table')) {
      divTablePersons.dataTable();
    }
    else {
      divTablePersons.dataTable({
        "responsive": true,
        "sDom": '<"table-var-wrapper"rftp>',
        "bServerSide": false,
        "iDisplayLength": 10,
        "sAjaxSource": Drupal.settings.basePath + Drupal.settings.pathPrefix + Drupal.settings.resourcePathPersons + studies_id + '/ws',
        "aoColumns": headerTable,
        "bSearchable": false,
        "searching": true,
        "paging": true,
        "columnDefs": [
          {
            targets: 1,
            render: function (data, type, row) {
              return row.email ? row.email : '';
            }
          },
          {
            targets: 0,
            render: function (data, type, row) {
              var title = row.title ? row.title : '';
              return title + ' ' + row.firstName + ' ' + row.lastName;
            }
          },
          {
            targets: - 1,
            render: function (data, type, row) {
              var studies = '';
              var acronymCurrentLang;
              $.each(row.studyMemberships, function (study, studyObj) {
                $.each(studyObj.parentAcronym, function (index, acronym) {
                  if (acronym.lang == Drupal.settings.current_lang) {
                    acronymCurrentLang = acronym.value;
                    return false
                  }
                });
                studies += (studies != '' ? ', ' : '') + '<a href="' + Drupal.settings.basePath + 'mica/study/' + studyObj.parentId + '">' + acronymCurrentLang + '</a> (' + studyObj.role + ')';
              });
              return studies;
            }
          }

        ],
        "ordering": false,
        "language": {
          "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
        }
      });
    }
  }
}(jQuery));
