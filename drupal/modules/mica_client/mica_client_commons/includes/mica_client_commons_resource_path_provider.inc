<?php

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

  static function studies() {
    return self::STUDIES;
  }

  static function study($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY, 1);
  }

  static function networks() {
    return self::NETWORKS;
  }

  static function network($id) {
    return preg_replace('/\\{id\\}/', $id, self::NETWORK, 1);
  }

  static function datasets() {
    return self::DATASETS;
  }

  static function study_datasets() {
    return self::STUDY_DATASETS;
  }

  static function study_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY_DATASET, 1);
  }

  static function harmonization_datasets() {
    return self::HARMONIZATION_DATASETS;
  }

  static function harmonization_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::HARMONIZATION_DATASET, 1);
  }

  static function search_study_datasets($text, $studyId) {
    $query = MicaClient::add_parameter_dto_query_link(array('variables' => array('terms' => array('studyIds' => $studyId))));
    $options = array(
      'query' => array(
        'type' => 'networks',
        'query' => $query
      )
    );

    return l($text, 'mica/search', $options);
  }
}
