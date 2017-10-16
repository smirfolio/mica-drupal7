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
 * Mica client studies retrieve Studies lists
 */

/**
 * Format column study table depending in studies type
 */
function obiba_mica_study_study_table_column($row, $type) {
  switch ($type) {
    case DrupalMicaStudyResource::HARMONIZATION_STUDY:
      array_splice($row, 2, -1);
      return $row;
      break;
    default:
      return $row;
  }
}


function obiba_mica_study_study_summaries_table_headers($study_type = DrupalMicaStudyResource::INDIVIDUAL_STUDY) {
  $localize = obiba_mica_commons_mica_server_localisation();
  $header = array(
    array("title" => $localize->getTranslation('study.acronym')),
    array("title" => $localize->getTranslation('study.name')),
    array("title" => $localize->getTranslation('study.design')),
    array("title" => $localize->getTranslation('client.label.dataset.participants')),
    array("title" => $localize->getTranslation('client.label.countries')),
    array("title" => $localize->getTranslation('variables')),
  );
  return obiba_mica_study_study_table_column($header, $study_type);
}

function obiba_mica_study_study_summaries_table_rows($study_summaries) {
  $rows = array();
  if (!empty($study_summaries)) {
    foreach ($study_summaries as $study_summary) {
      $rows[] = obiba_mica_study_study_summaries_table_row($study_summary);
    }
  }
  return $rows;
}

function obiba_mica_study_study_summaries_table_row($study_summary) {
  $localize = obiba_mica_commons_mica_server_localisation();
  $name = obiba_mica_commons_get_localized_field($study_summary, 'name');
  return array(
    DrupalMicaStudyResource::anchorStudy($study_summary),
    $name,
    isset($study_summary->design) ? obiba_mica_study_translate_study_design_summary($study_summary->design) : '',
    isset($study_summary->targetNumber->noLimit) ? $localize->getTranslation('numberOfParticipants.no-limit') :
      isset($study_summary->targetNumber->number) ? obiba_mica_commons_format_number($study_summary->targetNumber->number) : NULL,
    isset($study_summary->countries) ? obiba_mica_commons_countries($study_summary->countries) : NULL,
    isset($study_summary->variables) ?obiba_mica_commons_format_number($study_summary->variables) : NULL,
  );
}
