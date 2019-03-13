/*
 * Copyright (c) 2017 Smirfolio. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

'use strict';
(function ($) {
    Drupal.behaviors.obiba_remove_mails = {
        attach: function (context, settings) {
            if (context != document) {
                return;
            }
            $.transformMail(Drupal.settings.obiba_mica_mails_selector);

        }
    }
}(jQuery));