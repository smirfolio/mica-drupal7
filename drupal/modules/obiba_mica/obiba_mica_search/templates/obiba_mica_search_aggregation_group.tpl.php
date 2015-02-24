<div class="panel-group ">
  <div class="panel panel-default">
    <div class="panel-heading no-border-radius">
      <div class="panel-title">
        <a data-toggle="collapse" data-parent="#accordion" href="#<?php print $name?>"><?php print $title; ?></a>
      </div>
    </div>
    <div id="<?php print $name?>" class="panel-collapse collapse in">
      <div class="panel-body no-padding">
        <div class="block-content panel-collapse">
          <?php print $content ?>
        </div>
      </div>
    </div>
  </div>
</div>