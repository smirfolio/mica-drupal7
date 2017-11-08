<?php
/**
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
 * class tools provided by Mica client
 */

class ObibaDatasetConstants {
  const FACET_TYPE_HIDE = 0;
  const FACET_TYPE_AUTOCOMPLETE = 1;
  const FACET_TYPE_CHECKBOX = 2;

  const  UNDETERMINED_HARMO_ICON = 'glyphicon-question-sign';
  const  COMPLETE_HARMO_ICON = 'glyphicon-ok';
  const  INCOMPLETE_HARMO_ICON = 'glyphicon-minus';
  const  IMPOSSIBLE_HARMO_ICON = 'glyphicon-remove';

  /**
   * Set the harmonization status icon.
   */
  public static function getIcon() {
    $impossible_icon = variable_get_value('dataset_harmonization_impossible_icon');
    $color_icon = (!empty($impossible_icon) && $impossible_icon != ObibaDatasetConstants::IMPOSSIBLE_HARMO_ICON) ?
      ' alert-black' : ' alert-danger';
    return !empty($impossible_icon) ? ($impossible_icon . $color_icon) : (ObibaDatasetConstants::IMPOSSIBLE_HARMO_ICON . $color_icon);
  }

  /*
   * Function to call correct Callback in the boutton template
   * */
  public static function bouttonAnchor($method, $text = NULL ,$id , $attributes){
    return call_user_func($method, $text, $id, $attributes);;
  }
}
