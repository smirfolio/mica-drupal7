<?php

abstract class AbstractDtoBuilder {
  protected $dto = NULL;

  abstract function build();
}

class RangeConditionDtoBuilder extends AbstractDtoBuilder {
  private function __construct() {
    $this->dto = new \obiba\mica\RangeConditionDto();
  }

  static function newBuilder() {
    return new RangeConditionDtoBuilder();
  }

  function lt($value) {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::LT);
    $this->dto->setValue($value);
    return $this;
  }

  function lte($value) {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::LTE);
    $this->dto->setValue($value);
    return $this;
  }

  function gt($value) {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::GT);
    $this->dto->setValue($value);
    return $this;
  }

  function gte($value) {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::GTE);
    $this->dto->setValue($value);
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

abstract class FieldFilterQueryDtoBuilder extends AbstractDtoBuilder {
  private $filter = NULL;

  protected function __construct() {
    $this->dto = new \obiba\mica\FilteredQueryDto();
    $this->filter = new \obiba\mica\FieldFilterQueryDto();
    $this->dto->setExtension('obiba.mica.FieldFilterQueryDto.filter', $this->filter);
  }

  protected function extension($key, $extension) {
    $this->filter->setExtension($key, $extension);
    return $this;
  }

  function field($field) {
    $this->filter->setField($field);
    return $this;
  }

  function filter() {
    return $this->filter;
  }

}

class RangeFieldFilterQueryDtoBuilder extends FieldFilterQueryDtoBuilder {
  private $range = NULL;

  protected function __construct() {
    parent::__construct();
    $this->range = new \obiba\mica\RangeFilterQueryDto();
    $this->extension("obiba.mica.RangeFilterQueryDto.range", $this->range);
  }

  static function newBuilder() {
    return new RangeFieldFilterQueryDtoBuilder();
  }

  function from(\obiba\mica\RangeConditionDto $dto) {
    $this->range->setFrom($dto);
    return $this;
  }

  function fromBuilder(RangeConditionDtoBuilder $builder) {
    $this->range->setFrom($builder->build());
    return $this;
  }

  function to(\obiba\mica\RangeConditionDto $dto) {
    $this->range->setTo($dto);
    return $this;
  }

  function toBuilder(RangeConditionDtoBuilder $builder) {
    $this->range->setTo($builder->build());
    return $this;
  }

  function build() {
    return $this->dto;
  }

}

class TermsFieldFilterQueryDtoBuilder extends FieldFilterQueryDtoBuilder {
  private $terms = NULL;

  protected function __construct() {
    parent::__construct();
    $this->terms = new \obiba\mica\TermsFilterQueryDto();
    $this->extension("obiba.mica.TermsFilterQueryDto.terms", $this->terms);
  }

  static function newBuilder() {
    return new TermsFieldFilterQueryDtoBuilder();
  }

  function value($value) {
    $this->terms->addValues($value);
    return $this;
  }

  function values($values) {
    foreach ($values as $value) {
      $this->terms->addValues($value);
    }
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

class BoolFilterQueryDtoBuilder extends AbstractDtoBuilder {
  private $filter = NULL;

  private function __construct() {
    $this->dto = new \obiba\mica\FilteredQueryDto();
    $this->filter = new \obiba\mica\BoolFilterQueryDto();
    $this->dto->setExtension('obiba.mica.BoolFilterQueryDto.filter', $this->filter);
  }

  static function newBuilder() {
    return new BoolFilterQueryDtoBuilder();
  }

  function operator($value) {
    $this->filter->setOp($value);
    return $this;
  }

  function filteredQueries(array $values) {
    foreach ($values as $value) {
      $this->filter->addFilteredQuery($value);
    }
  }

  function filteredQueriesBuilders(array $values) {
    foreach ($values as $value) {
      $this->filter->addFilteredQuery($value->build);
    }
  }

  function build() {
    return $this->dto;
  }
}

class FieldStatementDtoBuilder extends AbstractDtoBuilder {

  private function __construct() {
    $this->dto = new \obiba\mica\FieldStatementDto();
  }

  static function newBuilder() {
    return new FieldStatementDtoBuilder();
  }

  static function mapOp($value) {
    switch (strtolower($value)) {
      case 'or':
        return \obiba\mica\FieldStatementDto\Operator::_OR;
      case 'and':
        return \obiba\mica\FieldStatementDto\Operator::_AND;
      case 'not':
        return \obiba\mica\FieldStatementDto\Operator::_AND_NOT;
    }

    return NULL;
  }

  function field(\obiba\mica\FieldFilterQueryDto $value) {
    $this->dto->setField($value);
    return $this;
  }

  function fieldBuilder(FieldFilterQueryDtoBuilder $value) {
    $this->dto->setField($value->build());
    return $this;
  }

  function op($value) {
    $this->dto->setOp(self::mapOp($value));
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

class LogicalFilterQueryDtoBuilder extends AbstractDtoBuilder {
  private $filter = NULL;

  private function __construct() {
    $this->dto = new \obiba\mica\FilteredQueryDto();
    $this->filter = new \obiba\mica\LogicalFilterQueryDto();
    $this->dto->setExtension('obiba.mica.LogicalFilterQueryDto.filter', $this->filter);
  }

  static function newBuilder() {
    return new LogicalFilterQueryDtoBuilder();
  }


  function field(\obiba\mica\FieldFilterQueryDto $value, $op) {
    $fieldStatementDto = FieldStatementDtoBuilder::newBuilder()->field($value)->op($op)->build();
    $this->filter->addFields($fieldStatementDto);
    return $this;
  }

  function fieldBuilder(FieldFilterQueryDtoBuilder $value, $op) {
    $this->field($value->filter(), $op);
    return $this;
  }

  function hasFields() {
    return $this->filter->hasFields();
  }

  function build() {
    return $this->dto;
  }
}


class FilteredQueryDtoBuilder extends AbstractDtoBuilder {
  private function __construct() {
    $this->dto = new \obiba\mica\FilteredQueryDto();
  }

  static function newBuilder() {
    return new FilteredQueryDtoBuilder();
  }

  function build() {
    return $this->dto;
  }
}

class SortDtoBuilder extends AbstractDtoBuilder {

  private function __construct() {
    $this->dto = new \obiba\mica\QueryDto\SortDto();
  }

  static function newBuilder() {
    return new SortDtoBuilder();
  }

  function field($field) {
    $this->dto->setField($field);
    return $this;
  }

  function orderAsc() {
    $this->dto->setOrder(\obiba\mica\QueryDto\SortDto\Order::ASC);
    return $this;
  }

  function orderDesc() {
    $this->dto->setOrder(\obiba\mica\QueryDto\SortDto\Order::DESC);
    return $this;
  }

  function build() {
    return $this->dto;
  }
}


class QueryStringDtoBuilder extends AbstractDtoBuilder {

  private function __construct() {
    $this->dto = new \obiba\mica\QueryDto\QueryStringDto();
  }

  static function newBuilder() {
    return new QueryStringDtoBuilder();
  }

  function query($query) {
    $this->dto->setQuery($query);
    return $this;
  }

  function fields($fields) {
    foreach ($fields as $field) {
      $this->dto->addFields($field);
    }
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

class QueryDtoBuilder extends AbstractDtoBuilder {
  private function __construct($from, $size, $sort_field, $matches, $group_by) {
    $this->dto = new \obiba\mica\QueryDto();
    $this->dto->setFrom($from);
    $this->dto->setSize($size);

    if (!empty($matches)) {
      $this->dto->setQueryString(QueryStringDtoBuilder::newBuilder()->query($matches)->build());
    }

    if (!empty($sort_field)) {
      $this->dto->setSort(SortDtoBuilder::newBuilder()->field($sort_field)->build());
    }

    if (!empty($group_by)) {
      if (is_array($group_by)) {
        $this->dto->setAggsBy($group_by);
      }
      else {
        $this->dto->addAggsBy($group_by);
      }
    }
  }

  static function newBuilder($from, $size, $sort_field, $matches, $group_by) {
    return new QueryDtoBuilder($from, $size, $sort_field, $matches, $group_by);
  }

  function filteredQuery(\obiba\mica\FilteredQueryDto $dto) {
    $this->dto->setFilteredQuery($dto);
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

class JoinQueryDtoBuilder extends AbstractDtoBuilder {
  const VARIABLES = 'variables';
  const DATASETS = 'datasets';
  const STUDIES = 'studies';
  const NETWORKS = 'networks';
  const MATCHES = 'matches';

  const OR_OPERATOR = 'or';
  const AND_OPERATOR = 'and';

  private $mactehsMap = NULL;
  private $builderMap = NULL;
  private $defaultSortMap = NULL;

  private function __construct($data, $defaultSize, $locale) {
    $this->dto = new \obiba\mica\JoinQueryDto();
    $this->dto->setLocale($locale);
    $this->builderMap = array();
    $this->defaultSize = $defaultSize;
    $this->initializeDefaultSortMap();
    $this->queryTypes = array(self::VARIABLES, self::DATASETS, self::STUDIES, self::NETWORKS);
    if (!empty($data)) {
      $this->parseData($data);
    }
  }

  static function newBuilder($data, $defaultSize, $locale) {
    return new JoinQueryDtoBuilder($data, $defaultSize, $locale);
  }

  function documentQuery($type, $from, $size, $group_by = NULL) {
    $matches = empty($this->mactehsMap[$type]) ? NULL : $this->mactehsMap[$type];
    $defaultSortField = $this->defaultSortMap[$type];
    $this->setQuery($type, array_key_exists($type, $this->builderMap) //
      ? $this->createQuery($this->builderMap[$type], $from, $size, $defaultSortField, $matches, $group_by) //
      : QueryDtoBuilder::newBuilder($from, $size, $defaultSortField, $matches, $group_by)->build() //
    );

    $queryTypes = array_filter( //
      $this->queryTypes, //
      function ($queryType) use ($type) {
        return $queryType !== $type;
      });

    foreach ($queryTypes as $queryType) {
      $matches = empty($this->mactehsMap[$queryType]) ? NULL : $this->mactehsMap[$queryType];
      $builders = empty($this->builderMap[$queryType]) ? NULL : $this->builderMap[$queryType];
      $defaultSortField = $this->defaultSortMap[$queryType];

      if (!empty($matches) || !empty($builders)) {
        $this->setQuery($queryType, empty($builders) //
          ? QueryDtoBuilder::newBuilder(0, $this->defaultSize, $defaultSortField, $matches, $group_by)->build() //
          : $this->createQuery($builders, 0, $this->defaultSize, $defaultSortField, $matches, $group_by) //
        );
      }
    }

    return $this;
  }

  private function setQuery($type, $query) {
    switch ($type) {
      case self::VARIABLES:
        $this->dto->setVariableQueryDto($query);
        break;
      case self::DATASETS:
        $this->dto->setDatasetQueryDto($query);
        break;
      case self::STUDIES:
        $this->dto->setStudyQueryDto($query);
        break;
      case self::NETWORKS:
        $this->dto->setNetworkQueryDto($query);
        break;
    }
  }

  function build() {
    return $this->dto;
  }

  /**
   * Expect to have an array of normalized URL param=value
   * @param $data
   */
  private function parseData($data) {

    foreach ($data as $type => $searchData) {
      foreach ($searchData as $searchPartType => $parts) {

        if ($searchPartType === self::MATCHES) {
          $this->mactehsMap[$type] = $parts;
          continue;
        }

        $logicalFilterBuilder = $this->getLogicalFilterBuilder($type);

        foreach ($parts as $aggName => $agg) {
          if ($this->processException($logicalFilterBuilder, $type, $aggName, $agg, $searchPartType)) {
            continue;
          }
          $logicalFilterBuilder->fieldBuilder(
            $this->getAggregationBuilder($searchPartType, $aggName, $agg),
            $agg->op
          );
        }
      }

      if (!empty($logicalFilterBuilder) && $logicalFilterBuilder->hasFields()) {
        $this->builderMap[$type] = $logicalFilterBuilder;
        $logicalFilterBuilder = NULL;
      }
    }
  }

  private function processException($logicalFilterBuilder, $type, $aggName, $agg, $searchPartType) {
    if (self::NETWORKS === $type && "networkId" === $aggName) {
      $logicalFilterBuilder->fieldBuilder(
        $this->getAggregationBuilder($searchPartType, "id", $agg),
        $agg->op
      );
      $this->builderMap[self::NETWORKS] = $logicalFilterBuilder;
      return TRUE;
    }
    else {
      if (self::STUDIES === $type && "studyIds" === $aggName) {
        $logicalFilterBuilder->fieldBuilder(
          $this->getAggregationBuilder($searchPartType, "id", $agg),
          $agg->op
        );
        return TRUE;
      }
    }

    return FALSE;
  }

  private function getNormalizedAggName($aggName) {
    return preg_replace('/-/', '.', $aggName);
  }

  private function getLogicalFilterBuilder($type) {
    return array_key_exists($type, $this->builderMap) //
      ? $this->builderMap[$type] //
      : LogicalFilterQueryDtoBuilder::newBuilder();
  }

  private function getAggregationBuilder($searchPartType, $aggName, $agg) {
    $normalizedAggName = $this->getNormalizedAggName($aggName);
    $aggValues = $agg->values;
    return $searchPartType == 'terms' //
      ? TermsFieldFilterQueryDtoBuilder::newBuilder()->field($normalizedAggName)->values($aggValues) //
      : RangeFieldFilterQueryDtoBuilder::newBuilder()->field($normalizedAggName)
        ->fromBuilder(RangeConditionDtoBuilder::newBuilder()->gte($aggValues[0]->min))
        ->toBuilder(RangeConditionDtoBuilder::newBuilder()->lte($aggValues[0]->max));
  }

  private function createQuery(LogicalFilterQueryDtoBuilder $builder, $from, $size, $sort_field, $matches, $group_by = NULL) {
    $dto = QueryDtoBuilder::newBuilder($from, $size, $sort_field, $matches, $group_by)
      ->filteredQuery($builder->build())->build();

    return $dto;
  }

  private function initializeDefaultSortMap() {
    global $language;
    $lang = $language->language;

    $this->defaultSortMap = array( //
      self::VARIABLES => "name", //
      self::DATASETS => "acronym." . $lang, //
      self::STUDIES => "acronym." . $lang, //
      self::NETWORKS => "acronym." . $lang //
    );
  }

}