<?php
//dpm($dataset_dto);
//dpm($datset_type);
?>
<?php if (!empty($dataset_dto->description)) : ?>
  <article>
    <header>
    </header>

    <div class="field field-name-body">
      <div class="field-items">
        <div class="field-label">
          <?php print t('Description') ?> :
        </div>
        <div class="field-item even" property="content:encoded">
          <p>
            <?php print mica_client_commons_get_localized_field($dataset_dto, 'description'); ?>
          </p>
        </div>
      </div>
    </div>
    <footer>
    </footer>
  </article>
<?php endif; ?>