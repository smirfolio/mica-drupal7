<?php
//dpm($coverages);
//dpm($vocabulary_coverage_outputs);
//dpm($query);
//dpm($group_by);

// protect agaist empty queries
if (empty($query)) {
  $query = array();
}
?>

<div class="alert alert-info">
  <div id="search-help">
    <i class="glyphicon glyphicon-arrow-left"></i>
    <span class="indent">
      <?php print t('Start searching by selecting a facet'); ?>
    </span>
  </div>
  <div id="search-query"></div>
</div>

<div>
  <p class="pull-left">

    <?php if (!empty($coverages->totalHits)): ?>
      <?php print t('%hits variables', array(
        '%hits' => $coverages->totalHits,
      )) ?>
    <?php else: ?>
      <?php print t('%hits variables', array(
        '%hits' => 0
      )) ?>
    <?php endif ?>
    <?php
      print MicaClientAnchorHelper::ajax_friendly_anchor(
        MicaClientPathProvider::SEARCH,
        t(variable_get_value('variables_search_label')),
        array('class' => 'btn btn-primary indent'),
        array('type' => 'variables', 'query' => $query)
      );
    ?>
    <span id="download-coverage">
      <a href="" class="btn btn-success"><i
          class='glyphicon glyphicon-download'></i> <?php print t('Download') ?></a>
    </span>
  </p>

  <ul class="nav nav-pills pull-right">
    <li class="<?php if (!empty($group_by) && $group_by == 'studyIds') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by study') ?>">
      <?php
        print MicaClientAnchorHelper::ajax_friendly_anchor(
          MicaClientPathProvider::COVERAGE,
          t('Study'),
          array('class' => 'group-by'),
          array('group-by' => 'studyIds', 'query' => $query)
        );
      ?>
    </li>
    <li class="<?php if (!empty($group_by) && $group_by == 'dceIds') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by data collection event') ?>">
      <?php
        print MicaClientAnchorHelper::ajax_friendly_anchor(
          MicaClientPathProvider::COVERAGE,
          t('Data Collection Event'),
          array('class' => 'group-by'),
          array('group-by' => 'dceIds', 'query' => $query)
        );
      ?>
    </li>
    <li class="<?php if (!empty($group_by) && $group_by == 'datasetId') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by dataset') ?>">
      <?php
        print MicaClientAnchorHelper::ajax_friendly_anchor(
          MicaClientPathProvider::COVERAGE,
          t('Dataset'),
          array('class' => 'group-by'),
          array('group-by' => 'datasetId', 'query' => $query)
        );
      ?>
    </li>
  </ul>
</div>

<?php $has_coverage = FALSE; ?>

<article class="pull-left">
  <?php if (!empty($coverages->taxonomies)): ?>

    <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
      <?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>

        <section>
          <!--          <a href="#" class="btn btn-success md-top-margin pull-right"><i class="glyphicon glyphicon-download right-indent"></i>Download</a>-->

          <div>
            <h2 id="<?php print $taxonomy_coverage->taxonomy->name; ?>">
              <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
            </h2>

            <p class="help-block">
              <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>
            </p>
          </div>

          <?php foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) : ?>
            <?php if (!empty($vocabulary_coverage->hits)): ?>
              <?php $has_coverage = TRUE; ?>
            <?php endif ?>
            <?php print render($vocabulary_coverage_outputs[$taxonomy_coverage->taxonomy->name][$vocabulary_coverage->vocabulary->name]); ?>
          <?php endforeach; ?>
        </section>
      <?php endif ?>
    <?php endforeach; ?>
  <?php endif ?>
</article>

<?php if (!$has_coverage): ?>
  <p class="md-top-margin pull-left">
    <i><?php print t(variable_get_value('variables_empty_label')); ?></i>
  </p>
<?php endif ?>
<div class="back-to-top t_badge"><i class="glyphicon glyphicon-arrow-up"></i></div>
