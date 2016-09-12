<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

function canEditDraftDocument($document) {
  global $user;
  return $user->uid!==0 // authenticated
    && variable_get_value('mica_enable_to_mica_server_link') //
    && !empty($document) //
    && !empty($document->permissions) //
    && $document->permissions->edit; //
}

function obiba_mica_user_has_role($role) {
  global $user;
  return in_array($role, $user->roles);
}