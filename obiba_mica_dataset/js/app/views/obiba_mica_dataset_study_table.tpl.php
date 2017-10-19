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
 * Code for the obiba_mica_dataset modules.
 */

?>
<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<span ng-init="info = extractSummaryInfo(contingency.studyTable)" title="{{info.population ? info.population + ':' + info.dce : ''}}">
  <span ng-if="contingency.studyTable">
    <a href="<?php print $base_path . 'mica/' . DrupalMicaStudyResource::INDIVIDUAL_STUDY; ?>/{{contingency.studyTable.studyId}}">{{contingency.studyTable.studySummary.acronym | localizedValue}}</a>
    <span>{{contingency.studyTable.name | localizedValue}}</span>
  </span>
</span>
