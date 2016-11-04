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
  Drupal.behaviors.obiba_mica_network_detail = {
    attach: function (context, settings) {
      if (context === document) {
        if (settings.study_ids.length > 0) {
          if (Drupal.settings.displayCoverage) {
            var resource_url = Drupal.settings.basePath
              + Drupal.settings.pathPrefix
              + 'mica/coverage/network/'
              + encodeURIComponent(JSON.stringify(settings.study_ids ? settings.study_ids : []));

            $.ajax(resource_url)
              .done(function (data) {
                if (!data) {
                  $('#coverage').remove();
                  return;
                }
              })
              .fail(function () {
                $('#coverage').remove();
              });
          }


          $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + 'mica/network/' + settings.networkUrl + '/datasets')
            .done(function (data) {
              if (!data) {
                $('#datasets').remove();
                return;
              }
              $('#datasets').html(data).show();
              var datasets = $('#datasetsDisplay').data();
            })
            .fail(function () {
              $('#datasets').remove();
            });

        }
        else {
          $('#coverage').remove();
          $('#datasets').remove();
        }
      }
    }
  }
}(jQuery));