<?php
/**
 * @file
 * Obiba Mica Module.
 *
 * Copyright (c) 2016 OBiBa. All rights reserved.
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<div>
  <?php if (!empty($network_dto->description)): ?>
    <p class="md-top-margin">
      <?php if (!empty($network_dto->logo->id)): ?>
        <a
          href="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
          class="fancybox-button">
          <img
            src="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
            class="imageThumb img-responsive">
        </a>
      <?php endif; ?>
      <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($network_dto, 'description')); ?>
    </p>
  <?php endif; ?>

  <?php if (!empty($network_dto->studyIds)): ?>
    <div class="btn-group pull-right md-bottom-margin">
      <?php global $user; ?>
      <?php if ($user->uid!==0 &&  variable_get_value('mica_enable_to_mica_server_link')): ?>
        <a title="<?php print t('Edit') ?>" target="_blank" href="<?php print variable_get_value('mica_url').'/#/network/'.$network_dto->id ?>" class="btn btn-primary">
          <i class="glyphicon glyphicon-pencil"></i></a>
      <?php endif; ?>
      <?php if (variable_get_value('networks_list_show_search_button')): ?>
        <?php  print MicaClientAnchorHelper::networkVariables(NULL, $network_dto->id, array('class' => 'btn btn-primary indent')); ?>
      <?php endif; ?>
    </div>
  <?php endif; ?>
</div>

<div class="clearfix"></div>

<article class="bordered-article">

  <section>
    <h2><?php print t('Overview') ?></h2>

    <div class="row">
      <div class="col-lg-6 col-xs-12">

        <table class="table table-striped">
          <tbody>
          <?php if (!empty($network_dto->acronym)): ?>
            <tr>
              <th><?php print t('Acronym') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($network_dto, 'acronym'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->website)): ?>
            <tr>
              <th><?php print t('Website') ?></th>
              <td>
                <p><?php
                  print l(obiba_mica_commons_get_localized_field($network_dto, 'acronym') . ' ' . t('website'),
                    $network_dto->website,
                    array('attributes' => array('target' => '_blank')));
                  ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->investigators)): ?>
            <tr>
              <th><?php print t('Investigators') ?></th>
              <td>
                <ul class="list-unstyled">
                  <?php foreach ($network_dto->investigators as $key_investigator => $investigator) : ?>
                    <li>
                      <a href="#" data-toggle="modal"
                         data-target="#investigator_<?php print $network_dto->id ?>_<?php print $key_investigator ?>">
                        <?php print $investigator->title; ?>
                        <?php print $investigator->firstName; ?>
                        <?php print $investigator->lastName; ?>
                        <?php if (!empty($investigator->academicLevel)) {
                          print ', ' . $investigator->academicLevel;
                        } ?>
                        (<?php print obiba_mica_commons_get_localized_field($investigator->institution, 'name'); ?>
                        )
                      </a>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->contacts)): ?>
            <tr>
              <th><?php print t('Contacts') ?></th>
              <td>
                <ul class="list-unstyled">
                  <?php foreach ($network_dto->contacts as $key_contact => $contact) : ?>
                    <li>
                      <a href="#" data-toggle="modal"
                         data-target="#contact_<?php print $network_dto->id ?>_<?php print $key_contact ?>">
                        <?php print $contact->title; ?>
                        <?php print $contact->firstName; ?>
                        <?php print $contact->lastName; ?>
                        <?php if (!empty($contact->academicLevel)) {
                          print ', ' . $contact->academicLevel;
                        } ?>
                        (<?php print obiba_mica_commons_get_localized_field($contact->institution, 'name'); ?>
                        )
                      </a>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>
        <?php if (!empty($associated_people_button)): ?>
          <?php print render($associated_people_button); ?>
          <?php if (!empty($associated_people_modal)): ?>
            <?php print render($associated_people_modal); ?>
          <?php endif; ?>
        <?php endif; ?>
      </div>

      <?php if (!empty($network_dto->attributes)): ?>
        <div class="col-lg-6 col-xs-12">
          <h4><?php print t('Attributes') ?></h4>

          <p><?php print obiba_mica_dataset_attributes_tab($network_dto->attributes, 'maelstrom'); ?></p>
        </div>
      <?php endif; ?>
    </div>

  </section>
  <?php if (!empty($statistics)): ?>
    <section>
      <h2><?php print t('Summary statistics'); ?></h2>
      <?php print render($statistics); ?>
    </section>
  <?php endif; ?>

  <?php if (!empty($attachments)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print (!empty($file_browser) ? $file_browser : $attachments); ?>
    </section>
  <?php endif; ?>

  <!-- STUDIES and NETWORKS -->
  <?php if (!empty($network_dto->studySummaries) || !empty($network_dto->networkSummaries)): ?>
    <section>

      <?php if (!empty($network_dto->networkSummaries)): ?>
        <div>
          <h2><?php print variable_get_value('networks_section_label') ?></h2>

          <div id="networks-table">
            <div class="row">
              <div class="col-lg-12 col-xs-12">
                <table class="table table-striped" id="table-networks"></table>
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>

      <?php if (!empty($network_dto->studySummaries)): ?>
        <div>
          <h2><?php print t('Studies') ?></h2>

          <div id="studies-table">
            <div class="row">
              <div class="col-lg-12 col-xs-12">
                <table class="table table-striped" id="table-studies"></table>
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>

    </section>
  <?php endif; ?>

  <!-- COVERAGE placeholder -->
  <section id="coverage">
    <h2><?php print t('Variable Classification') ?></h2>
    <p><?php print t('Loading...') ?></p>
  </section>

  <div><?php !empty($investigators_modal) ? print $investigators_modal : ''; ?></div>
  <div><?php !empty($contacts_modal) ? print $contacts_modal : ''; ?></div>

</article>
