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
include_once($path_module_protos . '/protos/MicaSearch.php');

/**
 * Class MicaClient
 */
class MicaClient {
  const child = \obiba\mica\ParentChildFilterDto\Relationship::CHILD;
  const parent = \obiba\mica\ParentChildFilterDto\Relationship::PARENT;
  const AUTHORIZATION_HEADER = 'Authorization';

  const COOKIE_HEADER = 'Cookie';

  const SET_COOKIE_HEADER = 'Set-Cookie';

  const OBIBA_COOKIE = 'obibaid';

  const MICA_COOKIE = 'micasid';

  const HEADER_BINARY = 'application/x-protobuf';

  const HEADER_JSON = 'application/json';

  const SIZE_RESPONSE = 30;

  const PAGINATE_study = 0;
  const PAGINATE_variable = 1;
  const PAGINATE_dataset = 2;

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
   * Forwards the 'Set-Cookie' directive to the drupal client.
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

      setcookie($name, $value, $expire, $path, $domain);
      $_SESSION[$name] = $value;
    }
  }

  /**
   * Add authorization headers
   * @param array $headers
   * @return array
   */
  protected function authorizationHeader(array $headers) {
    // was logged in via Agate
    if (isset($_COOKIE[self::OBIBA_COOKIE])) {
      // authenticate by cookie
      $cookie = self::OBIBA_COOKIE . '=' . $_COOKIE[self::OBIBA_COOKIE];

      if (isset($_COOKIE[self::MICA_COOKIE])) {
        $cookie = $cookie . '; ' . self::MICA_COOKIE . '=' . $_COOKIE[self::MICA_COOKIE];
      }

      if (isset($headers[self::COOKIE_HEADER])) {
        array_push($headers[self::COOKIE_HEADER], $cookie);
      }
      else {
        $headers[self::COOKIE_HEADER] = array($cookie);
      }
    }
    else {
      // authenticate by credentials
      $credentials = variable_get_value('mica_anonymous_name') . ':' . variable_get_value('mica_anonymous_password');
      $headers[self::AUTHORIZATION_HEADER] = array('Basic ' . base64_encode($credentials));
    }

    return $headers;
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


  protected function session_facets_builder($aggregations, $dto_type, $request_param = NULL) {
    if (!empty($aggregations->totalHits)) {
      $_SESSION[$dto_type]['aggregations'] = $aggregations->aggs;
      $_SESSION[$dto_type]['aggregations']['totalHits'] = $aggregations->totalHits;
      $_SESSION[$dto_type]['request'] = !empty($request_param) ? $request_param : NULL;

    }
  }

  protected function normalize_parameters($request_param) {
    $requestArry = explode('&', $request_param);

    $formated_term = array();
    foreach ($requestArry as $term_association) {
      $term = explode('=', $term_association);
      if (!empty($term[1])) {
        $decoded_term = urldecode($term[0]);
        $formated_term[preg_replace('/\[[^\]]*\]/', '', $decoded_term)][] = $term[1];
      }
    }
    return $formated_term;
  }

  protected function pagination_parameters($current_page = NULL, $dto_type = NULL) {
    $nb_pages = ceil($_SESSION[strtolower($dto_type)]['aggregations']['totalHits'] / $this::SIZE_RESPONSE);
    if (!empty($current_page)) {
      $pageActuelle = intval($current_page);
      if ($pageActuelle > $nb_pages) // Si la valeur de $pageActuelle (le numéro de la page) est plus grande que $nombreDePages...
      {
        $pageActuelle = $nb_pages;
      }
    }
    else {
      $pageActuelle = 1; // La page actuelle est la n°1
    }
    $premiereEntree = ($pageActuelle) * $this::SIZE_RESPONSE; // On calcul la première entrée à lire
    return $premiereEntree;
  }

  /*
   * Dto filter construction
   * @param $request_param: url passed parameters,
   * @param $spec_dto_param: specific  passed parameters,
   * @param $parent_child: array must be 'parent'=>'<entity parent>' or 'child'=>'<entity parent>',
   * @param $type_dto_search: must be 'Study' or 'Dataset',
   *
   * */
  protected function dto_filter_construct($request_param = NULL, $parent_child = NULL, $type_dto_search = NULL, $spec_dto_params = NULL) {
//    dpm($parent_child);
    // dpm($type_dto_search);
    $query_dto = new \obiba\mica\QueryDto;
    $filtered_query_dto = new \obiba\mica\FilteredQueryDto;
    $bool_filter_query_dto = new \obiba\mica\BoolFilterQueryDto;
    if (!empty($parent_child)) {
      $parent_filtered_query_dto = new \obiba\mica\FilteredQueryDto;
      $parent_bool_filter_query_dto = new \obiba\mica\BoolFilterQueryDto;
    }
    if (!empty($spec_dto_params)) {
      foreach ($spec_dto_params as $spec_dto_param) {
        foreach ($spec_dto_param['terms'] as $term_value) {
          $dto_spec_query_term = new \obiba\mica\TermsQueryDto;
          $dto_spec_query_term->setField($spec_dto_param['field']);
          $dto_spec_query_term->setValues($term_value);
          $bool_filter_query_dto->addTerms($dto_spec_query_term);
        }
      }
    }
    if (!empty($request_param)) {
      foreach ($this->normalize_parameters(urldecode($request_param)) as $field => $term_association) {
        if ($field != 'page') {
          if (strpos($field, key($parent_child)) === FALSE) {
            foreach ($term_association as $term) {
              $parent_child_field = explode(':', urldecode($field));
              $dto_guery_term = new \obiba\mica\TermsQueryDto;
              $dto_guery_term->setField(str_replace('-', '.', $parent_child_field[1]));
              $dto_guery_term->setValues(str_replace($parent_child_field[1] . '.', '', $term));
              $bool_filter_query_dto->addTerms($dto_guery_term);
            }
          }
          else {
            foreach ($term_association as $term) {
              $parent_child_field = explode(':', urldecode($field));
              $parent_child_dto_guery_term = new \obiba\mica\TermsQueryDto;
              $parent_child_dto_guery_term->setField(str_replace('-', '.', $parent_child_field[1]));
              $parent_child_dto_guery_term->setValues(str_replace($parent_child_field[1] . '.', '', $term));
              $parent_bool_filter_query_dto->addTerms($parent_child_dto_guery_term);
            }
            if (!empty($parent_bool_filter_query_dto) && !empty($parent_bool_filter_query_dto)) {
              $parent_query_dto = new \obiba\mica\ParentChildFilterDto;
              $parent_query_dto->setRelationship(constant("MicaClient::" . key($parent_child)));
              $parent_query_dto->setType($parent_child[key($parent_child)]);
              $parent_filtered_query_dto->setFilter($parent_bool_filter_query_dto);
              $parent_query_dto->setFilteredQuery($parent_filtered_query_dto);
            }
          }
        }
        if ($field == 'page') {
          $pagination_param = explode(',', $term_association[0]);
          if (array_count_values($pagination_param)[0] == constant("MicaClient::PAGINATE_" . $type_dto_search)) {
            $query_dto->setFrom($this->pagination_parameters($pagination_param[1], $type_dto_search));
          }
        }

      }
    }

    if (!empty($parent_query_dto)) {
      $bool_filter_query_dto->setParentChildFilter($parent_query_dto);
    }

    $filtered_query_dto->setFilter($bool_filter_query_dto);

    $query_dto->setFilteredQuery($filtered_query_dto);

    $query_dto->setSize($this::SIZE_RESPONSE);
    $query_dto->detailed = FALSE;

    $json_query_encoded = Protobuf::encode($query_dto);
    return $json_query_encoded;
  }

}