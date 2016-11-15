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
 * MicaStudyResource class
 */

/**
 * Class MicaStudyResource
 */
class DrupalMicaStudyResource{

  public function __construct() {
  }

  /**
   * Get the list of studies.
   *
   * @param null $query .
   * @param int $from .
   * @param $limit .
   * @param null $sort field name to sort by.
   * @param null $order "asc" or "desc".
   * @param null $study_rql_query rql query "in(Mica_study.id,(epoa,ici-vph)".
   *
   * @return array|mixed
   */
  public function getStudies($query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    $parameters = compact('query', 'from', 'limit', 'sort', 'order');
    $obiba->buildResourceQuery('getStudies', $parameters);
    return $obiba->getCollections('getStudies');
  }

  /**
   * Get a study by its ID.
   *
   * @param $study_id
   *
   * @return array
   */
  public function getStudy($study_id, $token_key = NULL) {
    $obiba = new \ObibaMicaClient\ObibaMicaDocuments();
    return $obiba->buildResourceQuery('getStudy', $study_id)
      ->getDocument('getStudy');
  }
}