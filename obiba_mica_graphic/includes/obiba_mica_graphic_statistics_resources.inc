<?php

/**
 * @file
 * Mica networks file
 */
class NetworkStatistics extends MicaSearchResource {
  const MODULE_GRAPHIC_CHARTS_GEO_CHART = 'GraphicChartsGeoChart';
  const MODULE_GRAPHIC_CHARTS_STUDY_DESIGN_CHART = 'GraphicChartsStudyDesignChart';

  const GEO_NBR_STAT = 'countriesIso';
  const RECRUITMENT_SOURCES = 'recruitment-dataSources';
  const METHODS_DESIGNS = 'methods-designs';
  const BIO_SAMPLES = 'populationDceBioSamples';
  const ACCESS = 'access';
  public $id_networks;

  function __construct($id_networks) {
    parent::__construct();
    $id_networks= explode(',', $id_networks);
    $this->id_networks = json_encode($id_networks);
  }

  static function deltaAggregationsMap(){
    return array(
      NetworkStatistics::GEO_NBR_STAT =>'populations-selectionCriteria-countriesIso',
      NetworkStatistics::RECRUITMENT_SOURCES => 'populations-recruitment-dataSources',
      NetworkStatistics::METHODS_DESIGNS => 'methods-designs',
      NetworkStatistics::BIO_SAMPLES => 'populations-dataCollectionEvents-bioSamples',
      NetworkStatistics::ACCESS => 'access',
      );
  }

  public function _aggregation_resource_external($parts_query = NULL) {
    $dto_param = $this->_get_dto_query_param_from_url($parts_query, $parts_query['type']);

    $url = $this->micaUrl . '/' . $parts_query['type'] . '/_search';

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_POST,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
          'Content-Type' => array(parent::HEADER_JSON)
        )
      ),
      'data' => !empty($dto_param) ? $dto_param : $this->dtoFilterConstruct($parts_query['type'], NULL, 0, NULL),
    ));

    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return json_decode($data);
    }
    catch (HttpClientException $e) {
      if ($e->getCode() == 403) {
        drupal_set_message('<i class="glyphicon glyphicon-info-sign"></i> Please set correct credentials access to mica-server', 'warning');
      }
      watchdog('Mica Client', 'Connection to server fail,  Error serve code : @code, message: @message',
        array('@code' => $e->getCode(), '@message' => $e->getMessage()), WATCHDOG_WARNING);
      return array();
    }
  }

  private function _get_dto_query_param_from_url($parts = NULL, $type, $parameters = NULL) {
    $from = empty($parts['page']) ? 0 : $this->paginationListSearchParameters($_GET['page'], $type, MicaClient::getResponsePageSize());
    $q = empty($parts['query']) ? (empty($parameters) ? NULL : $parameters) : $parts['query'];
    $group_by = empty($parts['group-by']) ? NULL : $parts['group-by'];
    $withFacets = empty($parts['with-facets']) ? TRUE : strtolower($parts['with-facets']) === "true";

    return $this->dtoFilterConstruct($type, $q, $from, $group_by, $withFacets);
  }

  public function GeoStudiesQuery() {
      $parts_query['type'] = 'studies';
      if (!empty($this->id_networks) && $this->id_networks !== '["NaN"]') {
        $parts_query['query'] = '{"networks":{"terms":{"networkId":{"values":' . $this->id_networks . ',"op":"and"}}}}';
      }
      $data = $this->_aggregation_resource_external($parts_query);
    return $data;
  }

  public function queryForPieChart() {
    $parts_query['type'] = 'studies';
    if (!empty($this->id_networks) && $this->id_networks !== '["NaN"]') {
      $parts_query['query'] = '{"networks":{"terms":{"networkId":{"values":' . $this->id_networks . ',"op":"and"}}}}';
    }
    $data = $this->_aggregation_resource_external($parts_query);
    return $data;
  }

  public function getTableData($chart_data, $percentage = FALSE) {
    $header = $chart_data[0];
    array_shift($chart_data);
    if (!empty($percentage)) {
      $total_studies = array_sum(array_column($chart_data, 1));
      foreach ($chart_data as $key_tab => $item_value) {
        $chart_data[$key_tab][1] = round(($chart_data[$key_tab][1] * 100) / $total_studies, 1) . ' %';
      }
    }
    return theme('table', array('header' => $header, 'rows' => $chart_data));
  }

}
