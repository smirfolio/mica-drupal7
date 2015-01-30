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
    print l(t('Search'), 'mica/search', array(
      'attributes' => array(
        'class' => array(
          'btn',
          'btn-primary',
          'indent'
        )
      ),
      'query' => array(
        'type' => 'variables',
        array('query' => $query)
      ),
    )); ?>
    <span id="download-coverage">
      <a href="" class="btn btn-success"><i
          class='glyphicon glyphicon-download'></i> <?php print t('Download') ?></a>
    </span>
  </p>

  <ul class="nav nav-pills pull-right">
    <li class="<?php if (!empty($group_by) && $group_by == 'studyIds') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by study') ?>">
      <?php
      print l(t('Study'), 'mica/coverage', array(
        'query' => array(
          array(
            'query' => $query,
            'group-by' => 'studyIds'
          )
        ),
      )); ?>
    </li>
    <li class="<?php if (!empty($group_by) && $group_by == 'dceIds') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by data collection event') ?>">
      <?php
      print l(t('Data Collection Event'), 'mica/coverage', array(
        'query' => array(
          array(
            'query' => $query,
            'group-by' => 'dceIds'
          )
        ),
      )); ?>
    </li>
    <li class="<?php if (!empty($group_by) && $group_by == 'datasetId') print 'active' ?>" data-toggle="tooltip"
      data-placement="top" title="<?php print t('Group by dataset') ?>">
      <?php
      print l(t('Dataset'), 'mica/coverage', array(
        'query' => array(
          array(
            'query' => $query,
            'group-by' => 'datasetId'
          )
        ),
      )); ?>
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
            <h3 id="<?php print $taxonomy_coverage->taxonomy->name; ?>">
              <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
            </h3>

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
    <i><?php print t('No coverage'); ?></i>
  </p>
<?php endif ?>
<div class="back-to-top t_badge"><i class="glyphicon glyphicon-arrow-up"></i></div>
