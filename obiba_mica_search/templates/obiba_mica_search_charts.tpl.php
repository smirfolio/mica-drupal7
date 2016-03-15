<?php
/**
 * @file
 * Obiba Mica Module.
 *
 * Copyright (c) 2016 OBiBa. All rights reserved.
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

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