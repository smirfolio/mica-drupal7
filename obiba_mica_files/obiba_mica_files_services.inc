<?php
/**
 * @file
 * Mica Files module file
 */

/**
 * Download the attachments.
 *
 * @param string $entity_type
 *   The entity type containing attachments.
 * @param string $entity_id
 *   The entity id.
 * @param string $file_resource_id
 *   The file resource id.
 */
function obiba_mica_files_download_attachment($entity_id, $entity_type, $file_name) {
  _obiba_mica_files_download_attachment($entity_id, $entity_type, $_POST['file_path'], $file_name, FALSE);
}

function obiba_mica_files_get_file() {
  $mica_file = new MicaFilesResource();
  drupal_json_output(json_decode($mica_file->getFile(drupal_get_query_parameters()['path'])));
}

function obiba_mica_files_search_files() {
  $query_params = drupal_get_query_parameters();
  $mica_file = new MicaFilesResource();
  $path = $query_params['path'];
  unset($query_params['path']);
  drupal_json_output(json_decode($mica_file->searchFiles($path, $query_params)));
}

function  obiba_mica_file_download() {
  $path = drupal_get_query_parameters()['path'];
  $inline = drupal_get_query_parameters()['inline'];


  $file_path = dirname($path);
  $file_name = basename($path);
  _obiba_mica_files_download_attachment(NULL, NULL, $file_path, $file_name, empty($inline) ? 'false' : $inline);
}

/**
 * Download the attachments.
 *
 * @param string $entity_type
 *   The entity type containing attachments.
 * @param string $entity_id
 *   The entity id.
 * @param string $file_resource_id
 *   The file resource id.
 */
function _obiba_mica_files_download_attachment($entity_id, $entity_type, $file_path, $file_name, $inline) {
  $mica_file = new MicaFilesResource();
  $raw_data = $mica_file->downloadAttachmentFile($file_path, $file_name, $inline);
  if (!empty($raw_data) && empty($raw_data['code'])) {
    drupal_add_http_header('Content-Type',
      $raw_data['raw_header_array']['Content-Type']);
    drupal_add_http_header('Content-Disposition',
      $raw_data['raw_header_array']['Content-Disposition']);
    ob_clean();
    print $raw_data['data'];
    exit;
  }
  else {
    drupal_set_message(t('An error occurred downloading file,
      server response code : @code, Server message: "@message"',
      array(
        '@code' => $raw_data['code'],
        '@message' => $raw_data['message'],
      )
    ),
      'error');

    if (!empty($entity_type) && !empty($entity_id)) {
      drupal_goto('mica/' . $entity_type . '/' . $entity_id);
    }
  }
}