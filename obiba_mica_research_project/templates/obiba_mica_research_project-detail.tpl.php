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


<div class="row md-top-margin">
  <div class="col-xs-12">
    <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($project, 'summary')) ?>
  </div>
</div>

<article class="bordered-article md-top-margin">
  <section>
    <div class="row">
      <div class="col-lg-6 col-xs-12">
        <h2><?php print t('General Information') ?></h2>
        <table class="table table-striped">
          <tbody>
          <?php if(!empty($content->startDate)) : ?>
            <tr>
              <th><?php print t('Start Date') ?></th>
              <td>
                <p><?php print obiba_mica_commons_convert_and_format_string_date($content->startDate, 'd-m-Y') ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if(!empty($content->endDate)) : ?>
            <tr>
              <th><?php print t('End Date') ?></th>
              <td>
                <p><?php print obiba_mica_commons_convert_and_format_string_date($content->endDate, 'd-m-Y') ?></p>
              </td>
            </tr>  
          <?php endif; ?>

          <?php if (module_exists('obiba_mica_data_access_request') && (!empty($project->request) && $project->request->viewable)) : ?>
            <tr>
              <th><?php print t('Data Access Request') ?></th>
              <td>
                <p>
                  <a href="<?php print MicaClientPathProvider::data_access_request($project->request->id) ?>">
                    <?php print $project->request->id ?>
                  </a>
                </p>
              </td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>
      </div>
      <?php if(!empty($content->name) || !empty($content->institution)) : ?>
      <div class="col-lg-6 col-xs-12">
        <h2><?php print t('Contact Details') ?></h2>
        <table class="table table-striped">
          <tbody>
          <?php if(!empty($content->name)) : ?>
            <tr>
              <th><?php print t('Name') ?></th>
              <td>
                <p><?php print $content->name ?></p>
              </td>
            </tr>
          <?php endif; ?>
          <?php if (!empty($content->institution)) : ?>
            <tr>
              <th><?php print t('Institution') ?></th>
              <td>
                <p><?php print $content->institution ?></p>
              </td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>
      </div>
      <?php endif; ?>
    </div>
  </section>

  <?php if (!empty($attachments)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print (!empty($file_browser) ? $file_browser : $attachments); ?>
    </section>
  <?php endif; ?>

</article>
