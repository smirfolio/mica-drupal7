<?php //dvm('search var',$studies);
?>
<div id="search-facets">
  <ul class="nav nav-tabs facets-tab no-border" role="tablist" id="facet-search">
  <?php if (!empty($obiba_mica_study)): ?>
    <li class="active"><a href="#study-facet" role="tab" data-toggle="tab"> <?php print t('Studies') ?> </a></li>
    <li><a href="#variable-facet" role="tab" data-toggle="tab"><?php print t('Variables') ?> </a></li>
  <?php endif; ?>
    <li class="pull-right nonactive monospace"><a href="" id="facets-expand-collapse">[+]</a></li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content bordered-tab-content">
    <?php if (!empty($obiba_mica_study)): ?>
      <div class="tab-pane" id="variable-facet"> <?php print render($obiba_mica_variable); ?></div>
      <div class="tab-pane active" id="study-facet"> <?php print  render($obiba_mica_study); ?></div>
    <?php else: ?>
      <div class="tab-pane active" id="variable-facet"> <?php print render($obiba_mica_variable); ?></div>
    <?php endif; ?>
  </div>
</div>