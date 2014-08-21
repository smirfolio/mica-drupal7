<?php //dpm($context_detail);?>

<?php if (!empty($context_detail->logo)): ?>
  <img typeof="foaf:Image"
       src="http://localhost:8082/ws/draft/study/<?php print $context_detail->id ?>/file/<?php print $context_detail->logo->id ?>/_download"
       width="120" height="96" alt="">
<?php endif; ?>

  <p>
    <?php print mica_client_commons_get_localized_field($context_detail, 'objectives'); ?>
  </p>

  <!-- GENERAL INFORMATION -->
<?php if (!empty($context_detail->acronym) || !empty($context_detail->website) ||
  !empty($context_detail->investigators) || !empty($context_detail->contacts) ||
  !empty($context_detail->startYear) || !empty($context_detail->endYear) ||
  !empty($context_detail->networks)
): ?>
  <section>
    <h3><?php print t('General Information') ?></h3>

    <div>
      <?php if (!empty($context_detail->acronym)): ?>
        <h5><?php print t('Acronym') ?></h5>
        <p><?php print mica_client_commons_get_localized_field($context_detail, 'acronym'); ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->website)): ?>
        <h5><?php print t('Website') ?></h5>
        <p><?php
          print l($context_detail->website,
            $context_detail->website,
            array('attributes' => array('target' => '_blank')));
          ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->investigators)): ?>
        <h5><?php print t('Investigators') ?></h5>
        <ul>
          <?php foreach ($context_detail->investigators as $investigator) : ?>
            <li>
              <a href="">
                <?php print $investigator->title; ?>
                <?php print $investigator->firstName; ?>
                <?php print $investigator->lastName; ?>
                ( <?php print mica_client_commons_get_localized_field($investigator->institution, 'name'); ?>
                )
              </a>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>

      <?php if (!empty($context_detail->contacts)): ?>
        <h5><?php print t('Contacts') ?></h5>
        <ul>
          <?php foreach ($context_detail->contacts as $contact) : ?>
            <li>
              <a href="">
                <?php print $contact->title; ?>
                <?php print $contact->firstName; ?>
                <?php print $contact->lastName; ?>
                ( <?php print mica_client_commons_get_localized_field($contact->institution, 'name'); ?>
                )
              </a>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>

      <?php if (!empty($context_detail->startYear)): ?>
        <h5><?php print t('Study Start Year') ?></h5>
        <p><?php print $context_detail->startYear; ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->endYear)): ?>
        <h5><?php print t('Study End Year') ?></h5>
        <p><?php print $context_detail->endYear; ?></p>
      <?php endif; ?>

      <!--
        <?php if (!empty($context_detail->networks)): ?>
        <h5><?php print t('Networks') ?> :</h5>
        <p>
          <a href=""><?php //print $context_detail->networks; ?></a>
        </p>
        </div>
        <?php endif; ?>
        -->
    </div>
  </section>
<?php endif; ?>

  <!-- GENERAL DESIGN -->
<?php if (!empty($context_detail->methods->designs) ||
  !empty($context_detail->methods->followUpInfo) ||
  !empty($context_detail->methods->recruitments) ||
  !empty($context_detail->numberOfParticipants->participant->number) ||
  !empty($context_detail->numberOfParticipants->sample->number) ||
  !empty($context_detail->numberOfParticipants->info)
): ?>
  <section>
    <h3><?php print t('General Design') ?></h3>

    <div>
      <?php if (!empty($context_detail->methods->designs)): ?>
        <h5><?php print t('Study Designs') ?></h5>
        <ul>
          <?php foreach ($context_detail->methods->designs as $design): ?>
            <li>
              <?php print t($design); ?>
              <?php if ($design == 'other'): ?>
                : <?php print mica_client_commons_get_localized_field($context_detail->methods, 'otherDesign'); ?>
              <?php endif; ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>

      <?php if (!empty($context_detail->methods->followUpInfo)): ?>
        <h5><?php print t('General Information on Follow Up (profile and frequency)') ?></h5>
        <p><?php print mica_client_commons_get_localized_field($context_detail->methods, 'followUpInfo'); ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->methods->recruitments)): ?>
        <h5><?php print t('Recruitment Target') ?></h5>
        <ul>
          <?php foreach ($context_detail->methods->recruitments as $recruitment): ?>
            <li>
              <?php print t($recruitment) ?>
              <?php if ($recruitment == 'other'): ?>
                : <?php print mica_client_commons_get_localized_field($context_detail->methods, 'otherRecruitment'); ?>
              <?php endif; ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>

      <?php if (!empty($context_detail->numberOfParticipants->participant->number)): ?>
        <h5><?php print t('Target number of participants') ?></h5>
        <p>
          <?php print $context_detail->numberOfParticipants->participant->number; ?>
          <?php if (!empty($context_detail->numberOfParticipants->participant->noLimit)): ?>
            (<?php print t('No limit'); ?>)
          <?php endif; ?>
        </p>
      <?php endif; ?>

      <?php if (!empty($context_detail->numberOfParticipants->sample->number)): ?>
        <h5><?php print t('Target number of participants with biological samples') ?></h5>
        <p>
          <?php print $context_detail->numberOfParticipants->sample->number; ?>
          <?php if (!empty($context_detail->numberOfParticipants->sample->noLimit)): ?>
            (<?php print t('No limit'); ?>)
          <?php endif; ?>
        </p>
      <?php endif; ?>

      <?php if (!empty($context_detail->numberOfParticipants->info)): ?>
        <h5><?php print t('Supplementary information about target number of participants') ?></h5>
        <p><?php print mica_client_commons_get_localized_field($context_detail->numberOfParticipants, 'info'); ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->methods->info)): ?>
        <h5><?php print t('Supplementary information') ?></h5>
        <p><?php print mica_client_commons_get_localized_field($context_detail->methods, 'info'); ?></p>
      <?php endif; ?>

    </div>
  </section>
<?php endif; ?>

  <!-- ACCESS -->
<?php if (in_array('data', $context_detail->access) ||
  in_array('bio_samples', $context_detail->access) ||
  in_array('other', $context_detail->access)
): ?>
  <section>
    <h3><?php print t('Access') ?></h3>

    <div>
      <p><?php print t('Access to external researchers or third parties provided or foreseen for:'); ?></p>

      <h5><?php print t('Data (questionnaire-derived, measured...)'); ?></h5>

      <p>
        <?php if (in_array('data', $context_detail->access)): ?>
          <?php print t('Yes'); ?>
        <?php else : ?>
          <?php print t('No'); ?>
        <?php endif; ?>
      </p>

      <h5><?php print t('Biological samples'); ?></h5>

      <p>
        <?php if (in_array('bio_samples', $context_detail->access)): ?>
          <?php print t('Yes'); ?>
        <?php else : ?>
          <?php print t('No'); ?>
        <?php endif; ?>
      </p>

      <?php if (in_array('other', $context_detail->access)): ?>
        <h5><?php print t('Other'); ?></h5>
        <p>
          <?php if (in_array('other', $context_detail->access)): ?>
            <?php print t('Yes'); ?> --
          <?php endif; ?>
          <?php if (!empty($context_detail->otherAccess)): ?>
            <?php print mica_client_commons_get_localized_field($context_detail, 'otherAccess'); ?>
          <?php endif; ?>
        </p>
      <?php endif; ?>
    </div>
  </section>
<?php endif; ?>

  <!-- MARKER PAPER -->
<?php if (!empty($context_detail->markerPaper) || !empty($context_detail->pubmedId)): ?>
  <section>
    <h3><?php print t('Marker Paper') ?></h3>

    <div>
      <?php if (!empty($context_detail->markerPaper)): ?>
        <h5><?php print t('Marker paper'); ?></h5>
        <p><?php print $context_detail->markerPaper; ?></p>
      <?php endif; ?>

      <?php if (!empty($context_detail->pubmedId)): ?>
        <h5><?php print t('Pubmed ID'); ?></h5>
        <p>
          <a href="http://www.ncbi.nlm.nih.gov/pubmed/<?php print $context_detail->pubmedId; ?>">
            PUBMED <?php print $context_detail->pubmedId; ?>
          </a>
        </p>
      <?php endif; ?>
    </div>
  </section>
<?php endif; ?>

  <!-- SUPPLEMENTARY INFORMATION -->
<?php if (!empty($context_detail->info) || !empty($context_detail->attachments)): ?>
  <section>
    <h3><?php print t('Supplementary Information'); ?></h3>

    <div>
      <?php if (!empty($context_detail->info)): ?>
        <p>
          <?php print mica_client_commons_get_localized_field($context_detail, 'info'); ?>
        </p>
      <?php endif; ?>

      <?php if (!empty($context_detail->attachments)): ?>
        <?php print mica_client_study_get_attachment_file($context_detail->id, $context_detail->attachments); ?>
      <?php endif; ?>
    </div>
  </section>
<?php endif; ?>