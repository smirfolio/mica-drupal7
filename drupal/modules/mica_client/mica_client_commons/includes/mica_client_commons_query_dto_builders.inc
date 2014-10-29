<?php

abstract class AbstractDtoBuilder
{
  protected $dto = NULL;

  abstract function build();
}

class RangeConditionDtoBuilder extends AbstractDtoBuilder
{
  private function __construct()
  {
    $this->dto = new \obiba\mica\RangeConditionDto();
  }

  static function newBuilder()
  {
    return new RangeConditionDtoBuilder();
  }

  function lt($value)
  {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::LT);
    $this->dto->setValue($value);
    return $this;
  }

  function lte($value)
  {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::LTE);
    $this->dto->setValue($value);
    return $this;
  }

  function gt($value)
  {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::GT);
    $this->dto->setValue($value);
    return $this;
  }

  function gte($value)
  {
    $this->dto->setOp(\obiba\mica\RangeConditionDto\Operator::GTE);
    $this->dto->setValue($value);
    return $this;
  }

  function build()
  {
    return $this->dto;
  }
}

abstract class FilterQueryDto extends AbstractDtoBuilder
{

  protected function __construct()
  {
    $this->dto = new \obiba\mica\FilterQueryDto();
  }

  function field($field)
  {
    $this->dto->setField($field);
    return $this;
  }

}

class RangeFilterQueryDtoBuilder extends FilterQueryDto
{
  private $range = NULL;

  protected function __construct()
  {
    parent::__construct();
    $this->range = new \obiba\mica\RangeFilterQueryDto();
    $this->dto->setExtension("obiba.mica.RangeFilterQueryDto.range", $this->range);
  }

  static function newBuilder()
  {
    return new RangeFilterQueryDtoBuilder();
  }

  function from(\obiba\mica\RangeConditionDto $dto)
  {
    $this->range->setFrom($dto);
    return $this;
  }

  function fromBuilder(RangeConditionDtoBuilder $builder)
  {
    $this->range->setFrom($builder->build());
    return $this;
  }

  function to(\obiba\mica\RangeConditionDto $dto)
  {
    $this->range->setTo($dto);
    return $this;
  }

  function toBuilder(RangeConditionDtoBuilder $builder)
  {
    $this->range->setTo($builder->build());
    return $this;
  }

  function build()
  {
    return $this->dto;
  }

}

class TermsFilterQueryDtoBuilder extends FilterQueryDto
{
  private $terms = NULL;

  protected function __construct()
  {
    parent::__construct();
    $this->terms = new \obiba\mica\TermsFilterQueryDto();
    $this->dto->setExtension("obiba.mica.TermsFilterQueryDto.terms", $this->terms);
  }

  static function newBuilder()
  {
    return new TermsFilterQueryDtoBuilder();
  }

  function value($value)
  {
    $this->terms->addValues($value);
    return $this;
  }

  function values($values)
  {
    foreach ($values as $value) {
      $this->terms->addValues($value);
    }
    return $this;
  }

  function build()
  {
    return $this->dto;
  }
}

class BoolFilterQueryDtoBuilder extends AbstractDtoBuilder
{
  private function __construct()
  {
    $this->dto = new \obiba\mica\BoolFilterQueryDto();
  }

  static function newBuilder()
  {
    return new BoolFilterQueryDtoBuilder();
  }

  function must(\obiba\mica\FilterQueryDto $dto)
  {
    $this->dto->addMust($dto);
    return $this;
  }

  function musts($dtos)
  {
    foreach ($dtos as $dto) {
      $this->dto->addMust($dto);
    }

    return $this;
  }

  function mustBuilders($builders)
  {
    foreach ($builders as $builder) {
      $this->dto->addMust($builder->build());
    }

    return $this;
  }

  function mustNot(\obiba\mica\FilterQueryDto $dto)
  {
    $this->dto->addMustNot($dto);
    return $this;
  }

  function mustNots($dtos)
  {
    foreach ($dtos as $dto) {
      $this->dto->addMustNot($dto);
    }

    return $this;
  }

  function mustNotBuilders($builders)
  {
    foreach ($builders as $builder) {
      $this->dto->addMustNot($builder->build());
    }

    return $this;
  }

  function should(\obiba\mica\FilterQueryDto $dto)
  {
    $this->dto->addShould($dto);
    return $this;
  }

  function shoulds($dtos)
  {
    foreach ($dtos as $dto) {
      $this->dto->addShould($dto);
    }

    return $this;
  }

  function shouldBuilders($builders)
  {
    foreach ($builders as $builder) {
      $this->dto->addShould($builder->build());
    }

    return $this;
  }

  function build()
  {
    return $this->dto;
  }
}

class FilteredQueryDtoBuilder extends AbstractDtoBuilder
{
  private function __construct()
  {
    $this->dto = new \obiba\mica\FilteredQueryDto();
  }

  static function newBuilder()
  {
    return new FilteredQueryDtoBuilder();
  }

  function filter(\obiba\mica\BoolFilterQueryDto $dto)
  {
    $this->dto->setFilter($dto);
    return $this;
  }

  function filterBuilder(BoolFilterQueryDtoBuilder $builder)
  {
    $this->dto->setFilter($builder->build());
    return $this;
  }

  function build()
  {
    return $this->dto;
  }
}

class SortDtoBuilder extends AbstractDtoBuilder {

  private function __construct()
  {
    $this->dto = new \obiba\mica\QueryDto\SortDto();
  }

  static function newBuilder()
  {
    return new SortDtoBuilder();
  }

  function field($field)
  {
    $this->dto->setField($field);
    return $this;
  }

  function orderAsc()
  {
    $this->dto->setOrder(\obiba\mica\QueryDto\SortDto\Order::ASC);
    return $this;
  }

  function orderDesc()
  {
    $this->dto->setOrder(\obiba\mica\QueryDto\SortDto\Order::DESC);
    return $this;
  }

  function build() {
    return $this->dto;
  }
}


class QueryStringDtoBuilder extends AbstractDtoBuilder {

  private function __construct()
  {
    $this->dto = new \obiba\mica\QueryDto\QueryStringDto();
  }

  static function newBuilder()
  {
    return new QueryStringDtoBuilder();
  }

  function query($query) {
    $this->dto->setQuery($query);
    return $this;
  }

  function fields($fields)
  {
    foreach($fields as $field) {
      $this->dto->addFields($field);
    }
    return $this;
  }

  function build() {
    return $this->dto;
  }
}

class QueryDtoBuilder extends AbstractDtoBuilder
{
  private function __construct($from, $size, $sort_field, $matches, $group_by)
  {
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

  static function newBuilder($from, $size, $sort_field, $matches, $group_by)
  {
    return new QueryDtoBuilder($from, $size, $sort_field, $matches, $group_by);
  }

  function filteredQuery(\obiba\mica\FilteredQueryDto $dto)
  {
    $this->dto->setFilteredQuery($dto);
    return $this;
  }

  function filteredQueryBuilder(FilteredQueryDtoBuilder $builder)
  {
    $this->dto->setFilteredQuery($builder->build());
    return $this;
  }

  function build()
  {
    return $this->dto;
  }
}

class JoinQueryDtoBuilder extends AbstractDtoBuilder
{
  const VARIABLES = 'variables';
  const DATASETS = 'datasets';
  const STUDIES = 'studies';
  const NETWORKS = 'networks';
  const MATCHES = 'matches';

  private $mactehsMap = NULL;
  private $builderMap = NULL;
  private $defaultSortMap = NULL;

  private function __construct($data, $defaultSize, $locale)
  {
    $this->dto = new \obiba\mica\JoinQueryDto();
    $this->dto->setLocale($locale);
    $this->builderMap = array();
    $this->defaultSize = $defaultSize;
    $this->initializeDefaultSortMap();
    $this->queryTypes = array(self::VARIABLES, self::DATASETS, self::STUDIES, self::NETWORKS);
    if (!empty($data)) $this->parseData($data);
  }

  static function newBuilder($data, $defaultSize, $locale)
  {
    return new JoinQueryDtoBuilder($data, $defaultSize, $locale);
  }

  function documentQuery($type, $from, $size, $group_by = NULL)
  {
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

  function build()
  {
    return $this->dto;
  }

  /**
   * Expect to have an array of normalized URL param=value
   * @param $data
   */
  private function parseData($data)
  {
    foreach ($data as $type => $searchData) {
      foreach ($searchData as $searchPartType => $parts) {

        if ($searchPartType === self::MATCHES) {
          $this->mactehsMap[$type] = $parts;
          continue;
        }

        foreach ($parts as $part => $values) {
          $normalizedAggName = preg_replace('/-/', '.', $part);
          $builders = array_key_exists($type, $this->builderMap) ? $this->builderMap[$type] : array();
          array_push(
            $builders, $searchPartType == 'terms' //
              ? TermsFilterQueryDtoBuilder::newBuilder()->field($normalizedAggName)->values($values) //
              : RangeFilterQueryDtoBuilder::newBuilder()->field($normalizedAggName)
                ->fromBuilder(RangeConditionDtoBuilder::newBuilder()->gte($values[0]->min))
                ->toBuilder(RangeConditionDtoBuilder::newBuilder()->lte($values[0]->max))
          );

          $this->builderMap[$type] = $builders;
        }
      }
    }
  }


  private function createQuery($builders, $from, $size, $sort_field, $matches, $group_by = NULL)
  {
    return QueryDtoBuilder::newBuilder($from, $size, $sort_field, $matches, $group_by)->filteredQueryBuilder(
      FilteredQueryDtoBuilder::newBuilder()->filterBuilder(
        BoolFilterQueryDtoBuilder::newBuilder()->mustBuilders($builders)))->build();
  }

  private function initializeDefaultSortMap()
  {
    global $language;
    $lang = $language->language;

    $this->defaultSortMap = array( //
      self::VARIABLES => "name", //
      self::DATASETS => "acronym.".$lang, //
      self::STUDIES => "acronym.".$lang, //
      self::NETWORKS => "acronym.".$lang //
    );
  }


}