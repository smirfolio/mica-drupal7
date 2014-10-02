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
  <?php print l(t('Search'), 'mica/search', array(
    'attributes' => array(
      'class' => array(
        'btn',
        'btn-primary',
        'indent'
      )
    ),
    'query' => array(
      'type' => 'variables',
      'query' => $query
    ),
  )); ?>
</p>
<article>
  <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
    <?php if (!empty($taxonomy_coverage->vocabularies)): ?>
      <section>
        <h3 data-toggle="tooltip"
            title="<?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>">
          <?php print mica_client_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
        </h3>

        <?php foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) : ?>
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
                          title="<?php print empty($vocabulary_coverage->count) ? 0 : floor($term_coverage->count * 10000 / $vocabulary_coverage->count) / 100; ?>%">
                        <?php print $term_coverage->count; ?>
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

        <?php endforeach; ?>
      </section>
    <?php endif ?>
  <?php endforeach; ?>

</article>