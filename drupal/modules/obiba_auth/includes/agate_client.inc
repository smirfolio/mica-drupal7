<?php

/**
 * @file
 * AgateClient class
 */
class AgateClient
{
    private $agateUrl;

    private $applicationName;

    private $applicationKey;

    private $lastResponse;

    public function __construct($agate_url, $application_name, $application_key)
    {
        $this->agateUrl = $agate_url . '/ws';
        $this->applicationName = $application_name;
        $this->applicationKey = $application_key;
    }

    /**
     * Get the last response (if any).
     * @return mixed
     */
    public function getLastResponse() {
        return $this->lastResponse;
    }

    /**
     * Get the last response headers (if any).
     * @return array
     */
    public function getLastResponseHeaders() {
        if ($this->lastResponse != null) {
            return $this->lastResponse->headers;
        }
        return array();
    }

    /**
     * Perform authentication by user name.
     * @param $username
     * @param $password
     * @return bool
     * @throws Exception
     */
    public function authenticate($username, $password)
    {
        $this->lastResponse = null;
        $url = $this->agateUrl . '/tickets';
        $data = 'username=' . $username . '&password=' . $password;

        $post = new HttpClientRequest($url, array(
            'method' => HttpClientRequest::METHOD_POST,
            'headers' => array('Content-Type' => array('application/x-www-form-urlencoded')),
            'data' => $data,
            'parameters' => array('application' => $this->applicationName, 'key' => $this->applicationKey),
        ));

        $client = $this->client();
        try {
            $body = $client->execute($post);
        } catch (HttpClientException $e) {
            if ($e->getCode() == 0) {
                // curl error
                throw new Exception($e->getMessage());
            }
            return false;
        }

        $this->lastResponse = $client->lastResponse;

        dpm($this->lastResponse);

        return true;
    }

    /**
     * @return HttpClient
     */
    private function client()
    {
        $client = new HttpClient($formatter = FALSE);

        if (!isset($client->options['curlopts'])) {
            $client->options['curlopts'] = array();
        }

        $client->options['curlopts'] += array(
            CURLOPT_SSLVERSION => 3,
            CURLOPT_SSL_VERIFYHOST => FALSE,
            CURLOPT_SSL_VERIFYPEER => FALSE
        );

        return $client;
    }
}