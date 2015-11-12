<nav id="scroll-menu" data-spy="affix">
  <ul class="nav">
    <li>
      <a href="#overview">
        <?php print t('Study Detail'); ?>
      </a>
      <ul class="nav" style="display: block;">
        <li>
          <a href="#overview">
            <?php print t('Overview / Design'); ?>
          </a>
        </li>
        <li>
          <a href="#access">
            <?php if ($marker_paper && $pubmed_id): ?>
              <?php print t('Access / Marker Paper'); ?>
            <?php elseif ($marker_paper): ?>
              <?php print t('Marker Paper'); ?>
            <?php else: ?>
              <?php print t('Access'); ?>
            <?php endif; ?>
          </a>
        </li>
        <?php if ($info): ?>
          <li>
            <a href="#info"><?php print t('Supplementary Information'); ?>
            </a>
          </li>
        <?php endif; ?>
        <?php if ($attachments): ?>
          <li>
            <a href="#documents">
              <?php print variable_get('files_documents_label'); ?>
            </a>
          </li>
        <?php endif; ?>
        <li>
          <a href="#timeline">
            <?php print t('Timeline'); ?>
          </a>
        </li>
        <li>
          <a href="#populations">
            <?php print t('Populations'); ?>
          </a>
        </li>
        <?php if (!empty($networks)): ?>
          <li>
            <a href="#networks">
              <?php print t('Networks'); ?>
            </a>
          </li>
        <?php endif; ?>
        <?php if (!empty($datasets)): ?>
          <li>
            <a href="#datasets">
              <?php print t('Datasets'); ?>
            </a>
          </li>
        <?php endif; ?>
        <?php if (!empty($datasets) && !empty($study_variables_aggs)): ?>
          <li>
            <a href="#variables">
              <?php print t('Variables'); ?>
            </a>
          </li>
        <?php endif; ?>
        <?php if (!empty($coverage)): ?>
          <li>
            <a href="#coverage">
              <?php print t('Variable Classification'); ?>
            </a>
          </li>
        <?php endif; ?>
      </ul>
    </li>

</nav>
