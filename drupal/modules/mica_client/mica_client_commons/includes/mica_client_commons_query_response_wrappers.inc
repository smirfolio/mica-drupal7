<?php

abstract class AbstractResponseWrapper {
  const STUDY_RESULT_EXTENSION_ID = 'obiba.mica.StudyResultDto.result';
  const NETWORK_RESULT_EXTENSION_ID = 'obiba.mica.NetworkResultDto.result';
  const DATASET_RESULT_EXTENSION_ID = 'obiba.mica.DatasetResultDto.result';

  protected $dto = NULL;
  protected $documentDto = NULL;

  protected function __construct($joinQueryResponseDto) {
    $this->dto = $joinQueryResponseDto;
  }

  function getTotalHits() {
    return empty($this->documentDto) ? 0 : $this->documentDto->totalHits;
  }

  function getTotalCount() {
    return empty($this->documentDto) ? 0 : $this->documentDto->totalCount;
  }

  abstract function getSummaries();
}

class StudyJoinResponseWrapper extends AbstractResponseWrapper {

  private $studyToNetwork = array();

  function __construct($joinQueryResponseDto) {
    parent::__construct($joinQueryResponseDto);
    if (!empty($this->dto) && !empty($this->dto->studyResultDto)) {
      $this->documentDto = $this->dto->studyResultDto;
      $this->networks = $this->mapNetworkDigests();
    }
  }

  function getSummaries() {
    return empty($this->documentDto) || empty($this->documentDto->{self::STUDY_RESULT_EXTENSION_ID}) //
      ? array() //
      : $this->documentDto->{self::STUDY_RESULT_EXTENSION_ID}->summaries;
  }

  function getNetworkDigests($studyId) {
    $networks = array();
    if (!empty($this->studyToNetwork[$studyId])) {
      $networks = $this->studyToNetwork[$studyId];
    }
    return empty($networks) ? array() : $networks;
  }

  private function mapNetworkDigests() {
    foreach ($this->getSummaries() as $study) {
      $studyId = $study->id;
      $networks = $this->mapNetwork($studyId);
      if (!empty($networks)) {
        $this->studyToNetwork[$studyId] = $networks;
      }
    }
  }

  private function mapNetwork($studyId) {
    if (!empty($this->dto->networkResultDto)) {
      $networkDto = $this->dto->networkResultDto;

      return empty($networkDto) && empty($networkDto->{self::NETWORK_RESULT_EXTENSION_ID}) //
        ? array() //
        : array_filter( //
          $networkDto->{self::NETWORK_RESULT_EXTENSION_ID}->digests, //
          function ($network) use ($studyId) {
            $studies = $network->{'obiba.mica.NetworkDigestDto.studies'};
            return !empty($studies) && !empty($studies->ids) && in_array($studyId, $studies->ids);
          }
        );
    }
    else {
      return array();
    }
  }
}

class NetworkJoinResponseWrapper extends AbstractResponseWrapper {

  function __construct($joinQueryResponseDto) {
    parent::__construct($joinQueryResponseDto);
    if (!empty($this->dto) && !empty($this->dto->networkResultDto)) {
      $this->documentDto = $this->dto->networkResultDto;
    }
  }

  function getSummaries() {
    return empty($this->documentDto) || empty($this->documentDto->{self::NETWORK_RESULT_EXTENSION_ID}) //
      ? array() //
      : $this->documentDto->{self::NETWORK_RESULT_EXTENSION_ID}->networks;
  }
}

class DatasetJoinResponseWrapper extends AbstractResponseWrapper {

  function __construct($joinQueryResponseDto) {
    parent::__construct($joinQueryResponseDto);
    if (!empty($this->dto) && !empty($this->dto->datasetResultDto)) {
      $this->documentDto = $this->dto->datasetResultDto;
    }
  }

  function getSummaries() {
    return empty($this->documentDto) || empty($this->documentDto->{self::DATASET_RESULT_EXTENSION_ID}) //
      ? array() //
      : $this->documentDto->{self::DATASET_RESULT_EXTENSION_ID}->datasets;
  }

}