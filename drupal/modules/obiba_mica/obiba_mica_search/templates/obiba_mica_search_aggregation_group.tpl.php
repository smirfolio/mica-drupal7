<div class="panel-group">
  <div class="panel panel-default">
    <div class="panel-heading no-border-radius">
      <div class="panel-title">
        <span id="panel-title-icon" data-id="<?php print $name?>">
          <a id="collapsible-taxonomy"
             class="accordion-toggle collapsed"
             data-all-collapsed="true"
             data-toggle="collapse"
             href="#taxonomy-<?php print $name?>">
            <span><i class="glyphicon glyphicon-chevron-right"></i></span><span id=""><?php print $title; ?></span>
          </a>
        </span>
      </div>
    </div>
    <div id="taxonomy-<?php print $name?>" class="panel-collapse collapse">
      <div class="panel-body no-padding">
        <div class="block-content panel-collapse">
          <a href="" class="pull-right " data-all-collapsed="true" data-id="<?php print $name?>" id="group-expand-collapse-<?php print $name?>">
            <i class="glyphicon glyphicon-plus"></i>
          </a>
          <?php print $content ?>
        </div>
      </div>
    </div>
  </div>
</div>