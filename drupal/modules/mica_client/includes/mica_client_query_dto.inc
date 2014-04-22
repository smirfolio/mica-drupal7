<?php

include_once('protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();
const HEADER_BINARY = 'application/x-protobuf';
const HEADER_JSON = 'application/json';
include_once('protobuf/protos/Mica.php');

class queryDto
{
    function get_list($path, $dtoObj)
    {
        $studiesDto = array();
        Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
        $output = restclient_get($path, array('headers' => array('Accept' => HEADER_JSON)));
        foreach (json_decode($output->data) as $study) {
            $studiesDto [] = Protobuf::decode($dtoObj, json_encode($study));

        }
        return $studiesDto;
    }

    function get_detail($path, $dtoObj)
    {
        Protobuf::setDefaultCodec(new Protobuf\Codec\Binary());
        $output = restclient_get($path, array('headers' => array('Accept' => HEADER_BINARY)));
        $studyDto = Protobuf::decode($dtoObj, $output->data);

        return $studyDto;
    }
}