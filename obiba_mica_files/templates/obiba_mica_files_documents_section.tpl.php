<?php
/**
 * @file
 * Code for the obiba_mica_dataset modules.
 */

?>
<!--
  ~ Copyright (c) 2015 OBiBa. All rights reserved.
  ~
  ~ This program and the accompanying materials
  ~ are made available under the terms of the GNU Public License v3.0.
  ~
  ~ You should have received a copy of the GNU General Public License
  ~ along with this program.  If not, see <http://www.gnu.org/licenses/>.
  -->

<?php if (!empty($attachments)): ?>
  <section>
    <h2 id="documents"><?php print t('Documents'); ?></h2>
    <div>
        <ul class="list-group">
          <?php print $attachments; ?>
        </ul>
    </div>
  </section>
<?php endif; ?>

