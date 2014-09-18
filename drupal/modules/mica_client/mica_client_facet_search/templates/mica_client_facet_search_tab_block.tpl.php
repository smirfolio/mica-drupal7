<?php //dvm('search var',$studies);
?>
<div id="search-facets">
  <ul class="nav nav-tabs facets-tab" role="tablist" id="facet-search">
    <li class="active"><a href="#variable-facet" role="tab" data-toggle="tab"><?php print t('Variables') ?> </a></li>
    <li><a href="#study-facet" role="tab" data-toggle="tab"> <?php print t('Studies') ?> </a></li>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-facets">
    <div class="tab-pane active" id="variable-facet"> <?php print render($mica_client_variable); ?></div>
    <div class="tab-pane" id="study-facet"> <?php print  render($mica_client_study); ?></div>

  </div>
</div>