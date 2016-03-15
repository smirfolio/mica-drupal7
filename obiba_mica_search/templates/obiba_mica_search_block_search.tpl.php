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

<?php $style_hide = ''; ?>
<?php if (!empty($input_autocomplete)) : ?>
  <?php print render($input_autocomplete); ?>
  <?php $style_hide = "style='display: none'"; ?>
<?php endif; ?>

<div <?php print $style_hide; ?>>
  <form id="facet-search-<?php print $formId; ?>">
    <?php $nbr = 0 ?>
    <?php foreach ($items as $term => $term_count): ?>
      <?php if ($nbr < 5): ?>
        <label class="span-checkbox">
          <?php print render($term_count); ?>
        </label>
      <?php endif; ?>
      <?php $nbr++ ?>
    <?php endforeach; ?>

    <div class="expand-see-more expand-control-div-<?php print $formId; ?> collapse"
      id="block-search<?php print $formId; ?>">
      <?php $nch = 0; ?>
      <?php foreach ($items as $term => $term_count): ?>
        <?php if ($nch > 4) : ?>
          <label class="span-checkbox">
            <?php print render($term_count); ?>
          </label>
        <?php endif; ?>
        <?php $nch++; ?>
      <?php endforeach; ?>

    </div>
    <?php if ($nch > 5) : ?>
      <div class="expand-control" id="<?php print $formId; ?>">
        <a id="<?php print $formId; ?>"
          class="btn btn-primary btn-xs  expand-control-link-<?php print $formId; ?>"
          data-toggle="collapse"
          data-target="#block-search<?php print $formId; ?>"
          aria-expanded="true"
          aria-controls="block-search<?php print $formId; ?>">
          <?php print t('More'); ?></a>
      </div>
    <?php endif; ?>
  </form>
</div>


