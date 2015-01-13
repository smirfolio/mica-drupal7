<?php //dpm($charts);?>

<div class="lg-top-padding">
  <div class="row">
    <?php $nch = 0; ?>
    <?php foreach ($charts as $chart) : ?>
      <?php if ($nch < 4) : ?>
        <div class="col-md-3"><?php print render($chart); ?> </div>
      <?php endif; ?>
      <?php $nch++; ?>
    <?php endforeach; ?>

  </div>

  <div id="collapseOne" class="charts panel-collapse collapse">
    <div class="panel-body">
      <div class="row">
        <?php $nch = 0; ?>
        <?php foreach ($charts as $chart) : ?>
          <?php if ($nch > 4) : ?>
            <div class="col-md-3"><?php print render($chart); ?> </div>
          <?php endif; ?>
          <?php $nch++; ?>
        <?php endforeach; ?>
      </div>
    </div>

  </div>
  <div class="bottom-container">
    <span class="panel-title show-button">
      <small>
        <a class="text-button-field" data-toggle="collapse" data-parent="#accordion" href="#collapseOne">
          <?php print t('Show all') ?>
        </a>
      </small>
      </span>
  </div>
</div>