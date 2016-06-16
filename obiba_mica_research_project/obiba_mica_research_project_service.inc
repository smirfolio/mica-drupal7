<?php

/**
 * @file
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Get the research project form config
 */
function obiba_mica_project_form_get_config() {
  $mica_client = new MicaResearchProjectResource(NULL);
  $config = $mica_client->getFormDefinition();
  drupal_json_output($config);
}