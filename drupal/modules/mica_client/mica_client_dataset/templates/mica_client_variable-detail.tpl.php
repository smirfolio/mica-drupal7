<?php
//dpm($variable_dto);
//dpm($variable_harmonization);
?>

<?php if (!empty($variable_dto->description)): ?>
  <p><?php print $variable_dto->description; ?></p>
<?php endif; ?>

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
                <p>
                  <?php
                  foreach ($variable_dto->studySummaries as $studySummary) {
                    print l(mica_client_commons_get_localized_field($studySummary, 'name'), 'mica/study/' . $studySummary->id .
                      '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($studySummary, 'name')));
                  }
                  ?>
                </p>
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

          <tr>
            <td><h5><?php print t('Variable Type'); ?></h5></td>
            <td>
              <p>
                <?php print t($variable_dto->variableType); ?>
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
        <!-- Categories -->
        <?php if (!empty($variable_dto->categories)): ?>
          <h3><?php print t('Categories') ?></h3>
          <?php print mica_client_variable_get_categories($variable_dto->categories); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
</section>

<!-- Taxonomy terms -->
<?php if (!empty($variable_dto->termAttributes)): ?>

  <?php foreach ($variable_dto->termAttributes as $termAttributes) : ?>
    <section>
      <h3>
        <?php print mica_client_commons_get_localized_field($termAttributes->taxonomy, 'titles'); ?>
      </h3>

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


    </section>
  <?php endforeach; ?>
<?php endif; ?>

<section>
  <h3><?php print t('Statistics') ?></h3>

  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 lg-right-indent">

        <div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
          <div id="txtblnk"> <?php print t('Please wait loading Statistics table....'); ?> </div>
        </div>
      </div>
      <div class="col-xs-6">
        <div class="alert alert-info" role="alert"><strong>TODO</strong> charts here</div>
      </div>
    </div>
  </div>
</section>

<?php if ($variable_dto->variableType != 'Study'): ?>
  <section>
    <h3><?php print t('Harmonization') ?></h3>
    <?php if ($variable_dto->variableType == 'Dataschema'): ?>
      <?php print mica_client_variable_get_harmonizations($variable_dto); ?>
    <?php endif; ?>

    <?php if (!empty($variable_harmonization)): ?>
      <h5><?php print t('Status'); ?></h5>
      <p><?php print t($variable_harmonization['status']); ?></p>

      <h5><?php print t('Comment'); ?></h5>
      <p><?php print empty($variable_harmonization['comment']) ? '<i>None</i>' : $variable_harmonization['comment']; ?></p>

      <h5><?php print t('Script'); ?></h5>

      <?php print $variable_harmonization['script']; ?>
    <?php endif; ?>
  </section>
<?php endif; ?>

<!--  <section>-->
<!--    <div class="container-fluid">-->
<!--      <div class="row">-->
<!--        <div class="col-xs-6 lg-right-indent">-->
<!--        </div>-->
<!--        <div class="col-xs-6">-->
<!--        </div>-->
<!--      </div>-->
<!--    </div>-->
<!--  </section>-->

</article>