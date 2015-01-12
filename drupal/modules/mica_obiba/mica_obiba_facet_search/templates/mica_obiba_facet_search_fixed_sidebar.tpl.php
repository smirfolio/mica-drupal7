<?php if (!empty($coverages->taxonomies)): ?>
  <nav id="scroll-menu" data-spy="affix">
    <ul class="nav">
      <?php foreach ($coverages->taxonomies as $taxonomy_coverage) : ?>
        <?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>
          <li>
            <a href="#<?php print $taxonomy_coverage->taxonomy->name; ?>">
              <?php print mica_obiba_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
            </a>
            <ul class="nav" style="display: block;">
              <?php foreach ($taxonomy_coverage->vocabularies as $index => $vocabulary_coverage) : ?>
                <?php if (!empty($vocabulary_coverage->hits)): ?>
                  <li class="<?php $index === 0 ? 'active' : '' ?>">
                    <a
                      href="#<?php print $taxonomy_coverage->taxonomy->name . '-' . $vocabulary_coverage->vocabulary->name; ?>">
                      <?php print mica_obiba_commons_get_localized_field($vocabulary_coverage->vocabulary, 'titles'); ?>
                    </a>
                  </li>
                <?php endif ?>
              <?php endforeach; ?>
            </ul>
          </li>
        <?php endif ?>
      <?php endforeach; ?>
    </ul>
  </nav>

<?php endif ?>