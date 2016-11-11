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


namespace Obiba\ObibaMicaClient\MicaHttpClient;

use Obiba\ObibaMicaClient\MicaClient\DrupalMicaClient as DrupalMicaClient;
use Obiba\ObibaMicaClient\MicaConfigurations as MicaConfig;
use Obiba\ObibaMicaClient\MicaWatchDog as MicaWatchDog;

abstract class AbstractMicaHttpClient {

  const AUTHORIZATION_HEADER = 'Authorization';
  const COOKIE_HEADER = 'Cookie';
  const SET_COOKIE_HEADER = 'Set-Cookie';
  const OBIBA_COOKIE = 'obibaid';
  const MICA_COOKIE = 'micasid';
  const HEADER_BINARY = 'application/octet-stream';
  const HEADER_JSON = 'application/json';
  const HEADER_CSV = 'text/csv';
  const HEADER_EXCEL_SHEET = 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet';
  const HEADER_TEXT = 'text/plain';
  const HEADER_TEXT_HTML = 'text/html';
  const HEADER_APP_HTML_XML = 'application/xhtml+xml';
  const HEADER_APP_XML = 'application/xml;q=0.9';
  const HEADER_IMG_WEB = 'image/webp';
  const HEADER_MIXIN = '*/*;q=0.8';
  const PAGINATE_STUDIES = 0;
  const PAGINATE_VARIABLES = 1;
  const PAGINATE_DATASETS = 2;
  const PAGINATE_NETWORKS = 3;

  public $resource;
  public $micaUrl;
  public $drupalWatchDog;
  public $drupalConfig;
  public $headers = [];
  public $parameters = [];
  public $drupalMicaHttpClient;
  protected $httpType;
  protected $acceptHeaders;
  protected $lastResponse;

  function __construct($micaUrl = NULL) {
    $this->drupalMicaHttpClient = new DrupalMicaClient\DrupalMicaHttpClientFactory();
    $this->drupalWatchDog = new MicaWatchDog\MicaDrupalClientWatchDog();
    $this->drupalConfig = new MicaConfig\MicaDrupalConfig();
    $this->micaUrl = (isset($micaUrl) ? $micaUrl : $this->drupalConfig->MicaGetConfig('mica_url')) . '/ws';
  }

  /**
   * Http GET Query.
   *
   * @param $resource
   * @param $parameters
   * @return $this
   */
  public function httpGet($resource, $parameters = NULL) {
    $this->resource = $resource;
    $this->parameters = !empty($parameters) ? $parameters : NULL;
    $this->httpType = $this->drupalMicaHttpClient->getMicaHttpClientStaticMethod('METHOD_GET');
    return $this;
  }

  /**
   * Http POST query
   * @param $resource
   * @param $parameters
   * @return $this
   */
  public function httpPost($resource, $parameters = NULL) {
    $this->resource = $resource;
    $this->parameters = !empty($parameters) ? $parameters : NULL;
    $this->httpType = $this->drupalMicaHttpClient->getMicaHttpClientStaticMethod('METHOD_POST');
    return $this;
  }

  /**
   * Http DELETE query
   * @param $resource
   * @param $parameters
   * @return $this
   */
  public function httpDelete($resource, $parameters) {
    $this->resource = $resource;
    $this->parameters = !empty($parameters) ? $parameters : NULL;
    $this->httpType = $this->drupalMicaHttpClient->getMicaHttpClientStaticMethod('METHOD_DELETE');
    return $this;
  }

  /**
   * Http PUT query
   * @param $resource
   * @param $parameters
   * @return $this
   */
  public function httpPut($resource, $parameters = NULL) {
    $this->resource = $resource;
    $this->parameters = !empty($parameters) ? $parameters : NULL;
    $this->httpType = $this->drupalMicaHttpClient->getMicaHttpClientStaticMethod('METHOD_PUT');
    return $this;
  }

  /**
   * Perform the http query.
   *
   * @param $data
   * @return $this
   */
  public function send($parameters = NULL, $ajax = NULL) {
    $url = $this->micaUrl . $this->resource;
    $requestOptions = array(
      'method' => $this->httpType,
      'headers' => $this->headers,
    );
    if (!empty($parameters)) {
      $requestOptions = array_merge_recursive($requestOptions, $parameters);
    }
    $request = $this->drupalMicaHttpClient->getMicaHttpClientRequest($url, $requestOptions);
    $client = $this->client();
    try {
      $dataResponse = $client->execute($request);
      $this->lastResponse = $client->lastResponse;
      if ($ajax) {
        $headers = $this->httpGetLastResponseHeaders();
        if (!empty($headers) && !empty($headers['Location'])) {
          $this->drupalMicaHttpClient->micaClientAddHttpHeader('Location', $headers['Location'][0]);
        }
        $this->drupalMicaHttpClient->micaClientAddHttpHeader('Status', $this->httpGetLastResponseStatusCode());
     //   return $this->lastResponse->body;
      }
      return $dataResponse;
    } catch (\HttpClientException $e) {
      $this->drupalWatchDog->MicaWatchDog('MicaClient', 'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ), $this->drupalWatchDog->MicaWatchDogSeverity('WARNING'));
      $this->lastResponse = $client->lastResponse;
      unset($this->dataResponse);
      if ($ajax) {
        $this->drupalMicaHttpClient->micaClientAddHttpHeader('Status', $e->getCode());
        return json_encode(array(
          'code' => $e->getCode(),
          'message' => $e->getMessage(),
        ));
      }
      else {
        $message_parameters['message'] = 'Connection to server fail,  Error serve code : @code, message: @message';
        $message_parameters['placeholders'] = array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage()
        );
        $message_parameters['severity'] = 'error';
        if ($e->getCode() == 500 || $e->getCode() == 503 || $e->getCode() == 0) {
          DrupalMicaClient\MicaClient::DrupalMicaErrorHandler(TRUE, $message_parameters);
        }
        drupal_set_message(t($message_parameters['message'], $message_parameters['placeholders']), $message_parameters['severity']);
      }
    }
    return NULL;
  }

  static function acceptHeaderArray($acceptType) {
    $acceptTypeHeaders = $acceptType;
    if (is_array($acceptType)) {
      $acceptTypeHeaders = array_map(function ($type) {
        $types = [];
        if (is_array($type)) {
          $types = array_map(function ($item) {
            return self::getRequestConst($item);
          }, $type);
          return implode(', ', $types);
        }
        else {
          return self::getRequestConst($type);
        }
      }, $acceptType);
      return $acceptTypeHeaders;
    }
    return array(self::getRequestConst($acceptTypeHeaders));
  }

  static public function getRequestConst($type) {
    return constant("self::$type");
  }

  /**
   * The client object construction overriding the httpClient->client() method.
   *
   * @return object
   *   The overridden object.
   */
  protected function client() {
    $default_headers_setter = function ($request) {
      $request->setHeader('Accept-Encoding', 'gzip, deflate');
    };
    $client = $this->drupalMicaHttpClient->getMicaHttpClient(FALSE, FALSE, $default_headers_setter);
    if (!isset($client->options['curlopts'])) {
      $client->options['curlopts'] = array();
    }
    $client->options['curlopts'] += array(
      CURLOPT_SSL_VERIFYHOST => FALSE,
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_ENCODING => TRUE,
    );
    return $client;
  }

  /**
   * Get the file extension from file resource.
   *
   * @param string $file_resource
   *   The file name.
   *
   * @return string
   *   The file extension.
   */
  protected function getFileExtension($file_resource) {
    $file_array = explode('.', $file_resource);
    $extension_file = count($file_array);

    return $file_array[$extension_file - 1];
  }

  /**
   * Perform the http query.
   *
   * @return $this
   */
  public function download() {
    $url = $this->micaUrl . $this->resource;
    $requestOptions = array(
      'method' => $this->httpType,
      'headers' => $this->headers,
    );
    $request = $this->drupalMicaHttpClient->getMicaHttpClientRequest($url, $requestOptions);
    $client = $this->client();
    try {
      $data = $client->execute($request);
      $this->HttpSetLastResponse($client->lastResponse);
      $file_name = $this->HttpGetPropertyValueFromHeaderArray($this->HttpParseHeaders($client->lastResponse->headers),
        'filename',
        'Content-Disposition'
      );

      $raw_data = array(
        'extension' => $this->getFileExtension($file_name),
        'data' => $data,
        'filename' => $file_name,
        'raw_header_array' => $this->HttpParseHeaders($client->lastResponse->headers),
      );
      return $raw_data;
    } catch (\HttpClientException $e) {
      $this->drupalWatchDog->MicaWatchDog(
        'MicaClient',
        'Connection to server fail,  Error serve code : @code, message: @message',
        array(
          '@code' => $e->getCode(),
          '@message' => $e->getMessage(),
        ),
        $this->drupalWatchDog->MicaWatchDogSeverity('WARNING'));
      return $raw_data = array(
        'code' => $e->getCode(),
        'message' => $e->getMessage(),
      );
    }
  }

  /**
   * Set some http headers.
   *
   * @param $headers
   * @return $this
   */
  public function httpSetHeaders($headers) {
    foreach ($this->headers as $keyHeader => $valueHeader) {
      if (key($headers) == $keyHeader) {
        return $this;
      }
    }
    $this->headers = array_merge($this->headers, $headers);
    return $this;
  }

  /**
   * Set Accept  http headers.
   *
   * @param $acceptType
   * @return $this
   */
  public function httpSetAcceptHeaders($acceptType) {
    $this->httpSetHeaders(array('Accept' => $acceptType));
    return $this;
  }

  /**
   * Set Accept  http headers.
   *
   * @param $acceptType
   * @return $this
   */
  public function httpSetContentTypeHeaders($acceptType) {
    $this->httpSetHeaders(array('Content-Type' => $acceptType));
    return $this;
  }

  /**
   * Add authorization by cookies header.
   *
   * @param string $obibaId
   *   The obibaid cookie id.
   * @param string $micaId
   *   The micaid cookie id.
   *
   * @return string
   *   The Value of the cooke.
   */
  protected function HttpCookieHeaderValue($obibaId = NULL, $micaId = NULL) {
    $cookie_parts = array();

    if (isset($obibaId)) {
      $cookie_parts[] = self::OBIBA_COOKIE . '=' . $obibaId;
    }

    if (isset($micaId)) {
      $cookie_parts[] = self::MICA_COOKIE . '=' . $micaId;
    }

    return implode("; ", $cookie_parts);
  }

  /**
   * Add the cookie Id/value to the header.
   *
   * @param string $obibaId
   *   The obibaid cookie id.
   * @param string $micaId
   *   The micaid cookie id.
   *
   * @return array
   *   The transformed initial headers.
   */
  protected function httpUpdateCookieHeaders($obibaId = NULL, $micaId = NULL) {
    $cookie = $this->HttpCookieHeaderValue($obibaId, $micaId);
    if (isset($this->headers[self::COOKIE_HEADER])) {
      array_push($this->headers[self::COOKIE_HEADER], $cookie);
    }
    else {
      $this->headers[self::COOKIE_HEADER] = array($cookie);
    }
    return $this;
  }

  /**
   * Add authorization headers.
   *
   * @return array
   *   The transformed initial headers.
   */
  public function httpAuthorizationHeader() {

    if (isset($_SESSION[self::OBIBA_COOKIE])) {
      // Authenticate by cookies coming from request (case of regular user
      // logged in via Agate).
      $this->drupalWatchDog->MicaWatchDog('obiba_mica', 'Auth by cookies from request');
      $this->httpUpdateCookieHeaders($_SESSION[self::OBIBA_COOKIE],
        isset($_SESSION[self::MICA_COOKIE]) ?
          $_SESSION[self::MICA_COOKIE] : NULL);
    }
    else {
      $this->drupalWatchDog->MicaWatchDog('obiba_mica', 'Auth by anonymous credentials');
      $current_anonymous_pass = $this->drupalConfig->MicaGetConfig('mica_anonymous_password');
      $saved_anonymous_pass = $this->drupalConfig->MicaGetConfig('mica_anonymous_password_saved');

      // always append credentials in case of mica session has expired
      $credentials = $this->drupalConfig->MicaGetConfig('mica_anonymous_name') . ':' . $current_anonymous_pass;
      $this->httpSetHeaders(array(
        self::AUTHORIZATION_HEADER => array(
          'Basic ' . base64_encode($credentials),
        )
      ));
      // detect if anonymous password was changed
      if ($current_anonymous_pass == $saved_anonymous_pass) {
        if (isset($_SESSION[self::MICA_COOKIE])) {
          $this->httpUpdateCookieHeaders(NULL,
            $_SESSION[self::MICA_COOKIE]);
        }
      }
      else {
        session_unset();
        $this->drupalConfig->MicaSetConfig('mica_anonymous_password_saved',
          $this->drupalConfig->MicaGetConfig('mica_anonymous_password'));
      }
    }
    return $this;
  }

  /**
   * Return the value of a given key header attribute  (filename, charset).
   *
   * ToDo may be need to be extended to retrieve more attributes(User-Agent,..).
   *
   * @param array $header
   *   The header to parse.
   * @param string $property
   *   The property to find.
   * @param string $attribute
   *   The attribute.
   *
   * @return string
   *   The value of property.
   */
  protected function HttpGetPropertyValueFromHeaderArray(array $header, $property, $attribute = NULL) {
    if (!empty($attribute)) {
      return $this->HttpParseHeader($header[$attribute], $property);
    }
    else {
      foreach ($header as $attributes) {
        $find_property_value = $this->HttpParseHeader($attributes, $property);
        if (!empty($find_property_value)) {
          return $find_property_value;
        }
      }
    }
    return NULL;
  }

  /**
   * Get property by given attribute.
   *
   * @param string $attribute
   *   The Attribute to get.
   * @param string $property
   *   The property.
   *
   * @return string
   *   The property value.
   */
  protected function HttpParseHeader($attribute, $property) {
    $attributes_array = explode(';', $attribute);
    foreach ($attributes_array as $property_string) {
      if (strstr($property_string, $property)) {
        return $property_value = str_replace('"', '', explode('=', $property_string)[1]);
      }
    }
    return FALSE;
  }

  /**
   * Parse a string header response and return an key/value array attributes.
   *
   * @param string $raw_headers
   *   The raw header.
   *
   * @return array
   *   The parsed header on an array.
   */
  protected function HttpParseHeaders($raw_headers) {
    $headers = [];

    foreach (explode("\n", $raw_headers) as $i => $h) {
      $h = explode(':', $h, 2);

      if (isset($h[1])) {
        $headers[$h[0]] = trim($h[1]);
      }
    }
    return $headers;
  }

  /**
   * Forwards the 'Set-Cookie' directive(s) to the drupal client.
   *
   * If the user was authenticated by Agate.
   */
  private function httpSetLastResponseCookies() {
    foreach ($this->httpGetLastResponseHeader(self::SET_COOKIE_HEADER) as $cookie_str) {
      $cookie = $this->HttpParseCookie($cookie_str);
      $keys = array_keys($cookie);
      $name = $keys[0];
      $value = $cookie[$name];
      $this->drupalWatchDog->MicaWatchDog('Mica Client',
        'Cookie: name=@name, value=@value',
        array('@name' => $name, '@value' => $value),
        $this->drupalWatchDog->MicaWatchDogSeverity('DEBUG'));
      if (empty($value)) {
        if (!empty($_SESSION[$name])) {
          unset($_SESSION[$name]);
        }
      }
      else {
        $_SESSION[$name] = $value;
      }
    }
  }


  /**
   * Set the last response cookies after a http call.
   *
   * @param array $last_response
   *   The server response.
   */
  protected function HttpSetLastResponse($last_response) {
    $this->lastResponse = $last_response;
    if (isset($last_response)) {
      $this->HttpSetLastResponseCookies();
    }
  }

  /**
   * Get the last response (if any).
   *
   * @return array
   *   The response server formatted as an array.
   */
  protected function httpGetLastResponse() {
    return $this->lastResponse;
  }

  /**
   * Get the last reposnse status code
   *
   * @return
   *   The status code
   */
  function httpGetLastResponseStatusCode() {
    if ($this->lastResponse != NULL) {
      return $this->lastResponse->responseCode;
    }
    return NULL;
  }

  /**
   * Get the last response headers (if any).
   *
   * @return array
   *   The header response server.
   */
  function httpGetLastResponseHeaders() {
    if ($this->lastResponse) {
      return $this->HttpGetHeaders($this->lastResponse->headers);
    }

    return array();
  }

  /**
   * Get a set of headers
   * @param $headers
   * @return mixed
   */
  function httpGetHeaders($headers) {
    if ($headers != NULL) {
      $result = array();
      foreach (explode("\r\n", $headers) as $header) {
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
    return array();
  }

  /**
   * Get the header value(s) from the last response.
   *
   * @param string $header_name
   *   The header information to extract.
   *
   * @return array
   *   The value of header name.
   */
  function httpGetLastResponseHeader($header_name) {
    $headers = $this->HttpGetLastResponseHeaders();

    if (array_key_exists($header_name, $headers)) {
      return $headers[$header_name];
    }
    return array();
  }

  /**
   * Add the cookie Id/value to the header.
   *
   * @param array $headers
   *   The server response header.
   * @param string $obibaid
   *   The obibaid cookie id.
   * @param string $micasid
   *   The micaid cookie id.
   *
   * @return array
   *   The transformed initial headers.
   */
  function httpAddCookieHeader(array $headers, $obibaid, $micasid) {
  }

  /**
   * Explode a cookie string in a array.
   *
   * @param string $cookie_str
   *   The cookie string.
   *
   * @return array
   *   The cookie array.
   */
  function httpParseCookie($cookie_str) {
    $cookie = array();
    foreach (explode(';', $cookie_str) as $entry_str) {
      if (strpos($entry_str, '=')) {
        $entry = explode('=', $entry_str);
        $cookie[$entry[0]] = $entry[1];
      }
      else {
        $cookie[$entry_str] = TRUE;
      }
    }
    return $cookie;
  }

  /**
   * GEt the setting of the samll page size response (for pagination).
   *
   * @return int
   *   The page size.
   */
  function httpGetResponsePageSizeSmall() {
  }

  /**
   * GEt the setting of the page size response (for pagination).
   *
   * @return int
   *   The page size.
   */
  static function httpGetResponsePageSize() {
  }

}