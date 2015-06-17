<?php
/*
* Copyright (c) 2015 OBiBa. All rights reserved.
*
* This program and the accompanying materials
* are made available under the terms of the GNU Public License v3.0.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

function obiba_mica_data_access_request_list_page() {
  obiba_mica_data_access_requests_datatable_init(array());
  drupal_set_title(t('My Data Access Requests'));
  return theme('obiba_mica_data_access_request-list');
}

function obiba_mica_data_access_request_form_get_config() {
  $mica_client = new MicaDataAccessRequest();
  $config = $mica_client->get_form_definition();
  drupal_json_output($config);
}

function obiba_mica_data_access_requests_action() {
  if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $mica_client = new MicaDataAccessRequests(NULL, 'METHOD_POST');
    $data_access_request = $mica_client->data_access_save(file_get_contents('php://input'), NULL, '/data-access-requests');
    drupal_json_output($data_access_request);
  }

}

function obiba_mica_data_access_request_comments_action($id_data_request) {
  switch ($_SERVER['REQUEST_METHOD']) {
    case 'GET':
      $mica_client = new MicaDataAccessRequestComments(NULL, 'METHOD_GET');
      $data_access_request = $mica_client->get_comments($id_data_request, '/data-access-request');
      drupal_json_output($data_access_request);
      break;

    case 'POST':
      $mica_client = new MicaDataAccessRequestComments(NULL, 'METHOD_POST');
      $data_access_request = $mica_client->save_comment(file_get_contents('php://input'), $id_data_request, '/data-access-request');
      drupal_json_output($data_access_request);
      break;
  }

}

function obiba_mica_data_access_request_comment_action($id_data_request, $comment_id) {

  switch ($_SERVER['REQUEST_METHOD']) {
    case 'PUT':
      $mica_client = new MicaDataAccessRequestComment(NULL, 'METHOD_PUT');
      $data_access_request = $mica_client->save_comment($id_data_request, $comment_id, file_get_contents('php://input'), '/data-access-request');
      drupal_json_output($data_access_request);
      break;

    case 'DELETE':
      $mica_client = new MicaDataAccessRequestComment(NULL, 'METHOD_DELETE');
      $data_access_request = $mica_client->delete_comment($id_data_request, $comment_id, '/data-access-request');
      drupal_json_output($data_access_request);
      break;
  }

}

function obiba_mica_data_access_request_attachment($id_data_request, $id_file) {
  $dataset_resource = new MicaDataAccessRequest(NULL, 'METHOD_GET');
  $responses = $dataset_resource->download_attachment($id_data_request, $id_file);
  if (!empty($responses)) {
    drupal_add_http_header('Content-Disposition', $responses['headers']['Content-Disposition'][0]);
    echo $responses['response']->body;
    flush();
    //stop drupal execution error : 'Headers already sent'
    die();
  }
}

function obiba_mica_data_access_request_download_pdf($id_data_request) {
  if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $dataset_resource = new MicaDataAccessRequest(NULL, 'METHOD_GET');
    $responses = $dataset_resource->download_pdf($id_data_request);
    if (!empty($responses)) {
      drupal_add_http_header('Content-Disposition', $responses['headers']['Content-Disposition'][0]);
      echo $responses['response']->body;
      flush();
      //stop drupal execution error : 'Headers already sent'
      die();
    }
  }
}

function obiba_mica_data_access_request_action($id_data_request) {
  switch ($_SERVER['REQUEST_METHOD']) {
    case 'GET':
      $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_GET');
      $data_access_request = $mica_client->get_request($id_data_request);
      if (empty($data_access_request)) {
        return FALSE;
      }
      drupal_json_output($data_access_request);
      break;
    case 'PUT':
      $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_PUT');
      $data_access_request = $mica_client->data_access_save(file_get_contents('php://input'), $id_data_request, '/data-access-request');
      drupal_json_output($data_access_request);
      break;
    case 'DELETE' :
      obiba_mica_data_access_request_delete_request_access($id_data_request);
      break;
  }

}

function obiba_mica_data_access_request_delete_request_access($id_request) {
  $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_DELETE');
  $data_access_request = $mica_client->delete_request($id_request);
  drupal_json_output($data_access_request);
}

function obiba_mica_data_access_request_update_request($id_request, $status) {
  $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_PUT');
  $data_access_request = $mica_client->status_update_request($id_request, $status);
  drupal_json_output($data_access_request);
}

function obiba_mica_data_access_request_upload_attachment() {
  $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_POST');
  $response = $mica_client->upload_file($_FILES);
  drupal_json_output($response);
}

function obiba_mica_data_access_request_get_attachment($id_file) {
  $mica_client = new MicaDataAccessRequest(NULL, 'METHOD_GET');
  $response = $mica_client->get_file($id_file, 'files/temp');
  drupal_json_output($response);
}