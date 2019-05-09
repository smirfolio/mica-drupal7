<div id="representative" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h3 class="modal-title">
          <?php print !empty($person->title)?filter_xss($person->title, obiba_mica_commons_allowed_filter_xss_tags()):''; ?>
          <?php print !empty($person->name)?filter_xss($person->name, obiba_mica_commons_allowed_filter_xss_tags()):''; ?>
        </h3>
      </div>
      <div class="modal-body" test-ref="modal-body">

        <section>
          <div>
            <table class="table table-striped">
              <tbody>
              <?php if (!empty($person->institution)): ?>
                <tr>
                  <th><?php print $localize->getTranslation('contact.institution') ?></th>
                  <td test-ref="institutionIdentifier">
                    <p>
                      <?php print $person->institution; ?>
                    </p>
                  </td>
                </tr>
              <?php endif; ?>
              <?php if (!empty($person->email)): ?>
                <tr>
                  <th><?php print $localize->getTranslation('contact.email') ?></th>
                  <td test-ref="email"><p><?php print $person->email; ?></p></td>
                </tr>
              <?php endif; ?>

              <?php if (!empty($person->telephone)): ?>
                <tr>
                  <th><?php print $localize->getTranslation('contact.phone') ?></th>
                  <td test-ref="phone"><p><?php print $person->telephone; ?></p></td>
                </tr>
              <?php endif; ?>
              </tbody>
            </table>

        </section>
      </div>
    </div>
  </div>
</div>