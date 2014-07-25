<?php
//dpm($title_section);
//dpm($tab_var);

?>
<?php if (!empty($tab_var)): ?>
  <article>
    <header>
    </header>

    <div class="field field-name-body">
      <div class="field-items">
        <?php if (!is_array($tab_var)): ?>
          <div class="field-label">
            <?php print $title_section ?> :
          </div>
          <div class="field-item even" property="content:encoded">


            <?php print $tab_var; ?>

          </div>
        <?php elseif (is_array($tab_var) && !empty($tab_var['study-dataset'])): ?>
          <div>
            <div class="field-label"><?php print t('Study') ?>:</div>
            <div class="field-item even" property="content:encoded">
              <?php print $tab_var['study-dataset']->studyId; ?>
            </div>
          </div>
          <div>
            <div class="field-label"><?php print t('Project') ?>:</div>
            <div class="field-item even" property="content:encoded">
              <?php print $tab_var['study-dataset']->project; ?>
            </div>
          </div>
          <div>
            <div class="field-label"><?php print t('Table') ?>:</div>
            <div class="field-item even" property="content:encoded">
              <?php print $tab_var['study-dataset']->table; ?>
            </div>
          </div>
        <?php endif; ?>


      </div>
    </div>
    <footer>
    </footer>
  </article>
<?php endif; ?>




