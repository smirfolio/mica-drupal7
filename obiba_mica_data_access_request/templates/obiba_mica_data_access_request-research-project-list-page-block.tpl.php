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

<tr>
  <?php if(obiba_mica_user_has_role('mica-data-access-officer')) : ?>
    <td>
      <?php
      if (!empty($project->request)) :
        print($project->request->applicant);
      endif;
      ?>
    </td>
  <?php endif; ?>
  <td>
    <?php print MicaClientPathProvider::project($project->id, obiba_mica_commons_get_localized_field($project, 'title')) ?>
  </td>
  <td>
    <?php if (!empty($project->request)) : ?>
      <?php if ($project->request->viewable) : ?>
        <?php print MicaClientPathProvider::data_access_request($project->request->id) ?>
      <?php else : ?>
        <span><?php print $project->request->id ?></span>
      <?php endif; ?>
    <?php endif ;?>
  </td>
  <td>
    <?php
    if (!empty($content->startDate)) :
      print(obiba_mica_commons_convert_and_format_string_date($content->startDate, 'D. d-m-Y'));
    endif;
    ?>
  </td>
  <td>
    <?php
    if (!empty($content->endDate)) :
      print(obiba_mica_commons_convert_and_format_string_date($content->endDate, 'D. d-m-Y'));
    endif;
    ?>
  </td>
</tr>
