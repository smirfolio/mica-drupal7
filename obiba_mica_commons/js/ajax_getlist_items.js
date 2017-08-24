/*
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * JsScript ajax helper for Search widget : in dataset, network, study list
 */

var datatables_add_head_TimeoutId = null;

(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {

      /*******************/
      if (Drupal.settings.context) {
        $("#edit-search-query").on("keyup", function (e) {
          var that = this;
          function doSearch(){
            var url = Drupal.settings.basePath + 'mica/' + Drupal.settings.context.url + '/' + $(that).val() + '/' +
                $("#edit-search-sort").val() + '/' + $("#edit-search-sort-order").val() + '/0';

            if (Drupal.settings.document_type) {
              url += '?document_type=' + Drupal.settings.document_type;
            }

            $.ajax({

              url: url,
              success: function (data) {
                if (data) {
                  $('#refresh-list').empty().append(data.list);
                  $('#refresh-count').empty().append(data.total === null ? 0 : data.total);
                }
              }
            });
          }

          if (datatables_add_head_TimeoutId) {
            clearTimeout(datatables_add_head_TimeoutId);
          }
          if (e.keyCode == 13) {
            e.preventDefault();
            var data_url = $('#obiba-mica-search-form').serialize();
            window.location = window.location.origin + Drupal.settings.context.currentCleanPath + data_url;
          }
          datatables_add_head_TimeoutId = setTimeout(doSearch, 250);
        });
      }

      $("#edit-search-query").on("blur", function () {
        var data_url = $('#obiba-mica-search-form').serialize();
        window.location = window.location.origin + Drupal.settings.context.currentCleanPath + data_url;
      });

      $("#edit-search-sort-order").on("change", function () {
        var data_url = $('#obiba-mica-search-form').serialize();
        window.location =  window.location.origin + Drupal.settings.context.currentCleanPath + data_url;
      });

      $("#edit-search-sort").on("change", function () {
        var data_url = $('#obiba-mica-search-form').serialize();
        window.location =  window.location.origin + Drupal.settings.context.currentCleanPath + data_url;
      });

      $("#refresh-button").on("click", function () {
        event.preventDefault();
        window.location = window.location.origin + Drupal.settings.context.currentCleanPath;
      });
      /*******************/
    }
  }
})(jQuery);
