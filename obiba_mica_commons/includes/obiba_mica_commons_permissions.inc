<?php

function canEditDraftDocument($document) {
  global $user;
  return $user->uid!==0 // authenticated
    && variable_get_value('mica_enable_to_mica_server_link') //
    && !empty($document) //
    && !empty($document->permissions) //
    && $document->permissions->edit; //
}