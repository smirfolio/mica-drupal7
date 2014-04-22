<?php

include_once('protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();
include_once('protobuf/protos/Mica.php');

const HEADER_BINARY = 'application/x-protobuf';
const HEADER_JSON = 'application/json';

class QueryDto {

  function get_list($path, $dtoObj) {
    $dtos = array();
    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
    $output = restclient_get($path, array('headers' => array('Accept' => HEADER_JSON)));
    if ($output) {
      foreach (json_decode($output->data) as $study) {
        $dtos [] = Protobuf::decode($dtoObj, json_encode($study));
      }
    }
    return $dtos;
  }

  function get_detail($path, $dtoObj) {
    Protobuf::setDefaultCodec(new Protobuf\Codec\Binary());
    $output = restclient_get($path, array('headers' => array('Accept' => HEADER_BINARY)));
    return $output ? Protobuf::decode($dtoObj, $output->data) : NULL;
  }
}