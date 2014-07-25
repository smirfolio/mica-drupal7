<?php


function mica_client_dataset_get_datastes() {
  $node_rendred = node_view(node_load(variable_get('dataset_page')));
  return $node_rendred;
}

function mica_client_dataset_get_harmonization_datasets() {
  $output = array('#markup' => 'hellooo word harmonization  dataset');
  return $output;
}

function mica_client_dataset_get_study_datasets() {
  $output = array('#markup' => 'hellooo word study dataset');
  return $output;
}