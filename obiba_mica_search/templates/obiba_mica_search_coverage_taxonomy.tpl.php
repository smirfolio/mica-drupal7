<?php if (!empty($taxonomy_coverage->hits) && !empty($taxonomy_coverage->vocabularies)): ?>
  <section>
    <div>
      <h2 id="<?php print $taxonomy_coverage->taxonomy->name; ?>">
        <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage->taxonomy, 'titles'); ?>
      </h2>

      <p class="help-block">
        <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage->taxonomy, 'descriptions'); ?>
      </p>
    </div>

    <?php foreach ($taxonomy_coverage->vocabularies as $vocabulary_coverage) : ?>
      <?php print render($vocabulary_coverage_output[$vocabulary_coverage->vocabulary->name]); ?>
    <?php endforeach; ?>
  </section>
<?php endif ?>
