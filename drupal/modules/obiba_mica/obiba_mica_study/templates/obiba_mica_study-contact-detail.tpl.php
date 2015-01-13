<?php
//dpm($contact);
?>
<div id="<?php print $contact_uid ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4
          class="modal-title"><?php print $contact->title; ?> <?php print $contact->firstName; ?>  <?php print $contact->lastName; ?> </h4>
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
                !empty($contact->institution->department) ||
                !empty($contact->institution->address)
              ): ?>
                <tr>
                  <td><h5><?php print t('Institution') ?></h5></td>
                  <td>
                    <div>
                      <?php !empty($contact->institution->name) ? //
                        print t('Name') . ' : ' . obiba_mica_commons_get_localized_field($contact->institution, 'name') : ''; ?>
                    </div>
                    <div>
                      <?php !empty($contact->institution->department) ?
                        print t('Department') . ' : ' . obiba_mica_commons_get_localized_field($contact->institution, 'department') : ''; ?></li>
                    </div>

                  </td>
                </tr>
                <?php
                if (!empty($contact->institution->address->street) ||
                  !empty($contact->institution->address->city) ||
                  !empty($contact->institution->address->state) ||
                  !empty($contact->institution->address->country)
                ): ?>
                  <tr>
                    <td><h5><?php print t('Adresse') ?></h5></td>
                    <td>
                      <div>   <?php !empty($contact->institution->address->street) ? print t('Street') . ' : ' .
                          obiba_mica_commons_get_localized_field($contact->institution->address, 'street') : ''; ?> </div>
                      <div>  <?php !empty($contact->institution->address->city) ?
                          print t('City') . ' : ' . obiba_mica_commons_get_localized_field($contact->institution->address, 'city') : ''; ?></div>
                      <div>  <?php !empty($contact->institution->address->zip) ?
                          print t('Zip code') . ' : ' . $contact->institution->address->zip : ''; ?></div>
                      <div>   <?php !empty($contact->institution->address->state) ?
                          print t('State') . ' : ' . $contact->institution->address->state : ''; ?></div>
                      <div>  <?php !empty($contact->institution->address->country) ?
                          print t('Country') . ' : ' . $contact->institution->address->country->iso : ''; ?></div>

                    </td>
                  </tr>
                <?php endif; ?>
              <?php endif; ?>

              </tbody>
            </table>

        </section>
      </div>
    </div>
  </div>
</div>
