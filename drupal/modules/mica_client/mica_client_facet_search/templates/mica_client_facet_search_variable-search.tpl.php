<?php //dvm('search var',$studies);
// dvm('search var', current($variables));
?>
<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
    <li class="active"><a href="#variables" role="tab" data-toggle="tab"><?php print t('Variables') ?> </a></li>
    <li><a href="#studies" role="tab" data-toggle="tab"> <?php print t('Studies') ?> </a></li>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variables">

    <?php print $variable_charts; ?>
      <?php print current($variables); ?>
    </div>
    <div class="tab-pane" id="studies">
    <?php print $study_charts; ?>
      <?php print $studies; ?>
    </div>

  </div>
</div>