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

/**
 * @file
 * Code for the obiba_mica_files modules.
 *
 * @author Obiba <info@obiba.org>
 *
 */

?>

<tr>
  <td>
    <div style="margin-left:  <?php print 5 * $indent ?>px;">
      <a
        id="download-attachment"
        entity="<?php print $entity_type ?>"
        id_entity="<?php print $id_entity ?>"
        file_name="<?php print rawurlencode($attachment->fileName) ?>"
        file_path="<?php print $attachment->path ?>"
        download="<?php print rawurldecode($attachment->fileName); ?>">
        <span class="glyphicon glyphicon-download"></span>
        <?php print urldecode($attachment->fileName); ?>
      </a>
    </div>
  </td>
  <td>
    <?php if (!empty($attachment->type)): ?>
      <?php $types = explode(',', $attachment->type) ?>
      <div>
        <?php foreach ($types as $type): ?>
          <span class="label label-default"><?php print $type; ?></span>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>
  </td>
  <td>
    <?php
    print obiba_mica_commons_get_localized_field($attachment, 'description');
    ?>
  </td>
  <td>
    <?php if (!empty($attachment->timestamps->lastUpdate)): ?>
      <?php print
        format_date(strtotime($attachment->timestamps->lastUpdate), 'custom', 'm/d/Y');
      ?>
    <?php endif; ?>
  </td>
</tr>