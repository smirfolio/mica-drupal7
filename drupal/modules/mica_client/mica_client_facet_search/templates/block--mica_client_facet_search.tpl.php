<section id="<?php print $block_html_id; ?>" class="boot-collapse <?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>

    <h2<?php print $title_attributes; ?>><a data-toggle="collapse" data-parent="<?php print $block_html_id; ?>"
                                            href="#collapse-<?php print $block_html_id; ?>"><?php print $title; ?>  </a>
    </h2>

  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="block-content panel-collapse" id="collapse-<?php print $block_html_id; ?>">
    <?php print $content ?>
  </div>

</section> <!-- /.block -->