<?php
//dpm($coverages);
//dpm($vocabulary_coverage_outputs);
//dpm($query);
//dpm($group_by);
?>

<div id="search-query"></div>
<div>
  <p class="pull-left">

    <?php if (!empty($coverages->totalHits)): ?>
      <?php print t('%hits variables (among %count)', array(
        '%hits' => $coverages->totalHits,
        '%count' => $coverages->totalCount
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
  </p>

  <ul class="nav nav-pills pull-right">
    <li class="<?php if (empty($group_by)) print 'active' ?>">
      <?php
      print l(t('All'), 'mica/coverage', array(
        'query' => array(
          array('query' => $query)
        ),
      )); ?>
    </li>
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

<?php if (!empty($coverages->taxonomies)): ?>
  <div class="affix-sidebar">
    <nav id="scroll-menu" data-spy="affix">
      <ul class="nav">
        <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
          <?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>
            <li>
              <a href="#<?php print $taxonomy_coverage->taxonomy->name; ?>">
                <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
              </a>
              <ul class="nav" style="display: block;">
                <?php foreach ($taxonomy_coverage->vocabularies as $index => $vocabulary_coverage) : ?>
                  <?php if (!empty($vocabulary_coverage->hits)): ?>
                    <li class="<?php $index === 0 ? 'active' : '' ?>">
                      <a
                        href="#<?php print $taxonomy_coverage->taxonomy->name . '-' . $vocabulary_coverage->vocabulary->name; ?>">
                        <?php print mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'); ?>
                      </a>
                    </li>
                  <?php endif ?>
                <?php endforeach; ?>
              </ul>
            </li>
          <?php endif ?>
        <?php endforeach; ?>
      </ul>
    </nav>
  </div>
<?php endif ?>

<article class="pull-left">
  <?php if (!empty($coverages->taxonomies)): ?>

    <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
      <?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>

        <section>
          <a href="#" class="btn btn-success md-top-margin pull-right"><i class="glyphicon glyphicon-download right-indent"></i>Download</a>

          <div>
            <h3 id="<?php print $taxonomy_coverage->taxonomy->name; ?>">
              <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
            </h3>

            <p class="help-block">
              <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>
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
