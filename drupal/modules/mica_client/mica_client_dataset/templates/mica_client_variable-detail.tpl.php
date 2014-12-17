<?php
//dpm($variable_dto);
//dpm($variable_harmonization);
?>

<article>
<section>
  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 lg-right-indent">
        <h3><?php print t('Overview') ?></h3>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($variable_dto->label)): ?>
            <tr>
              <td><h5><?php print t('Label') ?></h5></td>
              <td><?php print $variable_dto->label; ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($variable_dto->description)): ?>
            <tr>
              <td><h5><?php print t('Description') ?></h5></td>
              <td><p><?php print $variable_dto->description; ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($variable_dto->studySummaries)): ?>
            <tr>
              <td>
                <h5>
                  <?php if ($variable_dto->variableType == 'Dataschema') {
                    print t('Studies');
                  }
                  else {
                    print t('Study');
                  }?>
                </h5>
              </td>
              <td>
                <?php if ($variable_dto->variableType == 'Dataschema'): ?>
                  <ul>
                    <?php foreach ($variable_dto->studySummaries as $studySummary): ?>
                      <li>
                        <?php print l(mica_client_commons_get_localized_field($studySummary, 'name'), 'mica/study/' . $studySummary->id . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($studySummary, 'name'))); ?>
                      </li>
                    <?php endforeach ?>
                  </ul>
                <?php elseif (!empty($variable_dto->studySummaries)): ?>
                  <?php print l(mica_client_commons_get_localized_field($variable_dto->studySummaries[0], 'name'), 'mica/study/' . $variable_dto->studySummaries[0]->id . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto->studySummaries[0], 'name'))); ?>
                <?php endif ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($variable_dto->datasetId)): ?>
            <tr>
              <td><h5><?php print t('Dataset'); ?></h5></td>
              <td>
                <p>
                  <?php
                  print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/' . mica_client_variable_dataset_type($variable_dto)
                    . '/' . $variable_dto->datasetId . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')));
                  ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <tr>
            <td><h5><?php print t('Entity Type'); ?></h5></td>
            <td><p><?php print t($variable_dto->entityType); ?></p></td>
          </tr>

          <tr>
            <td><h5><?php print t('Value Type'); ?></h5></td>
            <td><p><?php print t($variable_dto->valueType); ?></p></td>
          </tr>

          <?php if (!empty($variable_dto->unit)): ?>
            <tr>
              <td><h5><?php print t('Unit'); ?></h5></td>
              <td><p><?php print t($variable_dto->unit); ?></p></td>
            </tr>
          <?php endif; ?>

          <tr>
            <td><h5><?php print t('Variable Type'); ?></h5></td>
            <td>
              <p>
                <?php print t('@type variable', array('@type' => t($variable_dto->variableType))); ?>
                <?php if ($variable_dto->variableType == 'Harmonized'): ?>
                  <?php
                  print '(' . l($variable_dto->name, 'mica/variable/' . $variable_dto->datasetId . ':' . $variable_dto->name
                      . ':Dataschema' . '/' . mica_client_commons_to_slug($variable_dto->name)) . ')';
                  ?>
                <?php endif; ?>
              </p>
            </td>
          </tr>

          <?php if (!empty($variable_dto->comment)): ?>
            <tr>
              <td><h5><?php print t('Comment'); ?></h5></td>
              <td><p><?php print($variable_dto->comment); ?></p></td>
            </tr>
          <?php endif; ?>


          </tbody>
        </table>
      </div>
      <div class="col-xs-6">
        <!-- Taxonomy terms -->
        <?php if (!empty($variable_dto->termAttributes)): ?>
          <h3><?php print t('Classification') ?></h3>
          <?php foreach ($variable_dto->termAttributes as $termAttributes) : ?>
            <h4>
              <?php print mica_client_commons_get_localized_field($termAttributes->taxonomy, 'titles'); ?>
            </h4>
            <p class="help-block">
              <?php print mica_client_commons_get_localized_field($termAttributes->taxonomy, 'descriptions'); ?>
            </p>

            <table class="table table-striped">
              <tbody>
              <?php foreach ($termAttributes->vocabularyTerms as $termAttribute) : ?>
                <tr>
                  <td>
                    <h5>
                      <?php print mica_client_commons_get_localized_field($termAttribute->vocabulary, 'titles'); ?>
                    </h5>

                    <p class="help-block">
                      <?php print mica_client_commons_get_localized_field($termAttribute->vocabulary, 'descriptions'); ?>
                    </p>
                  </td>

                  <td>
                    <?php if (count($termAttribute->terms == 1)): ?>
                      <p data-toggle="tooltip"
                        title="<?php print mica_client_commons_get_localized_field($termAttribute->terms[0], 'descriptions'); ?>">
                      <?php print mica_client_commons_get_localized_field($termAttribute->terms[0], 'titles'); ?>
                      </p>
                    <?php else: ?>
                      <ul>
                        <?php foreach ($termAttribute->terms as $term) : ?>
                          <li data-toggle="tooltip"
                            title="<?php print mica_client_commons_get_localized_field($term, 'descriptions'); ?>">
                          <?php print mica_client_commons_get_localized_field($term, 'titles'); ?>
                          </li>
                        <?php endforeach; ?>
                      </ul>
                    <?php endif; ?>
                  </td>
                </tr>
              <?php endforeach; ?>
              </tbody>
            </table>
            <!--    --><?php //endif; ?>
          <?php endforeach; ?>
        <?php endif; ?>

      </div>
    </div>
  </div>
</section>

<!-- Categories -->
<?php if (!empty($variable_dto->categories)): ?>
  <section>
    <h3><?php print t('Categories') ?></h3>
    <?php print mica_client_variable_get_categories($variable_dto->categories); ?>
  </section>
<?php endif; ?>

<section>
  <h3><?php print t('Statistics') ?></h3>

  <div>
    <div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
      <div id="toempty">
        <img
          src="<?php print base_path() . drupal_get_path('theme', mica_client_commons_get_current_theme()) ?>/img/spin.gif">
      </div>
    </div>

    <div id="param-statistics-chart" var-id="<?php print $variable_dto->id; ?>">
      <div id="toemptychart">
      </div>
    </div>
</section>

<?php if ($variable_dto->variableType != 'Study'): ?>
  <section>
    <h3><?php print t('Harmonization') ?></h3>
    <?php print render($harmonization_table_legend); ?>
    <?php if ($variable_dto->variableType == 'Dataschema'): ?>
      <?php print mica_client_variable_get_harmonizations($variable_dto); ?>

      <?php if (!empty($variable_harmonization_algorithms)): ?>

        <button id="harmo-algo" data-loading-text="<?php print t('Loading...') ?>"
          type="button"
          class="btn btn-success"
          data-toggle="collapse"
          data-target="#harmo-algo"
          aria-expanded="true"
          aria-controls="harmo-algo"
          var-id="<?php print $variable_dto->id; ?>">

        <?php print t('Harmonization Algorithms') ?>
        </button>
        <section id="harmo-algo" class="collapse">

        </section>
      <?php endif; ?>
    <?php else: ?>
      <div class="container-fluid">
        <div class="row">
          <div class="col-xs-6 lg-right-indent">
            <table class="table table-striped">
              <tbody>
              <tr>
                <td><h5><?php print t('Status'); ?></h5></td>
                <td>
                  <?php if (empty($variable_harmonization['status'])): ?>
                    -
                  <?php elseif ($variable_harmonization['status'] == 'complete'): ?>
                    <span class="glyphicon glyphicon-ok alert-success" title="<?php print t('Complete') ?>"></span>
                  <?php
                  elseif ($variable_harmonization['status'] == 'impossible'): ?>
                    <span class="glyphicon glyphicon-remove alert-danger"
                      title="<?php print t('Impossible') ?>"></span>
                  <?php
                  elseif ($variable_harmonization['status'] == 'undetermined'): ?>
                    <span class="glyphicon glyphicon-question-sign alert-warning"
                      title="<?php print t('Undetermined') ?>"></span>
                  <?php endif ?>
                </td>
              </tr>
              <tr>
                <td><h5><?php print t('Comment'); ?></h5></td>
                <td>
                  <p><?php print empty($variable_harmonization['comment']) ? '<i>None</i>' : $variable_harmonization['comment']; ?></p>
                </td>
              </tr>
              </tbody>
            </table>
          </div>
        </div>
      </div>

      <?php if ($variable_harmonization['status'] == 'complete'): ?>
        <?php if (!empty($variable_harmonization['algorithm'])): ?>
          <h3><?php print t('Algorithm') ?></h3>
          <?php print $variable_harmonization['algorithm']; ?>
        <?php else: ?>
          <h5><?php print t('Script'); ?></h5>
          <pre class="prettyprint lang-js">
            <?php print $variable_harmonization['script']; ?>
          </pre>
        <?php endif; ?>
      <?php endif; ?>

    <?php endif; ?>
  </section>
<?php endif; ?>
</article>