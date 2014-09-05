<?php //dpm($charts);?>

<div class="panel panel-default">
  <?php $nch = 0; ?>
  <?php foreach ($charts as $chart) : ?>
    <?php if ($nch < 3) : ?>
      <div class="col-md-4"><?php print render($chart); ?> </div>
    <?php endif; ?>
    <?php $nch++; ?>
  <?php endforeach; ?>


  <div id="collapseOne" class="charts panel-collapse collapse">
    <div class="panel-body">
      <div class="row">
        <?php $nch = 0; ?>
        <?php foreach ($charts as $chart) : ?>
          <?php if ($nch > 3) : ?>
            <div class="col-md-4"><?php print render($chart); ?> </div>
          <?php endif; ?>
          <?php $nch++; ?>
        <?php endforeach; ?>
      </div>
    </div>
  </div>
  <div class="botton-container">
    <span class="panel-title show-button">
    <a class="text-button-field" data-toggle="collapse" data-parent="#accordion" href="#collapseOne">
      <?php print t('Show all') ?>
    </a>
      </span>
  </div>
</div>