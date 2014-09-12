<?php //dvm('search var',$studies);
//dpm($variables_result);
?>
<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
  <li class="active"><a href="#variables" role="tab" data-toggle="tab"><?php print t('Variables') ?>
        <?php if (!empty($variables_result['totalHits'])) : ?>
          (  <?php print $variables_result['totalHits']; ?> )
        <?php endif; ?>
      </a></li>

    <li><a href="#studies" role="tab" data-toggle="tab"> <?php print t('Studies') ?>
        <?php if (!empty($studies['totalHits'])) : ?>
          (  <?php print $studies['totalHits']; ?> )
        <?php endif; ?>
      </a></li>

    <li><a href="#networks" role="tab" data-toggle="tab"> <?php print t('Networks') ?>
        <?php if (!empty($networks['totalHits'])) : ?>
          (  <?php print $networks['totalHits']; ?> )
        <?php endif; ?>
      </a></li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variables">
    <?php print $variable_charts; ?>
    <?php print $variables_result['data']; ?>
    </div>

    <div class="tab-pane" id="studies">
    <?php print $study_charts; ?>
    <?php print $studies['data']; ?>
    </div>
    <div class="tab-pane" id="networks">
      <?php print $study_charts; ?>
      <?php print $networks['data']; ?>
    </div>

  </div>
</div>