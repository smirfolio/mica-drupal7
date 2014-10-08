<?php
//dpm($vocabulary_coverage);
//dpm($charts);
?>

<?php if (!empty($vocabulary_coverage->hits)): ?>
  <?php $has_coverage = TRUE; ?>
  <h4>
    <?php print mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'); ?>
  </h4>

  <p class="help-block">
    <?php print mica_client_commons_get_localized_field($vocabulary_coverage->vocabulary, 'descriptions'); ?>
  </p>

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
        <?php print render($charts); ?>
      </div>
    </div>
  </div>

<?php endif ?>
