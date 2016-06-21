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

<article class="bordered-article">

  <section>
    <h2><?php print t('General Information') ?></h2>

    <div class="row">
      <div class="col-lg-6 col-xs-12 lg-right-indent">
        <table class="table table-striped">
          <tbody>
          <tr>
            <th><?php print t('Title') ?></th>
            <td>
              <p><?php print obiba_mica_commons_get_localized_field($project, 'title') ?></p>
            </td>
          </tr>
          <tr>
            <th><?php print t('Description') ?></th>
            <td>
              <p><?php print obiba_mica_commons_get_localized_field($project, 'summary') ?></p>
            </td>
          </tr>
          <?php if(!empty($content->startDate)) : ?>
            <tr>
              <th><?php print t('Start Date') ?></th>
              <td>
                <p><?php print convert_and_format_string_date($content->startDate, 'd-m-Y') ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if(!empty($content->endDate)) : ?>
            <tr>
              <th><?php print t('End Date') ?></th>
              <td>
                <p><?php print convert_and_format_string_date($content->endDate, 'd-m-Y') ?></p>
              </td>
            </tr>  
          <?php endif; ?>

          <?php if (!empty($project->request) && $project->request->viewable) : ?>
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
    </div>
  </section>

  <?php if(!empty($content->name) || !empty($content->institution)) : ?>
  <section>
    <h2><?php print t('Contact Details') ?></h2>
    
    <div class="row">
      <div class="col-lg-6 col-xs-12 lg-right-indent">
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
    </div>
  </section>
  <?php endif; ?>

  <?php if (!empty($attachments)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print (!empty($file_browser) ? $file_browser : $attachments); ?>
    </section>
  <?php endif; ?>

</article>
