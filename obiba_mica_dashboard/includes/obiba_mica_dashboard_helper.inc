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

class MicaMetricsHelper {

  public static function formatAsMap($metrics) {
    $localize = obiba_mica_commons_mica_server_localisation();
    if (empty($metrics)) throw new Exception("Metrics data is null");
    if (empty($metrics->documents)) throw new Exception("No document Metrics was found");
    $map = array();
    foreach ($metrics->documents as &$document) {
      $document->title = $localize->getTranslation('metrics.mica.' . self::getKeyFromType($document->type));
      $map[$document->type] = $document;
    }

    return $map;
  }

  private static function getKeyFromType($type) {
    switch ($type) {
      case 'Network':
        return 'networks';
      case 'Study' :
        return 'studies';
      case 'CollectionDataset':
        return 'collection-datasets';
      case 'HarmonizationDataset':
        return 'harmonization-datasets';
      case 'DatasetVariable':
        return 'variables';
      case 'StudyWithVariable':
        return 'studies-with-variables';
    }

    throw new Exception("Invalid metric type");
  }
}
