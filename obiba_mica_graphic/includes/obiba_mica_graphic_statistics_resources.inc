<?php

/**
 * @file
 * Mica networks file
 */
class NetworkStatistics extends MicaSearchResource {
  const MODULE_GRAPHIC_CHARTS_GEO_CHART = 'GraphicChartsGeoChart';
  const MODULE_GRAPHIC_CHARTS_STUDY_DESIGN_CHART = 'GraphicChartsStudyDesignChart';

  const GEO_NBR_STAT = 'countriesIso';
  const METHODS_DESIGNS = 'methods-designs';
  const BIO_SAMPLES = 'populationDceBioSamples';
  public $id_networks;

  function __construct($id_networks) {
    parent::__construct();
    $id_networks= explode(',', $id_networks);
    $this->id_networks = json_encode($id_networks);
  }

  static function deltaAggregationsMap(){
    return array(
      NetworkStatistics::GEO_NBR_STAT =>'populations-selectionCriteria-countriesIso',
      NetworkStatistics::METHODS_DESIGNS => 'methods-designs',
      NetworkStatistics::BIO_SAMPLES => 'populations-dataCollectionEvents-bioSamples',
      );
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
