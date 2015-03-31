<div class="panel-group">
  <div class="panel panel-default">
    <div class="panel-heading no-border-radius">
      <div class="panel-title">
        <a id="collapsible-taxonomy" class="accordion-toggle" data-all-collapsed="true" data-toggle="collapse" href="#taxonomy-<?php print $name?>">
          <span><?php print $title; ?></span>
        </a>
      </div>
    </div>
    <div id="taxonomy-<?php print $name?>" class="panel-collapse collapse in">
      <div class="panel-body no-padding">
        <div class="block-content panel-collapse">
          <?php print $content ?>
        </div>
      </div>
    </div>
  </div>
</div>