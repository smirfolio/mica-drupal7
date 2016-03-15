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

<section id="block-obiba-mica-search-facet-search<?php print $block_html_id; ?>"
  class="boot-collapse block-obiba-mica-search">

  <?php if ($title): ?>

    <h2 class="block-titles">
      <a data-toggle="collapse"
         data-all-collapsed="true"
         data-parent="<?php print $block_html_id; ?>"
         href="#collapse-<?php print $block_html_id; ?>"
         class="collapsed">
        <?php print t($title); ?>
      </a>
    </h2>
    <div class="checkedterms clearfix"></div>
  <?php endif; ?>

  <div class="block-content panel-collapse collapse" id="collapse-<?php print $block_html_id; ?>">
    <?php print render($content) ?>
  </div>

</section> <!-- /.block -->