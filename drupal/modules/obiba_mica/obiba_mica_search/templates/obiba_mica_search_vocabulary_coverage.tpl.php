<?php
//dpm($vocabulary_coverage);
//dpm($vocabulary_attribute);
//dpm($chart);
//dpm($bucket_names);
?>

<?php if (!empty($vocabulary_coverage->hits)): ?>
  <?php $has_coverage = TRUE; ?>
  <?php
  $term_names = array();
  foreach ($vocabulary_coverage->terms as $term_coverage) {
    if (!empty($term_coverage->hits)) {
      $term_names[] = $term_coverage->term->name;
    }
  } ?>
  <h3 id="<?php print $taxonomy->name . '-' . $vocabulary_coverage->vocabulary->name; ?>">
    <?php print obiba_mica_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'); ?>
  </h3>

  <p class="help-block">
    <?php print obiba_mica_commons_get_localized_field($vocabulary_coverage->vocabulary, 'descriptions'); ?>
  </p>



  <div class="coverage-table">

    <table class="table table-striped fix-first-column ">
      <thead>
      <tr>
        <th class="fix-width-column right-border">
          <?php print t('Term'); ?>
        </th>
        <th style="text-align: center;
          min-width: 100%;
        <?php !empty($vocabulary_coverage->buckets) ?
          print 'width: ' . (100 / (count($vocabulary_coverage->buckets) + 1)) . '%;' : ''; ?>
          " data-toggle="tooltip" data-placement="top"
            title="<?php print t('Total number of variables per term'); ?>">
          <?php print t('Total'); ?>
        </th>
        <?php if (!empty($vocabulary_coverage->buckets)): ?>
          <?php foreach ($vocabulary_coverage->buckets as $bucket) : ?>
            <th style="text-align: center;
              min-width: 100%;
              width: <?php print 100 / (count($vocabulary_coverage->buckets) + 1) ?>%;">
              <?php
                print MicaClientAnchorHelper::ajax_friendly_anchor(
                  MicaClientPathProvider::SEARCH,
                  $bucket->value,
                  array(
                    'data-toggle' => 'tooltip',
                    'data-placement' => 'top',
                    'title' => isset($bucket->description) ? $bucket->description : $bucket->value,
                  ),
                  array(
                    'type' => 'variables',
                    'query' => MicaClient::add_parameter_dto_query_link(array(
                      $bucket_type => array(
                        'terms' => array(
                          $bucket->field => $bucket->value
                        )
                      )
                    ))
                  )
                );
              ?>
            </th>
          <?php endforeach; ?>
        <?php endif ?>
      </tr>
      </thead>
      <tfoot>
      <tr>
        <th class="right-border"><?php print t('Total'); ?></th>
        <th style="text-align: center;">
          <?php
            print MicaClientAnchorHelper::ajax_friendly_anchor(
              MicaClientPathProvider::SEARCH,
              $vocabulary_coverage->hits,
              array(),
              array(
                'type' => 'variables',
                'query' => MicaClient::add_parameter_dto_query_link(array(
                  'variables' => array(
                    'terms' => array(
                      $vocabulary_attribute => $term_names,
                    )
                  )
                ))
              )
            );
          ?>
        </th>
        <?php if (!empty($vocabulary_coverage->buckets)): ?>
          <?php foreach ($vocabulary_coverage->buckets as $bucket) : ?>
            <th style="text-align: center;">
              <?php if (empty($bucket->hits)): ?>
                <?php print 0; ?>
              <?php else: ?>
                <?php
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::SEARCH,
                    $bucket->hits,
                    array(),
                    array(
                      'type' => 'variables',
                      'query' => MicaClient::add_parameter_dto_query_link(array_merge_recursive(
                          array(
                            $bucket_type => array(
                              'terms' => array(
                                $bucket->field => $bucket->value
                              )
                            )
                          ),
                          array(
                            'variables' => array(
                              'terms' => array(
                                $vocabulary_attribute => $term_names
                              )
                            )
                          )
                        )
                      )
                    )
                  );
                ?>
              <?php endif ?>
            </th>
          <?php endforeach; ?>
        <?php endif ?>
      </tr>
      </tfoot>
      <tbody>

      <?php foreach ($vocabulary_coverage->terms as $key_term => $term_coverage) : ?>
        <?php if (!empty($term_coverage->hits)): ?>
          <tr data-toggle="tooltip"
              title="<?php print obiba_mica_commons_get_localized_field($term_coverage->term, 'descriptions'); ?>">
            <td style="vertical-align: middle; word-wrap:break-word;" class="right-border">
              <?php if (empty($term_coverage->hits)): ?>
                <?php print obiba_mica_commons_get_localized_field($term_coverage->term, 'titles'); ?>
              <?php else: ?>
                <?php
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::SEARCH,
                    obiba_mica_commons_get_localized_field($term_coverage->term, 'titles'),
                    array(),
                    array(
                      'type' => 'variables',
                      'query' => MicaClient::add_parameter_dto_query_link(array(
                        'variables' => array(
                          'terms' => array(
                            $vocabulary_attribute => $term_coverage->term->name
                          )
                        )
                      ))
                    )
                  );
                ?>
              <?php endif ?>
            </td>
            <td style="text-align: center; vertical-align: middle;"
                title="<?php print empty($vocabulary_coverage->hits) ? '0' : floor($term_coverage->hits * 10000 / $vocabulary_coverage->hits) / 100; ?>%">
              <?php if (empty($term_coverage->hits)): ?>
                <?php print 0; ?>
              <?php else: ?>
                <span class="label label-success"><?php print $term_coverage->hits; ?></span>
              <?php endif ?>
            </td>
            <?php if (!empty($term_coverage->buckets)): ?>
              <?php foreach ($bucket_names as $bucket_name) : ?>
                <?php $found = FALSE ?>
                <?php foreach ($term_coverage->buckets as $bucket) : ?>
                  <?php if ($bucket->value == $bucket_name): ?>
                    <td style="text-align: center; vertical-align: middle;">
                      <?php if (empty($bucket->hits)): ?>
                        <?php print 0; ?>
                      <?php else: ?>
                        <span class="label label-info">
                        <?php
                          print MicaClientAnchorHelper::ajax_friendly_anchor(
                            MicaClientPathProvider::SEARCH,
                            $bucket->hits,
                            array(),
                            array(
                              'type' => 'variables',
                              'query' => MicaClient::add_parameter_dto_query_link(array_merge_recursive(
                                  array(
                                    $bucket_type => array(
                                      'terms' => array(
                                        $bucket->field => $bucket->value
                                      )
                                    )
                                  ),
                                  array(
                                    'variables' => array(
                                      'terms' => array(
                                        $vocabulary_attribute => $term_coverage->term->name
                                      )
                                    )
                                  )
                                )
                              )
                            )
                          );
                        ?>
                        </span>
                      <?php endif ?>
                    </td>
                    <?php $found = TRUE ?>
                  <?php endif ?>
                <?php endforeach; ?>
                <?php if (!$found): ?>
                  <td style="text-align: center; vertical-align: middle;">0</td>
                <?php endif ?>
              <?php endforeach; ?>
            <?php else: ?>
              <?php foreach ($bucket_names as $bucket_name) : ?>
                <td style="text-align: center; vertical-align: middle;">0</td>
              <?php endforeach; ?>
            <?php endif ?>
          </tr>
        <?php endif ?>
      <?php endforeach; ?>

      </tbody>
    </table>


  </div>

  <div>
    <?php //print render($chart); ?>
  </div>

<?php endif ?>
