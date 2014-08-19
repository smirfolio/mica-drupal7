<?php
//dpm($variable_dto);
?>

<h2><?php print t('General Information') ?></h2>

<?php if (!empty($variable_dto->label)): ?>
  <h4><?php print t('Label') ?></h4>
  <p><?php print $variable_dto->label; ?></p>
<?php endif; ?>

<?php if (!empty($variable_dto->description)): ?>
  <h4><?php print t('Description'); ?></h4>
  <p><?php print $variable_dto->description; ?></p>
<?php endif; ?>

<?php if (!empty($variable_dto->studyIds)): ?>
  <h4>
    <?php if ($variable_dto->variableType == 'Dataschema') {
      print t('Studies');
    }
    else {
      print t('Study');
    }?>
  </h4>
  <p>
    <?php
    foreach ($variable_dto->studyIds as $stuyId) {
      print l($stuyId, 'mica/study/' . $stuyId .
          '/' . $stuyId) . '</br>';
    }
    ?>
  </p>
<?php endif; ?>

<?php if (!empty($variable_dto->datasetId)): ?>
  <h4><?php print t('Dataset'); ?></h4>
  <p>
    <?php
    print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/dataset/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')) .
        '/dataset/' . $variable_dto->datasetId) . '</br>';
    ?>
  </p>
<?php endif; ?>

<h4><?php print t('Value Type'); ?></h4>
<p><?php print t($variable_dto->valueType); ?></p>

<h4><?php print t('Variable Type'); ?></h4>
<?php print t($variable_dto->variableType); ?>

<?php if (!empty($variable_dto->comment)): ?>
  <h4><?php print t('Comment'); ?></h4>
  <?php print($variable_dto->comment); ?>
<?php endif; ?>

<?php if (!empty($variable_dto->categoriestab)): ?>
  <h2><?php print t('Categories') ?></h2>
  <?php print($variable_dto->categoriestab); ?>
<?php endif; ?>

<h2><?php print t('Statistics') ?></h2>

<div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
  <div id="txtblnk"> <?php print t('Please wait loading Statistics table....'); ?> </div>
</div>

<?php if (!empty($variable_dto->harmonizationtab)): ?>
  <h2><?php print t('Harmonization') ?></h2>
  <?php print($variable_dto->harmonizationtab); ?>
<?php endif; ?>

