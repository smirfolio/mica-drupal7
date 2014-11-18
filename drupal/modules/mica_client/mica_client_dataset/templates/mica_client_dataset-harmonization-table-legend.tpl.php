<div class="lg-top-margin lg-bottom-margin">
  <div class="coverage-table-legend">
    <i class="glyphicon glyphicon-question-sign alert-warning"></i>
    <span class="coverage-table-legend-title"><?php print t('Undetermined') ?></span>
          <span class="coverage-table-legend-description">
            <?php print ' - ' . t('the harmonization potential of this variable has not yet been evaluated.') ?>
          </span>
  </div>
  <div class="coverage-table-legend sm-top-margin">
    <i class="glyphicon glyphicon-ok alert-success"></i>
    <span class="coverage-table-legend-title"><?php print t('Complete') ?></span>
          <span class="coverage-table-legend-description">
            <?php print ' - ' . t('the study assessment item(s) (e.g. survey question, physical measure, biochemical measure) allow construction of the variable as defined in the dataset.') ?>
          </span>
  </div>
  <div class="coverage-table-legend sm-top-margin">
    <i class="glyphicon glyphicon-remove alert-danger"></i>
    <span class="coverage-table-legend-title"><?php print t('Impossible') ?></span>
          <span class="coverage-table-legend-description">
            <?php print ' - ' . t('there is no information or insufficient information collected by this study to allow the construction of the variable as defined in the dataset.') ?>
          </span>
  </div>
</div>
