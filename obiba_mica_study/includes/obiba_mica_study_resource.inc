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
class MicaStudyResource extends MicaClient {

  public function __construct($mica_url = NULL) {
    parent::__construct($mica_url);
  }

  /**
   * Get the list of studies.
   *
   * @param null $query.
   * @param int $from.
   * @param $limit.
   * @param null $sort field name to sort by.
   * @param null $order "asc" or "desc".
   * @param null $study_rql_query rql query "in(Mica_study.id,(epoa,ici-vph)".
   *
   * @return array|mixed
   */
  public function getStudies($query = NULL, $from = 0, $limit = 5, $sort = NULL, $order = NULL) {
    global $language;
    $this->setLastResponse(NULL);
    $from = empty($from) ? '0' : $from;
    $limit = empty($limit) ? '5' : $limit;
    $order = empty($order) ? '' : ($order == 'desc' ? '-' : '');
    $sort_rql_bucket = empty($sort) ? "" : ",sort($order$sort)";
    $query = empty($query) ? NULL : ",match($query,(Mica_study.name,Mica_study.acronym,Mica_study.objectives))";
    if (empty($query)) {
      $params = "study(exists(Mica_study.id),limit($from,$limit)$sort_rql_bucket)";
    }
    else {
      $params = "study(limit($from,$limit)$query$sort_rql_bucket)";
    }
    $params .= ",locale($language->language)";
    $resource_query = '/studies/_rql?query=' . $params;

    $this->getCache($resource_query);
    if (!isset($this->result_resource_query)) {
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
        $this->result_resource_query = new StudyJoinResponseWrapper(json_decode($data));
        obiba_mica_commons_set_cache($resource_query, $this->result_resource_query);
        return $this->result_resource_query;
      }
      catch (HttpClientException $e) {
        watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
          array(
            '@code' => $e->getCode(),
            '@message' => $e->getMessage()
          ), WATCHDOG_WARNING);
        $this->result_resource_query = NULL;
        return array();
      }
    }
    return $this->result_resource_query;
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
    $this->getCache($resource_query);
    $url = $this->micaUrl . $resource_query;
    if (!isset($this->result_resource_query)) {
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
        $this->result_resource_query = $data ? json_decode($data) : NULL;

        if (!empty($this->result_resource_query)) {
          $this->updateModel($this->result_resource_query);
          if (!empty($this->result_resource_query->populations)) {
            foreach ($this->result_resource_query->populations as $population) {
              $this->updateModel($population);
              if (!empty($population->dataCollectionEvents)) {
                foreach ($population->dataCollectionEvents as $dce) {
                  $this->updateModel($dce);
                }
              }
            }
          }
        }

        obiba_mica_commons_set_cache($resource_query, $this->result_resource_query);
        return $this->result_resource_query;
      }
      catch (HttpClientException $e) {
        $this->result_resource_query = NULL;
      }
      return array();
    }
    return $this->result_resource_query;
  }

  private function updateModel($obj) {
    if (!empty($obj->content)) {
      $obj->model = json_decode($obj->content);
    } else {
      $obj->model = new stdClass();
    }
  }
}