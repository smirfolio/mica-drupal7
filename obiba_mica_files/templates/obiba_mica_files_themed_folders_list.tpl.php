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

<?php if (!empty($folder_path)): ?>
  <tr>
    <td>
      <div style="margin-left:  <?php print 5 * $indent ?>px;">
        <?php str_repeat('&nbsp;', $indent); ?>
        <i class="glyphicon glyphicon-folder-close"></i>
        <?php print $folder_path; ?>
      </div>
    </td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
<?php endif; ?>
<?php print $list_files; ?>




