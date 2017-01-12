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

<?php if (!empty($attachments)): ?>
    <div class="table-responsive">
      <table class="table table-striped table-condensed table-bordered">
        <thead>
        <tr>
          <th width="45%"><?php print $localize->getTranslation('name'); ?></th>
          <th><?php print $localize->getTranslation('type'); ?></th>
          <th width="30%"><?php print $localize->getTranslation('description'); ?></th>
          <th><?php print $localize->getTranslation('last-modified'); ?></th>
        </tr>
        </thead>
        <tbody>
        <?php print $attachments; ?>
        </tbody>
      </table>
    </div>
<?php endif; ?>

