<?php //dpm($charts);?>

<div class="panel panel-default">
  <div class="panel-heading">
    <h4 class="panel-title">
      <a data-toggle="collapse" data-parent="#accordion" href="#collapseOne">
        <?php print t('Show all charts') ?>
      </a>
    </h4>
  </div>
  <div id="collapseOne" class="charts panel-collapse collapse">
    <div class="panel-body">
      <div class="row">
        <?php foreach ($charts as $chart) : ?>
          <div class="col-md-4"><?php print render($chart); ?> </div>
        <?php endforeach; ?>
      </div>
    </div>
  </div>

</div>