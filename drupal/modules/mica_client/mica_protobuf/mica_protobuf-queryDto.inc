<?php

include_once('protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();
include_once('protobuf/protos/Mica.php');

const HEADER_BINARY = 'application/x-protobuf';
const HEADER_JSON = 'application/json';

class QueryDto
{

    function get_list($path, $dtoObj)
    {
        $dtos = array();
        Protobuf::setDefaultCodec(new Protobuf\Codec\Json());
        $data = ws_client_get($path, 'GET', array('Accept' => array(HEADER_JSON)));
        if ($data) {
            foreach (json_decode($data) as $study) {
                $dtos [] = Protobuf::decode($dtoObj, json_encode($study));
            }
        }
        return $dtos;
    }

    function get_detail($path, $dtoObj)
    {
        Protobuf::setDefaultCodec(new Protobuf\Codec\Binary());
        $data = ws_client_get($path, 'GET', array('Accept' => array(HEADER_BINARY)));
        return $data ? Protobuf::decode($dtoObj, $data) : NULL;
    }
}

function ws_client_get($path, $method, $header, $data = NULL)
{
    $url = 'http://localhost:8080/ws/' . $path;

    $post = new HttpClientRequest($url, array(
        'method' => $method, //GET. POST
        'headers' => $header, //array('Content-Type' => array('application/json')),
        'data' => $data,
        'parameters' => array(),
    ));

    try {
        $client = new HttpClient($formatter = FALSE);
        $body = $client->execute($post);
    } catch (HttpClientException $e) {
        if ($e->getCode() == 0) {
            // curl error

            throw new Exception($e->getMessage());
        } elseif (!in_array($e->getCode(), array(200, 201, 202, 203, 204, 205, 206))) {

            throw $e;
        }
        $body = $e->getResponse()->body;
    }
    return $body;
}