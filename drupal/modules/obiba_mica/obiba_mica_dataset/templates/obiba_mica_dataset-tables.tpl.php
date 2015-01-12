<?php
//dpm($title_section);
//dpm($tab_var);

?>
<?php if (!empty($tab_var)): ?>
  <section>
    <h3><?php print $title_section ?></h3>

    <div>
      <?php print $tab_var; ?>
    </div>
  </section>
<?php endif; ?>






