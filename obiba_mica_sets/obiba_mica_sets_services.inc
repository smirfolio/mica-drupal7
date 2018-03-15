<?php
/**
 * Copyright (c) 2018 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * Create a set by importing (possibly empty) a list of identifiers.
 */
function obiba_mica_sets_import($document_type = 'variables') {
  $resource = new ObibaSetsResources();
  $body = file_get_contents('php://input');
  $result = $resource->createSet($document_type, $body);
  drupal_json_output($result);
}

/**
 * Get a set.
 */
function obiba_mica_sets_set($document_type = 'variables', $set_id) {
  $resource = new ObibaSetsResources();
  $result = $resource->getSet($document_type, $set_id);
  drupal_json_output($result);
}

/**
 * Check a identifiers is in a set.
 */
function obiba_mica_sets_set_document_exists($document_type = 'variables', $set_id, $document_id) {
  $resource = new ObibaSetsResources();
  $result = $resource->existsInSet($document_type, $set_id, $document_id);
  drupal_json_output($result);
}

/**
 * Importing a list of identifiers in a set.
 */
function obiba_mica_sets_set_documents_import($document_type = 'variables', $set_id) {
  $resource = new ObibaSetsResources();
  $body = file_get_contents('php://input');
  $result = $resource->importSet($document_type, $set_id, $body);
  drupal_json_output($result);
}

/**
 * Remove a list of identifiers from a set.
 */
function obiba_mica_sets_set_documents_remove($document_type = 'variables', $set_id) {
  $resource = new ObibaSetsResources();
  $body = file_get_contents('php://input');
  $result = $resource->removeFromSet($document_type, $set_id, $body);
  drupal_json_output($result);
}

/**
 * Get the list of identifiers from a set.
 */
function obiba_mica_sets_set_documents_list($document_type = 'variables', $set_id, $from = 0, $limit = 10) {
  $resource = new ObibaSetsResources();
  $result = $resource->listSet($document_type, $set_id, $from, $limit);
  drupal_json_output($result);
}

/**
 * Clear the list of identifiers from a set.
 */
function obiba_mica_sets_set_documents_clear($document_type = 'variables', $set_id) {
  $resource = new ObibaSetsResources();
  $result = $resource->clearSet($document_type, $set_id);
  drupal_json_output($result);
}