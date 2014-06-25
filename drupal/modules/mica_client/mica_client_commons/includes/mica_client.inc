<?php

/**
 * @file
 * AgateClient class
 */

$path_module_protobuf = drupal_get_path('module', 'obiba_protobuf');
$path_module_protos = drupal_get_path('module', 'mica_client_model');

include_once($path_module_protobuf . '/protobuf/Protobuf.php');
use \DrSlump\Protobuf;

Protobuf::autoload();

include_once($path_module_protos . '/protos/Mica.php');

/**
 * Class MicaClient
 */
class MicaClient {

  const AUTHORIZATION_HEADER = 'Authorization';

  const COOKIE_HEADER = 'Cookie';

  const SET_COOKIE_HEADER = 'Set-Cookie';

  const OBIBA_COOKIE = 'obibaid';

  const MICA_COOKIE = 'micasid';

  const HEADER_BINARY = 'application/x-protobuf';

  const HEADER_JSON = 'application/json';

  protected $micaUrl;

  private $lastResponse;

  /**
   * Mica client from a given url or from the one retrieved from 'mica_url' variable.
   * @param null $mica_url
   */
  public function __construct($mica_url = NULL) {
    $this->micaUrl = (isset($mica_url) ? $mica_url : variable_get_value('mica_url')) . '/ws';
  }

  /**
   * Get the last response (if any).
   * @return mixed
   */
  public function getLastResponse() {
    return $this->lastResponse;
  }

  /**
   * Set the last response after a http call.
   * @param $lastResponse
   */
  protected function setLastResponse($lastResponse) {
    $this->lastResponse = $lastResponse;
    if (isset($lastResponse)) {
      $this->setLastResponseCookies();
    }
  }

  /**
   * Get the last response headers (if any).
   * @return array
   */
  protected function getLastResponseHeaders() {
    if ($this->lastResponse != NULL) {
      $result = array();
      foreach (explode("\r\n", $this->lastResponse->headers) as $header) {
        $h = explode(":", $header, 2);
        if (count($h) == 2) {
          if (!array_key_exists($h[0], $result)) {
            $result[$h[0]] = array();
          }
          array_push($result[$h[0]], trim($h[1]));
        }
      }
      return $result;
    }
    return '';
  }

  /**
   * Get the header value(s) from the last response.
   * @param $header_name
   * @return array
   */
  protected function getLastResponseHeader($header_name) {
    $headers = $this->getLastResponseHeaders();

    if (array_key_exists($header_name, $headers)) {
      return $headers[$header_name];
    }
    return array();
  }

  /**
   * Forwards the 'Set-Cookie' directive(s) to the drupal client if the user was authenticated by Agate.
   */
  private function setLastResponseCookies() {
    foreach ($this->getLastResponseHeader(self::SET_COOKIE_HEADER) as $cookie_str) {
      $cookie = $this->parseCookie($cookie_str);
      $keys = array_keys($cookie);
      $name = $keys[0];
      $value = $cookie[$name];
      $expire = isset($cookie['Max-Age']) ? time() + intval($cookie['Max-Age']) : 0;
      $path = isset($cookie['Path']) ? $cookie['Path'] : '/';
      $domain = isset($cookie['Domain']) ? $cookie['Domain'] : NULL;

      if (isset($_COOKIE[self::OBIBA_COOKIE])) {
        // forwards cookies to client if not anonymous user
        setcookie($name, $value, $expire, $path, $domain);
      }
      $_SESSION[$name] = $value;
    }
  }

  /**
   * Add authorization headers
   * @param array $headers
   * @return array
   */
  protected function authorizationHeader(array $headers) {
    if (isset($_COOKIE[self::OBIBA_COOKIE])) {
      // authenticate by cookies coming from request (case of regular user logged in via Agate)
      $obibaid = $_COOKIE[self::OBIBA_COOKIE];
      $micasid = isset($_COOKIE[self::MICA_COOKIE]) ? $_COOKIE[self::MICA_COOKIE] : NULL;
      $cookie = $this->cookieHeaderValue($obibaid, $micasid);

      if (isset($headers[self::COOKIE_HEADER])) {
        array_push($headers[self::COOKIE_HEADER], $cookie);
      }
      else {
        $headers[self::COOKIE_HEADER] = array($cookie);
      }
    } else if (isset($_SESSION[self::OBIBA_COOKIE])) {
      // authenticate by cookies coming from session (case of anonymous user logged in via Agate)
      $obibaid = $_SESSION[self::OBIBA_COOKIE];
      $micasid = isset($_SESSION[self::MICA_COOKIE]) ? $_SESSION[self::MICA_COOKIE] : NULL;
      $cookie = $this->cookieHeaderValue($obibaid, $micasid);

      if (isset($headers[self::COOKIE_HEADER])) {
        array_push($headers[self::COOKIE_HEADER], $cookie);
      }
      else {
        $headers[self::COOKIE_HEADER] = array($cookie);
      }
    } else {
      // authenticate by anonymous credentials
      $credentials = variable_get_value('mica_anonymous_name') . ':' . variable_get_value('mica_anonymous_password');
      $headers[self::AUTHORIZATION_HEADER] = array('Basic ' . base64_encode($credentials));
    }

    return $headers;
  }

  /**
   * Add authorization by cookies header.
   * @param array $headers
   * @param $obibaid
   * @param $micasid
   * @return string
   */
  private function cookieHeaderValue($obibaid, $micasid) {
    $cookie = self::OBIBA_COOKIE . '=' . $obibaid;

    if (isset($micasid)) {
      $cookie = $cookie . '; ' . self::MICA_COOKIE . '=' . $micasid;
    }

    return $cookie;
  }

  /**
   * Explode a cookie string in a array.
   * @param $cookie_str
   * @return array
   */
  private function parseCookie($cookie_str) {
    $cookie = array();
    foreach (explode(';', $cookie_str) as $entry_str) {
      $entry = explode('=', $entry_str);
      $cookie[$entry[0]] = $entry[1];
    }
    return $cookie;
  }

  /**
   * @return HttpClient
   */
  protected function client() {
    $client = new HttpClient($formatter = FALSE);

    if (!isset($client->options['curlopts'])) {
      $client->options['curlopts'] = array();
    }

    $client->options['curlopts'] += array(
      CURLOPT_SSLVERSION => 3,
      CURLOPT_SSL_VERIFYHOST => FALSE,
      CURLOPT_SSL_VERIFYPEER => FALSE
    );

    Protobuf::setDefaultCodec(new Protobuf\Codec\Json());

    return $client;
  }
}