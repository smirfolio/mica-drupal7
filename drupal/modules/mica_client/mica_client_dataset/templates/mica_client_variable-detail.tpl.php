<?php
//dpm($variable_dto);
//dpm($variable_harmonization);
?>
<article>

  <section>
    <h3><?php print t('General Information') ?></h3>

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 right-indent">


          <div>
            <?php if (!empty($variable_dto->label)): ?>
              <h5><?php print t('Label') ?></h5>
              <p><?php print $variable_dto->label; ?></p>
            <?php endif; ?>

            <?php if (!empty($variable_dto->description)): ?>
              <h5><?php print t('Description'); ?></h5>
              <p><?php print $variable_dto->description; ?></p>
            <?php endif; ?>

            <?php if (!empty($variable_dto->studySummaries)): ?>
              <h5>
                <?php if ($variable_dto->variableType == 'Dataschema') {
                  print t('Studies');
                }
                else {
                  print t('Study');
                }?>
              </h5>
              <p>
                <?php
                foreach ($variable_dto->studySummaries as $studySummary) {
                  print l(mica_client_commons_get_localized_field($studySummary, 'name'), 'mica/study/' . $studySummary->id .
                    '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($studySummary, 'name')));
                }
                ?>
              </p>
            <?php endif; ?>

            <?php if (!empty($variable_dto->datasetId)): ?>
              <h5><?php print t('Dataset'); ?></h5>
              <p>
                <?php
                print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/' . mica_client_variable_dataset_type($variable_dto)
                  . '/' . $variable_dto->datasetId . '/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')));
                ?>
              </p>
            <?php endif; ?>

            <h5><?php print t('Entity Type'); ?></h5>

            <p><?php print t($variable_dto->entityType); ?></p>

            <h5><?php print t('Value Type'); ?></h5>

            <p><?php print t($variable_dto->valueType); ?></p>

            <h5><?php print t('Variable Type'); ?></h5>

            <p>
              <?php print t($variable_dto->variableType); ?>
              <?php if ($variable_dto->variableType == 'Harmonized'): ?>
                <?php
                print '(' . l($variable_dto->name, 'mica/variable/' . $variable_dto->datasetId . ':' . $variable_dto->name
                    . ':Dataschema' . '/' . mica_client_commons_to_slug($variable_dto->name)) . ')';
                ?>
              <?php endif; ?>
            </p>

            <?php if (!empty($variable_dto->comment)): ?>
              <h5><?php print t('Comment'); ?></h5>
              <p><?php print($variable_dto->comment); ?></p>
            <?php endif; ?>
          </div>
        </div>
        <div class="col-xs-6">
          <?php if (!empty($variable_dto->categories)): ?>
            <h5><?php print t('Categories') ?></h5>
            <p><?php print mica_client_variable_get_categories($variable_dto->categories); ?></p>
          <?php endif; ?>
          <?php if (!empty($variable_dto->attributes)): ?>
            <h5><?php print t('Attributes') ?></h5>
            <p><?php print mica_client_dataset_attributes_tab($variable_dto->attributes, 'maelstrom', array(
                'description',
                'comment',
                'status'
              )); ?></p>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </section>

  <section>
    <h3><?php print t('Statistics') ?></h3>

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 right-indent">

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
  <!--        <div class="col-xs-6 right-indent">-->
  <!--        </div>-->
  <!--        <div class="col-xs-6">-->
  <!--        </div>-->
  <!--      </div>-->
  <!--    </div>-->
  <!--  </section>-->

</article>