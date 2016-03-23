<?php


class RqlQueryBuilder {
  
  public static function network_query_charts($studyIds)
  {
    return self::createQuery(
      "variable(in(studyIds,(%s)),sort(name),aggregate(%s,bucket(studyIds))),locale(%s)",
      $studyIds
    );
  }

  public static function study_query_charts($studyId)
  {
    return self::createQuery(
      "variable(eq(studyIds,%s),sort(name),aggregate(%s,bucket(dceIds))),locale(%s)",
      $studyId
    );
  }

  public static function dataset_query_charts($datasetId)
  {
    return self::createQuery(
      "variable(eq(datasetId,%s),sort(name),aggregate(%s)),locale(%s)",
      $datasetId
    );
  }

  private static function createQuery($format, $args) {
    global $language;

    return sprintf(
      $format ,
      is_array($args) ? join(',', $args) : $args,
      self::createAggregationQuery(),
      $language->language
    );
  }

  private static function createAggregationQuery() {
    $figures = variable_get_value('mica_taxonomy_figures');
    if (empty($figures)) return '';

    $taxonomies = explode(',', $figures);
    foreach ($taxonomies as &$taxonomy) {
      $taxonomy .= '*';
    }

    return sprintf("re(%s)", implode(',', $taxonomies));
  }

}
