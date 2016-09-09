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
  Drupal.behaviors.obiba_mica_study_shorten_text = {
    attach: function (context, settings) {

      /********* More/Less in search block ********/
      $(".trim-studies").each(function () {
        var controlSelector = $(this).attr('data-target');
        $(controlSelector).on('shown.bs.collapse', function () {
          $("button[data-target='" + controlSelector + "']").html(Drupal.settings.linkRead['less']);
        });
        $(controlSelector).on('hidden.bs.collapse', function () {
          $("button[data-target='" + controlSelector + "']").html(Drupal.settings.linkRead['more']);
        });
      });

    }
  }
}(jQuery));
