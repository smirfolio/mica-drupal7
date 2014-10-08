<?php

abstract class AbstractResponseWrapper {
  protected  $dto = NULL;
  protected  $documentDto = NULL;

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

  function __construct($joinQueryResponseDto) {
    parent::__construct($joinQueryResponseDto);
    if (!empty($this->dto) && !empty($this->dto->studyResultDto)) {
        $this->documentDto = $this->dto->studyResultDto;
    }
  }

  function getSummaries() {
    return empty($this->documentDto) || empty($this->documentDto->{'obiba.mica.StudyResultDto.result'}) //
      ? array() //
      : $this->documentDto->{'obiba.mica.StudyResultDto.result'}->summaries;
  }

  function getNetworkDigests() {
    $networkDto = $this->dto->networkResultDto;
    return empty($networkDto) && empty($networkDto->{'obiba.mica.NetworkResultDto.result'}) //
      ? array() //
      : $networkDto->{'obiba.mica.NetworkResultDto.result'}->digests;
  }
}