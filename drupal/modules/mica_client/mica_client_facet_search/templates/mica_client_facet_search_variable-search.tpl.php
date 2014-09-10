<?php //dvm('search var',$studies);
// dvm('search var', current($variables));
?>
<div id="search-result">
  <ul class="nav nav-tabs" role="tablist">
    <li class="active"><a href="#variable" role="tab" data-toggle="tab"><?php print t('Variables') ?> </a></li>
    <li><a href="#study" role="tab" data-toggle="tab"> <?php print t('Studies') ?> </a></li>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variable">

      <?php print $variable_charts; ?>
      <?php print current($variables); ?>
    </div>
    <div class="tab-pane" id="study">
      <?php print $study_charts; ?>
      <?php print $studies; ?>
    </div>

  </div>
</div>