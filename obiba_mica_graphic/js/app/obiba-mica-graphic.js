/*
 * Copyright (c) 2015 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
modules.push('mica.GraphicChartsStudyDesignChart');
modules.push('mica.GraphicChartsGeoChart');
mica.GraphicChartsStudyDesignChart = angular.module('mica.GraphicChartsStudyDesignChart', [ 'googlechart']);
mica.GraphicChartsGeoChart = angular.module('mica.GraphicChartsGeoChart', [ 'googlechart']);

mica.GraphicChartsStudyDesignChart.config(function(){

  console.log('toto');
  console.log(modules);
});

//(function ($) {
//
//  Drupal.behaviors.obiba_mica_graphic = {
//    attach: function (context, settings) {
//      GraphicChartsGeoChart = angular.module('GraphicChartsGeoChart', [
//        'googlechart'
//      ]);
//    }
//  }
//}(jQuery));

