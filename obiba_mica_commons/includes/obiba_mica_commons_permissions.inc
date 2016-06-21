<?php

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