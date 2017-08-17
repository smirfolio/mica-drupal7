<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<?php
print render($node_page) ?>

<div class="list-page">

  <div class="row">
    <?php
    $count = empty($total_items) ? 0 : $total_items;
    $caption = $count < 2 ? $localize->getTranslation('study.label') : $localize->getTranslation('studies');
    ?>
    <div class="col-md-2 col-sm-2 col-xs-4 min-height-align search-count">
      <?php if (variable_get_value('studies_list_show_studies_count_caption')): ?>
      <span id="refresh-count">
        <?php print $count ?>
      </span>
      <span id="refresh-count">
        <?php print $caption ?>
      </span>
      <?php endif; ?>
    </div>

    <div class="col-md-10  col-sm-10 col-xs-8 min-height-align pull-right">
      <div class="hidden-xs inline pull-left">
        <?php print render($form_search); ?>
      </div>
      <div class="btn-group pull-right">
        <?php if (variable_get_value('study_list_show_search_button')): ?>
          <?php
            print MicaClientAnchorHelper::searchStudies(TRUE,
              DrupalMicaStudyResource::mapTypeToClassName($study_type));
          ?>
        <?php endif; ?>
      </div>
    </div>


  </div>

  <div id="refresh-list">
    <?php if (!empty($list_studies)): ?>
      <?php print render($list_studies); ?>
    <?php endif; ?>
  </div>
  <div class="clearfix"></div>
  <div test-ref="pager"><?php print $pager_wrap; ?></div>

</div>
