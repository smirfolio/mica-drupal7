/*
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

(function ($) {
  Drupal.behaviors.micaNetwork_networks_datatable_init = {

    attach: function (context, settings) {
      if (context === document) {
        $('#table-networks').dataTable(
          {
            "bAutoWidth": false,
            "responsive": true,
            "data": settings.table_dataset_networks_data || [],
            "columns": settings.table_dataset_networks_headers || [],
            "iDisplayLength": 25,
            "scrollCollapse": true,
            "sDom": '<"table-var-wrapper" <<"md-top-margin pull-left" i><"pull-right" f>><"clear-fix" ><"no-float-tab" r<"scroll-content-tab" t>><"clear-fix" ><"pull-left md-top-margin" l><"pull-right md-top-margin" p>>',
            "language": {
              "url": Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/datatable-international'
            },
            "fnDrawCallback": function (oSettings) {
              if (oSettings._iDisplayLength > oSettings.aoData.length) {
                $('#networks-table .dataTables_paginate').hide();
                $('#networks-table .dataTables_length').hide();
              } else {
                $('#networks-table .dataTables_paginate').show();
                $('#networks-table .dataTables_length').show();
              }
            }
          }
        );
      }
    }
  }

}(jQuery));
