<?php
//dpm('title =>'.$title);
//dpm('block_html_id =>'.$block_html_id);
?>
<section id="block-obiba-mica-search-facet-search<?php print $block_html_id; ?>"
  class="boot-collapse block-obiba-mica-search">

  <?php if ($title): ?>

    <h2 class="block-titles">
      <a data-toggle="collapse"
        data-parent="<?php print $block_html_id; ?>"
        href="#collapse-<?php print $block_html_id; ?>"
        class="collapsed">
        <?php print $title; ?>
      </a>
    </h2>
    <div class="checkedterms clearfix"></div>
  <?php endif; ?>

  <div class="block-content panel-collapse collapse" id="collapse-<?php print $block_html_id; ?>">
    <?php print render($content) ?>
  </div>

</section> <!-- /.block -->