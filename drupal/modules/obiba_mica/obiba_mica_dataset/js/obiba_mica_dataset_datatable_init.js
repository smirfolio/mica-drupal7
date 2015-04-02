/**
 * @file
 * JsScript to initialise dataTables widgets
 */

(function ($) {
  Drupal.behaviors.micaDataset_Datatable_init = {

    invalidate: function (context, parent) {
      if (context === document && $('#table-variables').parents(parent.selector).length > 0) {
        var table = $('#table-variables').dataTable();
        if (table) {
          table.fnAdjustColumnSizing();
        }
      }
    },

    attach: function (context, settings) {
      createDataTable();
    }
  }

  function createDataTable() {
    var divDataTableVar = $('#variables-table');
    var idDataset = divDataTableVar.attr('id-dataset');
    var typeDataset = divDataTableVar.attr('type-dataset');
    var headerTable = null;

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

    function hideSortIcon() {
      var thHeaderSort = $(".DTFC_LeftBodyLiner .sorting");
      var thHeaderSortAsc = $(".DTFC_LeftBodyLiner .sorting_asc");
      var thHeaderSortDesc = $(".DTFC_LeftBodyLiner .sorting_desc");
      if (thHeaderSort.length) {
        thHeaderSort.removeClass("sorting");
      }
      if (thHeaderSortAsc.length) {
        thHeaderSortAsc.removeClass("sorting_asc");
      }
      if (thHeaderSortDesc.length) {
        thHeaderSortDesc.removeClass("sorting_desc");
      }
    }

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
        "responsive": true,
        "scrollX": true,
        "scrollCollapse": true,
        "processing": true,
        "sDom": '<"table-var-wrapper" <"md-top-margin" i>rt<"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
        "bServerSide": true,
        "iDisplayLength": 25,
        "sAjaxSource": Drupal.settings.basePath + 'mica/variables-tab-data/' + typeDataset + '/' + idDataset,
        "aoColumns": headerTable,
        "searching": true,
        "ordering": true,
        "fnDrawCallback": function (oSettings) {
          updateTooltip();
        },
        "fnInitComplete": function () {
          updateTooltip();
        },
        "language": {
          "url": Drupal.settings.basePath + 'mica/datatable-international'
        }
      });

      // NOTE: this breaks the paging and table state, keep an eye for an update
      new $.fn.dataTable.FixedColumns(dataTable, {
        leftColumns: 2
      });

      divTableVariable.on('init.dt', function () {
        hideSortIcon();
      });

      function updateTooltip() {
        $('span', dataTable.fnGetNodes()).tooltip( {
          "delay": 0,
          "track": true,
          "fade": 250
        } );
      }
    }
  }

}(jQuery));

