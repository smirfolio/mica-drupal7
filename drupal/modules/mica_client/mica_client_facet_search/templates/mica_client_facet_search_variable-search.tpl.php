<?php //dvm('search var',$studies);
//dpm($variables_result);
?>

<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
    <li class="active"><a href="#variables" role="tab" data-toggle="tab"><?php print t('Variables') ?>
        <?php if (!empty($variable_totalHits)) : ?>
          (  <?php print $variable_totalHits; ?> )
        <?php endif; ?>
      </a></li>

    <li><a href="#studies" role="tab" data-toggle="tab"> <?php print t('Studies') ?>
        <?php if (!empty($study_totalHits)) : ?>
          (  <?php print $study_totalHits; ?> )
        <?php endif; ?>
      </a></li>

    <li><a href="#networks" role="tab" data-toggle="tab"> <?php print t('Networks') ?>
        <?php if (!empty($network_totalHits)) : ?>
          (  <?php print $network_totalHits; ?> )
        <?php else : ?>
          (<?php print 0; ?>)
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