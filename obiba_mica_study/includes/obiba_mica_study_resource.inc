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

use \Obiba\ObibaMicaClient\MicaCache as MicaCache;

/**
 * Class MicaStudyResource
 */
class MicaStudyResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url, new MicaCache\MicaDrupalClientCache());
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
    global $language;
    $this->setLastResponse(NULL);
    $resource_query = $this->generateRqlQuery($query, $from, $limit, $sort, $order, $language);

    $cached_studies = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    if(!empty($cached_studies)){
      return $cached_studies;
    }
    else {
      $url_studies = $this->micaUrl . $resource_query;
      $request = new HttpClientRequest($url_studies, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        )
      ));
      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $response_wrapper = json_decode($data);
        if ($response_wrapper->studyResultDto->totalCount !== 0) {
          $return_studies = new StudyJoinResponseWrapper(json_decode($data));
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $return_studies);
          return $return_studies;
        }
      } catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        return array();
      }
    }
  }

  /**
   * Get a study by its ID.
   *
   * @param $study_id
   *
   * @return array
   */
  public function getStudy($study_id) {
    $resource_query = '/study/' . rawurlencode($study_id);
    $this->setLastResponse(NULL);
    $cached_study = $this->drupalCache->MicaGetCache(__FUNCTION__ . $resource_query);
    $url = $this->micaUrl . $resource_query;
    if(!empty($cached_study)){
      return $cached_study;
    }
    else {
      $request = new HttpClientRequest($url, array(
        'method' => HttpClientRequest::METHOD_GET,
        'headers' => $this->authorizationHeader(array(
            'Accept' => array(parent::HEADER_JSON),
          )
        ),
      ));

      $client = $this->client();
      try {
        $data = $client->execute($request);
        $this->setLastResponse($client->lastResponse);
        $result_study = $data ? json_decode($data) : NULL;

        if (!empty($result_study)) {
          $this->updateModel($result_study);
          if (!empty($result_study->populations)) {
            foreach ($result_study->populations as $population) {
              $this->updateModel($population);
              if (!empty($population->dataCollectionEvents)) {
                foreach ($population->dataCollectionEvents as $dce) {
                  $this->updateModel($dce);
                }
              }
            }
          }
          $this->drupalCache->MicaSetCache(__FUNCTION__ . $resource_query, $result_study);
          return $result_study;
        }
      } catch (HttpClientException $e) {
        return array();
      }
    }
  }

  private function updateModel($obj) {
    if (!empty($obj->content)) {
      $obj->model = json_decode($obj->content);
    }
    else {
      $obj->model = new stdClass();
    }
  }

  /**
   * @param $query
   * @param $from
   * @param $limit
   * @param $sort
   * @param $order
   * @param $language
   * @return string
   */
  private function generateRqlQuery($query, $from, $limit, $sort, $order, $language) {
    $from = empty($from) ? '0' : $from;
    $limit = empty($limit) ? '5' : $limit;
    $order = empty($order) ? '' : ($order == 'desc' ? '-' : '');
    $sort_rql_bucket = empty($sort) ? "" : ",sort($order$sort)";
    $query = empty($query) ? NULL : ",match($query,(Mica_study.name,Mica_study.acronym,Mica_study.objectives))";
    if (empty($query)) {
      $params = "study(exists(Mica_study.id),limit($from,$limit)$sort_rql_bucket)";
    } else {
      $params = "study(limit($from,$limit)$query$sort_rql_bucket)";
    }
    $params .= ",locale($language->language)";
    $resource_query = '/studies/_rql?query=' . $params;
    return $resource_query;
  }
}