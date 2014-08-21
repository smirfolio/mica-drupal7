<?php
//dpm($variable_dto);
?>

<h3><?php print t('General Information') ?></h3>

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
      print l(mica_client_commons_get_localized_field($studySummary, 'acronym'), 'mica/study/' . $studySummary->id .
          '/' . $studySummary->id) . '</br>';
    }
    ?>
  </p>
<?php endif; ?>

<?php if (!empty($variable_dto->datasetId)): ?>
  <h5><?php print t('Dataset'); ?></h5>
  <p>
    <?php
    print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/dataset/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')) .
        '/dataset/' . $variable_dto->datasetId) . '</br>';
    ?>
  </p>
<?php endif; ?>

<h5><?php print t('Value Type'); ?></h5>
<p><?php print t($variable_dto->valueType); ?></p>

<h5><?php print t('Variable Type'); ?></h5>
<p><?php print t($variable_dto->variableType); ?></p>

<?php if (!empty($variable_dto->comment)): ?>
  <h5><?php print t('Comment'); ?></h5>
  <p><?php print($variable_dto->comment); ?></p>
<?php endif; ?>

<?php if (!empty($variable_dto->categoriestab)): ?>
  <h3><?php print t('Categories') ?></h3>
  <p><?php print($variable_dto->categoriestab); ?></p>
<?php endif; ?>

<h3><?php print t('Statistics') ?></h3>

<div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
  <div id="txtblnk"> <?php print t('Please wait loading Statistics table....'); ?> </div>
</div>

<?php if (!empty($variable_dto->harmonizationtab)): ?>
  <h3><?php print t('Harmonization') ?></h3>
  <?php print($variable_dto->harmonizationtab); ?>
<?php endif; ?>

