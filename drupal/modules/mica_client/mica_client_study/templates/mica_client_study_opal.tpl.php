<?php if (!empty($opal_url)): ?>
  <section>
    <h2 class="block-title"><?php print t('Opal') ?></h2>
    <article>
      <div>
        <div class="field field-name-field-documents field-type-file">
          <div class="field-items">

            <div class="field-item even">
          <span class="file">
            <a
              href="<?php print $opal_url ?>"><?php print $opal_url ?></a>
          </span>
            </div>


          </div>
        </div>
      </div>
    </article>
  </section>
<?php endif; ?>