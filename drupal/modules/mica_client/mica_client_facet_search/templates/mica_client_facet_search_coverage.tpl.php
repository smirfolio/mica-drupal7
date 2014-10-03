<?php
//dpm($coverages);
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
        <h3 data-toggle="tooltip"
            title="<?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>">
          <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
        </h3>

        <?php foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) : ?>
          <?php if (!empty($vocabulary_coverage->hits)): ?>
            <?php $has_coverage = TRUE; ?>
            <h5 data-toggle="tooltip"
                title="<?php print mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'descriptions'); ?>">
              <?php print mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'); ?>
            </h5>

            <div class="container-fluid">
              <div class="row">
                <div class="col-xs-6 right-indent">
                  <table class="table table-striped">
                    <thead>
                    <tr>
                      <th><?php print t('Term'); ?></th>
                      <th style="width:50px; text-align: center;">
                        <?php print t('Count'); ?>
                      </th>
                    </tr>
                    </thead>
                    <tfoot>
                    <tr>
                      <th><?php print t('Total'); ?></th>
                      <th style="width:50px; text-align: center;" title="100%">
                        <?php print !property_exists($vocabulary_coverage, 'count') ? '-' : $vocabulary_coverage->count; ?>
                      </th>
                    </tr>
                    </tfoot>
                    <tbody>

                    <?php foreach ($vocabulary_coverage->terms as $term_coverage) : ?>
                      <tr data-toggle="tooltip"
                          title="<?php print mica_client_commons_get_localized_field($term_coverage->term, 'descriptions'); ?>">
                        <td>
                          <?php print mica_client_commons_get_localized_field($term_coverage->term, 'titles'); ?>
                        </td>
                        <td style="width:50px; text-align: center;"
                            title="<?php print empty($vocabulary_coverage->hits) ? 0 : floor($term_coverage->hits * 10000 / $vocabulary_coverage->hits) / 100; ?>%">
                          <?php if (empty($term_coverage->hits)): ?>
                            <?php print 0; ?>
                           <?php else: ?>
                            <span class="badge alert-success"><?php print $term_coverage->hits; ?></span>
                           <?php endif ?>
                        </td>
                      </tr>
                    <?php endforeach; ?>

                    </tbody>
                  </table>

                </div>
                <div class="col-xs-6">
                  <div class="alert alert-info" role="alert"><strong>TODO</strong> charts here</div>
                </div>
              </div>
            </div>

          <?php endif ?>
        <?php endforeach; ?>
      </section>
    <?php endif ?>
  <?php endforeach; ?>
</article>

<?php if(!$has_coverage): ?>
  <p class="md-top-margin">
    <i><?php print t('No coverage'); ?></i>
  </p>
<?php endif ?>