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
    $mica_file = new MicaFilesResource();
    $raw_data = $mica_file->downloadAttachmentFile($_POST['file_path'], $file_name);
    if (!empty($raw_data) && empty($raw_data['code'])) {
      drupal_add_http_header('Content-Type', $raw_data['raw_header_array']['Content-Type']);
      drupal_add_http_header('Content-Disposition', $raw_data['raw_header_array']['Content-Disposition']);
      ob_clean();
      print $raw_data['data'];
      exit;
    }
    else {
      drupal_set_message(t('An error occurred downloading file, server response code : @code, Server message: "@message"',
        array(
          '@code' => $raw_data['code'],
          '@message' => $raw_data['message'],
        )
      ),
        'error');
      drupal_goto('mica/' . $entity_type . '/' . $entity_id);

    }
}