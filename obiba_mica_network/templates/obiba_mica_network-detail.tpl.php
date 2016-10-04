<?php
/**
 * Copyright (c) 2016 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>

<div>
  <?php if (!empty($network_dto->description)): ?>
    <div class="row md-bottom-margin">
      <?php if (!empty($network_dto->logo->id)): ?>
        <div class="col-xs-12 col-md-6">
          <a
              href="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
              class="fancybox-button">
            <img
                src="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
                class="imageThumb img-responsive">
          </a>
        </div>
      <?php endif; ?>
      <div class="md-top-margin col-xs-12">
        <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($network_dto, 'description')); ?>
      </div>
    </div>
  <?php endif; ?>

  <div class="pull-right md-bottom-margin">
  <?php if (canEditDraftDocument($network_dto)): ?>
    <a title="<?php print t('Edit') ?>"
       target="_blank"
       href="<?php print MicaClientPathProvider::network_draft_url($network_dto->id) ?>"
       class="btn btn-default">
      <i class="fa fa-pencil-square-o"></i> <?php print t('Edit')?></a>
  <?php endif; ?>
  <?php if (!empty($network_dto->studyIds)): ?>
      <?php if (variable_get_value('network_detail_show_search_button')): ?>
        <?php  print MicaClientAnchorHelper::networkVariables(NULL, $network_dto->id, array('class' => 'btn btn-primary')); ?>
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

          <?php if (!empty($network_dto->model->website)): ?>
            <tr>
              <th><?php print t('Website') ?></th>
              <td>
                <p><?php
                  print l(obiba_mica_commons_get_localized_field($network_dto, 'acronym') . ' ' . t('website'),
                    $network_dto->model->website,
                    array('attributes' => array('target' => '_blank')));
                  ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->memberships)): ?>
            <?php foreach ($network_dto->memberships as $membership): ?>
              <tr>
                <th><?php print ucfirst(t($membership->role)) ?></th>
                <td>
                  <ul class="list-unstyled">
                    <?php if (!empty($membership->members)) : ?>
                      <?php foreach ($membership->members as  $key_member => $member) : ?>
                        <li>
                          <a href="#" data-toggle="modal"
                             data-target="#<?php print obiba_mica_person_generate_target_id($membership->role, $network_dto->id, $key_member); ?>">
                            <?php print !empty($member->title)?$member->title:''; ?>
                            <?php print !empty($member->firstName)?$member->firstName:''; ?>
                            <?php print !empty($member->lastName)?$member->lastName:''; ?>
                            <?php if (!empty($member->academicLevel)) {
                              print ', ' . $member->academicLevel;
                            } ?>
                            (<?php print obiba_mica_commons_get_localized_field($member->institution, 'name'); ?>
                            )
                          </a>
                        </li>
                      <?php endforeach; ?>
                    <?php endif; ?>
                  </ul>
                </td>
              </tr>
            <?php endforeach; ?>
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
      <h2><?php print t('Summary Statistics'); ?></h2>
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
    <h2><?php print t('Variables Classification') ?></h2>
    <p><?php print t('Loading...') ?></p>
  </section>

  <!-- DATASETS placeholder -->
  <section id="datasets">
    <div><?php print t('Loading ...') ?></div>
  </section>

  <div><?php !empty($investigators_modal) ? print $investigators_modal : ''; ?></div>
  <div><?php !empty($contacts_modal) ? print $contacts_modal : ''; ?></div>

</article>
