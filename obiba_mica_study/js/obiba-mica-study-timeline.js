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
 * code to initialise Timeline
 */

(function ($) {
  Drupal.behaviors.datatables_add_head = {
    attach: function (context, settings) {
      if (context === document) {
        if (Drupal.settings.obiba_mica_study.study_json) {
          new $.MicaTimeline(
            new $.StudyDtoParser(),
            timelinePopupIdFormatter,
            true
          ).create("#vis", JSON.parse(Drupal.settings.obiba_mica_study.study_json)).addLegend();
        }
      }

      function timelinePopupIdFormatter(study, pop, dce) {
        return ('#dce-' + study.id + '-' + pop.id + '-' + dce.id).replace(/\+/g, '-').replace(/\./, '___');
      }
    }
  }
})(jQuery);
