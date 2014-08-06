<?php
//dpm($variable_dto);
?>
  <article>
    <header>
    </header>
    <footer>
    </footer>
  </article>

<?php if (!empty($variable_dto->datasetName) || !empty($variable_dto->studyIds) ||
  !empty($variable_dto->name) ||
  !empty($variable_dto->valueType) || !empty($variable_dto->attributes) ||
  !empty($variable_dto->description) || !empty($variable_dto->comment) ||
  !empty($variable_dto->label)
): ?>
  <section class="block">
  <h2><?php print t('General Information') ?></h2>

  <div>

    <?php if (!empty($variable_dto->label)): ?>
      <div class="field field-name-field-label field-type-text  clearfix">
        <div class="field-label"><?php print t('Label') ?> :</div>
        <div class="field-items">
          <div class="field-item even">
            <?php print $variable_dto->label; ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!empty($variable_dto->description)): ?>
      <div class="field field-name-description field-type-list-boolean clearfix">
        <div class="field-label">
          <?php print t('Description'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php print $variable_dto->description; ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!empty($variable_dto->studyIds)): ?>
      <div class="field field-name-field-studyIds field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Studies'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">

            <?php
            foreach ($variable_dto->studyIds as $stuyId) {
              print l($stuyId, 'mica/study/' . $stuyId .
                  '/' . $stuyId) . '</br>';
            }

            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!empty($variable_dto->datasetId)): ?>
      <div class="field field-name-field-datasetName field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Dataset'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/dataset/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')) .
                '/dataset/' . $variable_dto->datasetId) . '</br>';
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!empty($variable_dto->valueType)): ?>
      <div class="field field-name-field-valueType field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Value Type'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print($variable_dto->valueType);
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!empty($variable_dto->comment)): ?>
      <div class="field field-name-field-comment field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Value Type'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print($variable_dto->comment);
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>


    <div class="field field-name-field-statistics field-type-list-boolean  clearfix">
      <div class="field-label">
        <?php print t('Statistics'); ?>
      </div>

      <div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
        <div id="txtblnk"> <?php print t('Please wait loading Statistics table....'); ?> </div>
      </div>
    </div>
  </div>

  <?php if (!empty($variable_dto->categoriestab)): ?>
    <div class="field field-name-field-comment field-type-list-boolean  clearfix">
      <div class="field-label">
        <?php print t('Categories'); ?> :
      </div>
      <div class="field-items">
        <div class="field-item even">
          <?php
          print($variable_dto->categoriestab);
          ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

<?php endif; ?>
