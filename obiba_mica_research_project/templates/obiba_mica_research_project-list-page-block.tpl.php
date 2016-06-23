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

<div class="row sm-bottom-margin document-item-list flex-row">
  <div class="col-xs-12">
    <div>
      <h4>
        <a href="<?php print MicaClientPathProvider::project($project->id); ?>">
          <?php print obiba_mica_commons_get_localized_field($project, 'title') ?>
        </a>
      </h4>
    </div>
    <p class="md-top-margin">
      <small>
        <?php print obiba_mica_commons_get_localized_field($project, 'summary') ?>
      </small>
    </p>
    <p class="md-top-margin">
      <div class="row">
        <div class="col-xs-3">
          <?php
            if (!empty($content->startDate)) :
              print(t('Start Date') . ': ' . obiba_mica_commons_convert_and_format_string_date($content->startDate, 'd-m-Y'));
            endif;
          ?>
        </div>
        <div class="col-xs-3">
          <?php
            if (!empty($content->endDate)) :
              print(t('End Date') . ': ' . obiba_mica_commons_convert_and_format_string_date($content->endDate, 'd-m-Y'));
            endif;
          ?>
        </div>
      </div>
    </p>
  </div>
</div>
