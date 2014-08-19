<section id="<?php print $block_html_id; ?>" class="bootCollaplse <?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <a data-toggle="collapse" data-parent="<?php print $block_html_id; ?>"
       href="#collapse-<?php print $block_html_id; ?>">
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    </a>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="block-content panel-collapse collapse in" id="collapse-<?php print $block_html_id; ?>">
    <?php print $content ?>
  </div>

</section> <!-- /.block -->
