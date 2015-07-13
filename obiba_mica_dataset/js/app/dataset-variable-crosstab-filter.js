/*
 * Copyright (c) 2014 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
'use strict';

(function ($) {
  Drupal.behaviors.obiba_mica_dataset_variable_crosstab_filter = {
    attach: function (context, settings) {

      mica.DatasetVariableCrosstab
        .filter('variableLabel', ['AttributeService',
          function (AttributeService) {
            return function (variable) {
              var label = '';
              if (variable) {
                var attributes = AttributeService.getAttributes(variable, ['label']);
                if (attributes) {
                  attributes.forEach(
                    function(attribute) {
                      label = AttributeService.getValue(attribute);
                      return false;
                    });
                }

                return label;
              }
            }
          }])

        .filter('localizedValue', ['LocalizedStringService',
          function (LocalizedStringService) {
            return function (container) {
              if (container) {
                return LocalizedStringService.getValue(container);
              }
            }
          }])
    }
  }
}(jQuery));

