<?php
//dpm($contact);
?>
<div id="<?php print $contact_uid ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4
          class="modal-title"><?php print $contact->title; ?> <?php print $contact->firstName; ?>  <?php print $contact->lastName; ?>
          <?php if (!empty($contact->academicLevel)) {
            print ', ' . $contact->academicLevel;
          } ?></h4>
      </div>
      <div class="modal-body">

        <section>
          <div>
            <table class="table table-striped">
              <tbody>
              <?php if (!empty($contact->email)): ?>
                <tr>
                  <td><h5><?php print t('Email') ?></h5></td>
                  <td><p><?php print $contact->email; ?></p></td>
                </tr>
              <?php endif; ?>

              <?php if (!empty($contact->phone)): ?>
                <tr>
                  <td><h5><?php print t('Phone') ?></h5></td>
                  <td><p><?php print $contact->phone; ?></p></td>
                </tr>
              <?php endif; ?>

              <?php if (!empty($contact->dataAccessCommitteeMember)): ?>
                <tr>
                  <td><h5><?php print t('Data Access Committee member') ?></h5></td>
                  <td>
                    <?php print !empty($contact->dataAccessCommitteeMember) ? 'YES' : 'NO'; ?>
                  </td>
                </tr>
              <?php endif; ?>

              <?php if (!empty($contact->institution->name) ||
                !empty($contact->institution->department)
              ): ?>
                <tr>
                  <td><h5><?php print t('Institution') ?></h5></td>
                  <td>
                    <?php if (!empty($contact->institution->name)): ?>
                      <p>
                        <?php print obiba_mica_commons_get_localized_field($contact->institution, 'name'); ?>
                      </p>
                    <?php endif; ?>
                    <?php if (!empty($contact->institution->department)): ?>
                      <p>
                        <?php print obiba_mica_commons_get_localized_field($contact->institution, 'department'); ?>
                      </p>
                    <?php endif; ?>
                  </td>
                </tr>
              <?php endif; ?>
              <?php
              if (!empty($contact->institution->address->street) ||
                !empty($contact->institution->address->city) ||
                !empty($contact->institution->address->zip) ||
                !empty($contact->institution->address->state) ||
                !empty($contact->institution->address->country)
              ): ?>
                <tr>
                  <td><h5><?php print t('Address') ?></h5></td>
                  <td>
                    <?php if (!empty($contact->institution->address->street)): ?>
                      <p>
                        <?php print obiba_mica_commons_get_localized_field($contact->institution->address, 'street'); ?>
                      </p>
                    <?php endif; ?>
                    <?php if (!empty($contact->institution->address->city)): ?>
                      <p>
                        <?php print obiba_mica_commons_get_localized_field($contact->institution->address, 'city'); ?>
                      </p>
                    <?php endif; ?>
                    <?php if (!empty($contact->institution->address->zip)): ?>
                      <p>
                        <?php print $contact->institution->address->zip; ?>
                      </p>
                    <?php endif; ?>
                    <?php if (!empty($contact->institution->address->country)): ?>
                      <p>
                        <?php if (!empty($contact->institution->address->state)): ?>
                          <?php print $contact->institution->address->state . ', '; ?>
                        <?php endif; ?>
                        <?php print $contact->institution->address->country->iso; ?>
                      </p>
                    <?php endif; ?>
                  </td>
                </tr>
              <?php endif; ?>

              </tbody>
            </table>

        </section>
      </div>
    </div>
  </div>
</div>
