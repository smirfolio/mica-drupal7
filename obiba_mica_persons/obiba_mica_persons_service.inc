<?php
/**
 * @file
 * Mica Persons module file
 */

/**
 * Get the person list by studies id (id1+id2+id3...).
 *
 * @param string $studies_id
 */
function obiba_mica_persons_list($studies_id) {
  $persons_resources = new MicaPersonsResource();
  $query_person = "studyMemberships.parentId:($studies_id)";
  $persons = $persons_resources->search($query_person);
  drupal_json_output(array(
    "recordsTotal" => $persons->total,
    "data" => $persons->persons
  ));
}

/**
 * Download a csv file of the person list by studies id (id1+id2+id3...).
 *
 * @param string $studies_id
 */
function obiba_mica_persons_list_csv_download($studies_id) {
  $persons_resources = new MicaPersonsResource();
  $query_person = "studyMemberships.parentId:($studies_id)";
  $response = $persons_resources->download($query_person);
  if (!empty($response)) {
    $headers = $persons_resources->getLastResponseHeaders();
    drupal_add_http_header('Content-Disposition', $headers['Content-Disposition'][0]);
    ob_clean();
    $csv_response = $response->body;
    print $csv_response;
    exit;
  }
}
