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

function obiba_mica_data_access_request_ng_list() {
  $mica_client = new MicaDataAccessRequestResource();
  $data_access_list = $mica_client->get_data_access_list();
  dpm($data_access_list);
  drupal_json_output($data_access_list);
}