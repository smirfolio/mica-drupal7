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
  const HARMONIZATION_VARIABLE = 'mica/variable/{id}:{name}:Dataschema';
  const SEARCH = 'mica/search';
  const COVERAGE = 'mica/coverage';


  static function study($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY, 1);
  }

  static function network($id) {
    return preg_replace('/\\{id\\}/', $id, self::NETWORK, 1);
  }

  static function dataset($dataset) {
    return !empty($dataset->{'obiba.mica.StudyDatasetDto.type'})
      ? self::study_dataset($dataset->id)
      : self::harmonization_dataset($dataset->id);
  }

  static function study_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::STUDY_DATASET, 1);
  }

  static function harmonization_dataset($id) {
    return preg_replace('/\\{id\\}/', $id, self::HARMONIZATION_DATASET, 1);
  }

  static function variable_dataset($variable) {
    return $variable->variableType == 'Study'
      ? self::study_dataset($variable->datasetId)
      : self::harmonization_dataset($variable->datasetId);
  }

  static function variable_harmonized($variable) {
    return preg_replace(
      '/(\\{id\\}):(\\{name\\})/',
      "$variable->datasetId:$variable->name",
      self::HARMONIZATION_VARIABLE,
      1
    );
  }

}

class MicaClientAnchorHelper {
  const DEFAULT_PRIMARY_BUTTON_CLASSES = 'btn highlight btn btn-primary';

  static function ellipses($text, $paragraph, $url, $max_length = 300) {
    if (empty($paragraph)) {
      return '';
    }

    if (drupal_strlen($paragraph) >= $max_length) {
      return text_summary(strip_tags(obiba_mica_commons_markdown($paragraph)), 'html', $max_length) . '... ' . l($text, $url);
    }

    return $paragraph;
  }

  static function study_list_item($study) {
    return self::list_item($study, MicaClientPathProvider::study($study->id));
  }

  static function study($study) {
    $name = obiba_mica_commons_get_localized_field($study, 'name');
    return l( $name, MicaClientPathProvider::study($study->id), array());
  }

  static function study_population_modal($population) {
    return l(obiba_mica_commons_get_localized_field($population, 'name'), '#', array(
      'external' => TRUE,
      'attributes' => array(
        'data-toggle' => 'modal',
        'data-target' => '#population-' . $population->id
      )
    ));
  }

  static function study_population_dce_modal($studyId, $populationId, $dce) {
    return l(obiba_mica_commons_get_localized_field($dce, 'name'), '#', array(
      'external' => TRUE,
      'attributes' => array(
        'data-toggle' => 'modal',
        'data-target' => '#dce-' . $studyId . '-' . $populationId . '-' . $dce->id
      )
    ));
  }

  static function study_datasets($text, $study_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('studyIds' => $study_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array(), //
      array('type' => 'datasets', 'query' => $query) //
    );
  }

  static function study_variables($text, $study_id, array $attributes = array()) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('studies' => array('terms' => array('studyIds' => $study_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      $attributes, //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function dce_study($text, $dceId, array $attributes = array()) {
    $query = MicaClient::create_query_dto_as_string(array("variables" => array("terms" => array("dceIds" => $dceId))));

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      $attributes, //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function coverage_dce_study($text, $dceId, array $attributes = array()) {
    $query = MicaClient::create_query_dto_as_string(array("variables" => array("terms" => array("dceIds" => $dceId))));

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      $attributes, //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function network_list_item($network) {
    return self::list_item($network, MicaClientPathProvider::network($network->id));
  }

  static function network($network) {
    $name = obiba_mica_commons_get_localized_field($network, 'name');
    return l( $name, MicaClientPathProvider::network($network->id), array());
  }

  static function study_networks($text, $study_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('studies' => array('terms' => array('studyIds' => $study_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array(), //
      array('type' => 'networks', 'query' => $query) //
    );
  }

  static function network_studies($text, $network_id, array $attributes = array()) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('networks' => array('terms' => array('networkId' => $network_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      $attributes, //
      array('type' => 'studies', 'query' => $query) //
    );
  }

  static function network_datasets($text, $network_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('networks' => array('terms' => array('networkId' => $network_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array(), //
      array('type' => 'datasets', 'query' => $query) //
    );
  }

  static function network_variables($text, $network_id, array $attributes = array()) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('networks' => array('terms' => array('networkId' => $network_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      $attributes, //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function search_networks($text) {
    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('type' => 'networks') //
    );
  }

  static function coverage_network($text, $networkId) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('networks' => array('terms' => array('networkId' => $networkId))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('group-by' => 'studyIds', 'query' => $query) //
    );
  }

  static function coverage_networks($text) {
    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('group-by' => 'studyIds') //
    );
  }

  static function dataset_list_item($dataset) {
    return self::list_item($dataset, MicaClientPathProvider::dataset($dataset));
  }

  static function dataset_variables($text, $dataset_id, array $attributes = array()) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $dataset_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      $attributes, //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function coverage_dataset($text, $dataset_id, array $attributes = array()) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $dataset_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      empty($attributes) ? array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES) : $attributes, //
      array('group-by' => 'studyIds', 'query' => $query) //
    );
  }

  static function dataset_studies($text, $dataset_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $dataset_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array(), //
      array('type' => 'studies', 'query' => $query) //
    );
  }

  static function dataset_networks($text, $dataset_id) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('datasetId' => $dataset_id))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array(), //
      array('type' => 'networks', 'query' => $query) //
    );
  }

  static function search_studies($text) {
    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('type' => 'studies') //
    );
  }

  static function coverage_studies($text) {
    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('group-by' => 'studyIds') //
    );
  }

  static function coverage_study($text, $studyId, array $attributes = array()) {
    $query = MicaClient::create_query_dto_as_string(array("studies" => array("terms" => array("studyIds" => $studyId))));

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      $attributes, //
      array('group-by' => 'studyIds', 'query' => $query) //
    );
  }

  static function search_study_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "study"))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('type' => 'variables', 'query' => $query) //
    );

  }

  static function coverage_study_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "study"))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('group-by' => 'datasetId', 'query' => $query) //
    );
  }

  static function search_harmonization_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "dataschema"))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::SEARCH, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('type' => 'variables', 'query' => $query) //
    );
  }

  static function coverage_harmonization_datasets($text) {
    $query = MicaClient::add_parameter_dto_query_link( //
      array('variables' => array('terms' => array('variableType' => "dataschema"))) //
    );

    return self::ajax_friendly_anchor( //
      MicaClientPathProvider::COVERAGE, //
      $text, //
      array('class' => self::DEFAULT_PRIMARY_BUTTON_CLASSES), //
      array('group-by' => 'datasetId', 'query' => $query) //
    );
  }

  static function variable_dataset($variable) {
    $datasetName = obiba_mica_commons_get_localized_field($variable, 'datasetName');
    return l(
      $datasetName,
      MicaClientPathProvider::variable_dataset($variable)
    );
  }

  static function variable_harmonized($variable) {
    return l(
      $variable->name,
      MicaClientPathProvider::variable_harmonized($variable)
    );
  }

  static function list_item($dto, $url) {
    $acronym = obiba_mica_commons_get_localized_field($dto, 'acronym');
    $name = obiba_mica_commons_get_localized_field($dto, 'name');
    return l($acronym == $name ? $acronym : $acronym . '  -  ' . $name, $url);
  }

  static function ajax_friendly_anchor($url, $text, array $attributes, array $query_params) {
    $options = array();

    // Drupal may require css classes to be inside an array!
    if (!empty($attributes) && !empty($attributes['class'])) {
      $attributes['class'] = self::format_class_as_array($attributes['class']);
    }

    if (!empty($attributes)) $options['attributes'] = $attributes;
    if (!empty($query_params)) {
      if (empty($query_params['query'])) unset($query_params['query']);
      $options['fragment'] = '!' . http_build_query($query_params);
    }

    return l($text, $url, $options);
  }

  static function format_class_as_array($class) {
    return is_array($class) ? $class : explode(' ', $class);
  }

}
