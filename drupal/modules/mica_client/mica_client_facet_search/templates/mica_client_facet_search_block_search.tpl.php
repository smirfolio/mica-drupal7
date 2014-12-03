<?php //dpm($items['VAR_ONE']);?>
<form id="facet-search_<?php print $formId; ?>">
  <?php $nbr = 0 ?>
  <?php foreach ($items as $term => $term_count): ?>
    <?php if ($nbr < 4): ?>
      <label class="span-checkbox">
        <?php print render($term_count); ?>
      </label>
    <?php endif; ?>
    <?php $nbr++ ?>
  <?php endforeach; ?>

  <div class="expend-see-more expend-control-div<?php print $formId; ?> collapse"
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
    <div class="expend-control" id="<?php print $formId; ?>">
      <a id="<?php print $formId; ?>"
         class="link-expend expend-control-linkblock-search<?php print $formId; ?>"
         data-toggle="collapse"
         data-target="#block-search<?php print $formId; ?>"
         aria-expanded="true"
         aria-controls="block-search<?php print $formId; ?>">
        <?php print t('More'); ?></a>
    </div>
  <?php endif; ?>
</form>

