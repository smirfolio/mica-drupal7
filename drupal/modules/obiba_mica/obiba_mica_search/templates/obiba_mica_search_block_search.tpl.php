<?php //dpm($items['VAR_ONE']);?>
<?php $style_hide = ''; ?>
<?php if (!empty($input_autocomplete)) : ?>
  <?php print render($input_autocomplete); ?>
  <?php $style_hide = "style='display: none'"; ?>
<?php endif; ?>

<div <?php print $style_hide; ?>>
  <form id="facet-search-<?php print $formId; ?>">
    <?php $nbr = 0 ?>
    <?php foreach ($items as $term => $term_count): ?>
      <?php if ($nbr < 4): ?>
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
        <?php if ($nch >= 4) : ?>
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
          class="label label-info link-expand expand-control-link-<?php print $formId; ?>"
          data-toggle="collapse"
          data-target="#block-search<?php print $formId; ?>"
          aria-expanded="true"
          aria-controls="block-search<?php print $formId; ?>">
          <?php print t('More'); ?></a>
      </div>
    <?php endif; ?>
  </form>
</div>


