<?php

class MicaClientPathProvider
{
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


  static function study($id)
  {
    return preg_replace('/\\{id\\}/', $id, self::STUDY, 1);
  }

  static function network($id)
  {
    return preg_replace('/\\{id\\}/', $id, self::NETWORK, 1);
  }

  static function study_dataset($id)
  {
    return preg_replace('/\\{id\\}/', $id, self::STUDY_DATASET, 1);
  }

  static function harmonization_dataset($id)
  {
    return preg_replace('/\\{id\\}/', $id, self::HARMONIZATION_DATASET, 1);
  }
}

class MicaClientAnchorHelper
{

  static function search_study_datasets($text, $studyId)
  {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('studyIds' => $studyId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'datasets',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function search_study_variables($text, $studyId)
  {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('studyIds' => $studyId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'variables',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function search_network_studies($text, $networkId)
  {
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

  static function search_dataset_variables($text, $datasetId)
  {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $datasetId))) //
    );

    $options = array(
      'query' => array(
        'type' => 'datasets',
        'query' => $query
      )
    );

    return l($text, MicaClientPathProvider::SEARCH, $options);
  }

  static function search_dataset_studies($text, $datasetId)
  {
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
}
