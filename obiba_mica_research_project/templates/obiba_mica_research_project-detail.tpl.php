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

<div>
  <div class="row md-bottom-margin">
    <?php if(!empty($project->timestamps)) : ?>
    <div class="col-xs-6"><?php print t('Project created the ') . convert_and_format_string_date($project->timestamps->created); ?></div>
    <?php endif; ?>

    <?php if (!empty($project->request)) : ?>
    <div class="col-xs-6">
      <span><?php print t('Data Access Request') . ': ' ?></span>
      <a href="<?php print MicaClientPathProvider::data_access_request($project->request->id) ?>"><?php print $project->request->id ?></a>
    </div>
    <?php endif; ?>
  </div>

  <hr class="row">

  <div class="row md-bottom-margin">
    <p><?php print obiba_mica_commons_get_localized_field($project, 'title'); ?></p>

    <p><?php print obiba_mica_commons_get_localized_field($project, 'summary'); ?></p>

    <p><?php print $researcher ?></p>

    <p><?php print $institution ?></p>
  </div>
</div>
