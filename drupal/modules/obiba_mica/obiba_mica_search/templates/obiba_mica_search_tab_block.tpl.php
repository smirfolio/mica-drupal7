<?php //dvm('search var',$studies);
?>
<div id="search-facets" class="hide">
  <ul class="nav nav-tabs facets-tab no-border" role="tablist" id="facet-search">
    <li class="active"><a href="#study-facet" role="tab" data-toggle="tab"> <?php print t('Studies') ?> </a></li>
    <li><a href="#variable-facet" role="tab" data-toggle="tab"><?php print t('Variables') ?> </a></li>
    <li class="pull-right nonactive monospace">
      <a href="" data-all-collapsed="true" id="facets-expand-collapse"><i class="glyphicon glyphicon-plus"></i></a>
    </li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content bordered-tab-content">
    <div class="tab-pane" id="variable-facet"> <?php print render($obiba_mica_variable); ?></div>
    <div class="tab-pane active" id="study-facet"> <?php print  render($obiba_mica_study); ?></div>
  </div>
</div>