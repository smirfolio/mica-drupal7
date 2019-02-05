/*
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

(function ($) {
  Drupal.behaviors.obiba_mica_study_detail = {
    attach: function (context, settings) {
      if (context === document) {
        var qNetworks;
        var optionsStudyContent = settings.optionsStudyContent;

        if (optionsStudyContent) {
          if (optionsStudyContent.showNetwork) {
            qNetworks = $.ajax(Drupal.settings.basePath + Drupal.settings.pathPrefix + settings.study_url + '/networks')
              .done(function (data) {
                if (!data) {
                  $('#networks').remove();
                  return;
                }

                $('#networks').html(data).show();
              })
              .fail(function () {
                $('#networks').remove();
              });
          }
          else {
            $('#networks').remove();
          }
        }

        function cleanHash(hash) {
          return hash.substr(1) ? hash.substr(1).replace(/^\//, '') : null;
        }

        var anchor = cleanHash(location.hash);
        if (anchor) {
          $('#tab-pane a[href="#' + anchor + '"]').tab('show');
          var scrollSpot = $('#' + anchor);

          if (scrollSpot.length) {
            $('html, body').animate({
              scrollTop: scrollSpot.offset().top
            }, 'slow');
          }
        }

        window.onhashchange = function (event) {
          var hash = cleanHash(event.currentTarget.location.hash);
          if (hash) {
            $('#tab-pane a[href="#' + hash + '"]').tab('show');
          }
        }
      }
    }
  }
}(jQuery));