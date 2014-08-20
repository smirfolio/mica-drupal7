<?php
//dpm($title_section);
//dpm($tab_var);

?>
<?php if (!empty($tab_var)): ?>
  <?php if (!is_array($tab_var)): ?>
    <h3><?php print $title_section ?></h3>
    <?php print $tab_var; ?>
  <?php elseif (is_array($tab_var) && !empty($tab_var['study-dataset'])): ?>
    <h5><?php print t('Study') ?></h5>
    <p><?php print l($tab_var['study-dataset']->studyId, 'mica/study/' . $tab_var['study-dataset']->studyId . '/' . $tab_var['study-dataset']->studyId); ?></p>
  <?php endif; ?>
<?php endif; ?>






