<?php

/*
 * @file class definition path server resources
 * */

class MicaClientPathProvider {
  const STUDIES = 'mica/studies';
  const STUDY = 'mica/study/{id}';
  const NETWORKS = 'mica/networks';
  const NETWORK = 'mica/network/{id}';
  const DATASETS = 'mica/datasets';
  const STUDY_DATASETS = 'mica/datasets/study-datasets';
  const STUDY_DATASET = 'mica/study-dataset/{id}';
  const HARMONIZATION_DATASETS = 'mica/datasets/harmonization-datasets';
  const HARMONIZATION_DATASET = 'mica/harmonization-dataset/{id}';
  const SEARCH = 'mica/search';
  const COVERAGE = 'mica/coverage';


  static function study($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY, 1);
  }

  static function network($id) {
    return preg_replace('/\\{id\\}/', $id, self::NETWORK, 1);
  }

  static function study_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY_DATASET, 1);
  }

  static function harmonization_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::HARMONIZATION_DATASET, 1);
  }
}

class MicaClientAnchorHelper {

  static function study_datasets($text, $study_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('studyIds' => $study_id))) //
    );

    $options = array(
      'query' => array(
        'type' => 'datasets',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function study_variables($text, $study_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('studyIds' => $study_id))) //
    );

    $options = array(
      'query' => array(
        'type' => 'variables',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function network_studies($text, $networkId) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('networks' => array('terms' => array('id' => $networkId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'studies',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function search_networks($text) {
    $options = array(
      'query' => array(
        'type' => 'networks'
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function coverage_networks($text) {
    $options = array(
      'query' => array(
        'group-by' => 'studyIds'
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::COVERAGE, $options);
  }

  static function dataset_variables($text, $datasetId) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $datasetId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'variables',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function dataset_studies($text, $datasetId) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $datasetId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'studies',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function search_studies($text) {
    $options = array(
      'query' => array(
        'type' => 'studies'
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function coverage_studies($text) {
    $options = array(
      'query' => array(
        'group-by' => 'studyIds'
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::COVERAGE, $options);
  }

  static function search_study_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "study"))) //
    );

    $options = array(
      'query' => array(
        'type' => 'variables',
        'query' => $query
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function coverage_study_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "study"))) //
    );
    $options = array(
      'query' => array(
        'group-by' => 'datasetId',
        'query' => $query
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::COVERAGE, $options);
  }

  static function search_harmonization_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "dataschema"))) //
    );
    $options = array(
      'query' => array(
        'type' => 'variables',
        'query' => $query
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function coverage_harmonization_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "dataschema"))) //
    );
    $options = array(
      'query' => array(
        'group-by' => 'datasetId',
        'query' => $query
      ),
      'attributes' => array('class' => 'btn-sm highlight btn btn-primary')
    );

    return l($text, MicaClientPathProvider::COVERAGE, $options);
  }

}
