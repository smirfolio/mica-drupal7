<?php
//dpm($coverages);
//dpm($vocabulary_coverage_outputs);
//dpm($query);
?>

  <div id="search-query"></div>
  <p>
    <?php print t('%hits variables (among %count)', array(
      '%hits' => $coverages->totalHits,
      '%count' => $coverages->totalCount
    )) ?>
    <?php

    $query_to_pass = !empty($query) ? array('query' => $query) : NULL;

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
        $query_to_pass
      ),
    )); ?>
  </p>

<?php $has_coverage = FALSE; ?>

  <article>
    <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
      <?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>
        <section>
          <h3>
            <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
          </h3>

          <p class="help-block">
            <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>
          </p>

          <?php foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) : ?>
            <?php if (!empty($vocabulary_coverage->hits)): ?>
              <?php $has_coverage = TRUE; ?>
            <?php endif ?>
            <?php print render($vocabulary_coverage_outputs[$taxonomy_coverage->taxonomy->name][$vocabulary_coverage->vocabulary->name]); ?>
          <?php endforeach; ?>
        </section>
      <?php endif ?>
    <?php endforeach; ?>
  </article>

<?php if (!$has_coverage): ?>
  <p class="md-top-margin">
    <i><?php print t('No coverage'); ?></i>
  </p>
<?php endif ?>