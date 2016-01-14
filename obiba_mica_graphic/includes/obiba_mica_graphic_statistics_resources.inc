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

  public function statisticsQuery($type_entities, $query_dto) {
    $url = $this->micaUrl . '/' . $type_entities . '/_search';

    $request = new HttpClientRequest($url, array(
      'method' => HttpClientRequest::METHOD_POST,
      'headers' => $this->authorizationHeader(array(
          'Accept' => array(parent::HEADER_JSON),
          'Content-Type' => array(parent::HEADER_JSON)
        )
      ),
      'data' => !empty($query_dto) ? $query_dto : $this->dtoFilterConstruct($type_entities, NULL, 0, NULL),
    ));;
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->setLastResponse($client->lastResponse);
      return $data;
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
