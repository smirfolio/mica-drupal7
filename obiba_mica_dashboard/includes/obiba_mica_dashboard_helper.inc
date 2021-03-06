<?php

/**
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

class MicaMetricsHelper {

  public static function formatAsMap($metrics) {
    $localize = obiba_mica_commons_mica_server_localisation();
    if (empty($metrics)) throw new Exception("Metrics data is null");
    if (empty($metrics->documents)) throw new Exception("No document Metrics was found");
    $map = array();
    foreach ($metrics->documents as &$document) {
      $type =$document->type;
      $key = self::getKeyFromType($type);
      if (!empty($key)) {
        $propertiesMap = new stdClass();

        array_map(function ($property) use ($propertiesMap) {
          $propertiesMap->{$property->name} = $property->value;
        }, $document->properties);
        $document->properties = $propertiesMap;

        $document->publishedFormatted = obiba_mica_commons_format_number($propertiesMap->published);

        if (!empty($propertiesMap->totalWithVariable)) {
          $document->totalWithVariableFormatted = obiba_mica_commons_format_number($propertiesMap->totalWithVariable);
          $document->withVariableTitle = $localize->getTranslation('metrics.mica.' . self::getKeyFromType($type . 'WithVariable') );
        }

        if (!empty($propertiesMap->variables)) {
          $document->variablesFormatted = obiba_mica_commons_format_number($propertiesMap->variables);
          $document->variablesTitle = $localize->getTranslation('metrics.mica.' . self::getKeyFromType($type. 'Variable') );
        }

        $document->title = $localize->getTranslation('metrics.mica.' . $key);
        $map[$document->type] = $document;
      }
    }

    return $map;
  }

  private static function getKeyFromType($type) {
    switch ($type) {
      case 'Network':
        return 'networks';
      case 'Study' :
        return 'studies';
      case 'StudyWithVariable':
        return 'studies-with-variables';
      case 'StudyVariable':
        return 'study-variables';
      case 'HarmonizationStudy' :
        return 'harmonization-studies';
      case 'HarmonizationStudyVariable':
        return 'harmonization-study-variables';
      case 'StudyDataset':
        return 'collection-datasets';
      case 'HarmonizationDataset':
        return 'harmonized-datasets';
      case 'DatasetVariable':
        return 'variables';
    }

    return NULL;
  }
}
