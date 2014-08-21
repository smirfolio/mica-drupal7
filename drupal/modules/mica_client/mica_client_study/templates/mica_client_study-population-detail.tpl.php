<?php //dpm($context_population_detail); ?>

  <p>
    <?php print mica_client_commons_get_localized_field($context_population_detail, 'description'); ?>
  </p>

  <h5><?php print t('Selection criteria') ?></h5>
  <ul>
    <?php if (isset($context_population_detail->selectionCriteria->gender) && ($context_population_detail->selectionCriteria->gender === 0 || $context_population_detail->selectionCriteria->gender === 1)): ?>
      <li>
        <i><?php print t('Gender') ?></i> :
        <?php print  mica_client_study_get_gender($context_population_detail->selectionCriteria->gender); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->ageMin) || !empty($context_population_detail->selectionCriteria->ageMax)): ?>
      <li>
        <i><?php print t('Age') ?></i> :
        <?php !empty($context_population_detail->selectionCriteria->ageMin) ? print t('Minimum') . ' '
          . $context_population_detail->selectionCriteria->ageMin : NULL; ?>,
        <?php !empty($context_population_detail->selectionCriteria->ageMax) ? print t('Maximum') . ' '
          . $context_population_detail->selectionCriteria->ageMax : NULL; ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->countriesIso)): ?>
      <li>
        <i><?php print t('Country'); ?></i> :
        <?php mica_client_commons_iterate_field($context_population_detail->selectionCriteria->countriesIso,
          'countries_country_lookup', 'iso3', 'name'); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->ethnicOrigin)): ?>
      <li>
        <i><?php print t('Ethnic origin') ?></i> :
        <?php $ehtnic_origins = mica_client_commons_get_localized_dtos_field($context_population_detail->selectionCriteria, 'ethnicOrigin'); ?>
        <?php mica_client_commons_iterate_field($ehtnic_origins); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->healthStatus)): ?>
      <li>
        <i><?php print t('Health status') ?></i> :
        <?php $health_status = mica_client_commons_get_localized_dtos_field($context_population_detail->selectionCriteria, 'healthStatus'); ?>
        <?php mica_client_commons_iterate_field($health_status); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->otherCriteria)): ?>
      <li>
        <i><?php print t('Other') ?></i> :
        <?php print mica_client_commons_get_localized_field($context_population_detail->selectionCriteria, 'otherCriteria'); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->selectionCriteria->info)): ?>
      <li>
        <i><?php print t('Supplementary information') ?></i> :
        <?php print mica_client_commons_get_localized_field($context_population_detail->selectionCriteria, 'info'); ?>
      </li>
    <?php endif; ?>

  </ul>

  <h5><?php print t('Sources of recruitment') ?></h5>
  <ul>
    <?php if (!empty($context_population_detail->recruitment->generalPopulationSources)): ?>
      <li>
        <i><?php print t('General population') ?></i> :
        <?php mica_client_commons_iterate_field($context_population_detail->recruitment->generalPopulationSources); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($context_population_detail->recruitment->studies)): ?>
      <li>
        <i><?php print t('Participants from existing studies') ?></i> :
        <?php
        $studies = mica_client_commons_get_localized_dtos_field($context_population_detail->recruitment, 'studies');
        ?>
        <?php mica_client_commons_iterate_field($studies); ?>
      </li>

      <?php if (!empty($context_population_detail->recruitment->specificPopulationSources)): ?>
        <li>
          <i><?php print t('Specific population') ?></i> :
          <?php mica_client_commons_iterate_field($context_population_detail->recruitment->specificPopulationSources); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($context_population_detail->recruitment->otherSpecificPopulationSource)): ?>
        <li>
          <i><?php print t('Other specific population') ?></i> :
          <?php print mica_client_commons_get_localized_field($context_population_detail->recruitment, 'otherSpecificPopulationSource'); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($context_population_detail->recruitment->otherSource)): ?>
        <li>
          <i><?php print t('Supplementary information') ?></i> :
          <?php print mica_client_commons_get_localized_field($context_population_detail->recruitment, 'otherSource'); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($context_population_detail->recruitment->info)): ?>
        <li>
          <?php print t('Supplementary information') ?> :
          <p> <?php print mica_client_commons_get_localized_field($context_population_detail->recruitment, 'info'); ?></p>
        </li>
      <?php endif; ?>

    <?php endif; ?>

  </ul>

<?php if (!empty($context_population_detail->numberOfParticipants->participant->number)): ?>
  <h5><?php print t('Number of participants') ?></h5>
  <p>
    <?php print $context_population_detail->numberOfParticipants->participant->number . ' ' . t('participants') ?>
    <?php if (!empty($context_population_detail->numberOfParticipants->participant->noLimit)): ?>
      (<?php print t('No limit'); ?>)
    <?php endif; ?>
  </p>
<?php endif; ?>

<?php if (!empty($context_population_detail->numberOfParticipants->sample->number)): ?>
  <h5><?php print t('Number of participants') ?></h5>
  <p>
    <?php print $context_population_detail->numberOfParticipants->sample->number . ' ' . t('participants') ?>
    <?php if (!empty($context_population_detail->numberOfParticipants->sample->noLimit)): ?>
      (<?php print t('No limit'); ?>)
    <?php endif; ?>
  </p>
<?php endif; ?>

<?php if (!empty($context_population_detail->numberOfParticipants->info)): ?>
  <h5><?php print t('Supplementary information') ?></h5>
  <p><?php print mica_client_commons_get_localized_field($context_population_detail->numberOfParticipants, 'info'); ?></p>
<?php endif; ?>

<?php if (!empty($context_population_detail->info)): ?>
  <h5><?php print t('Supplementary information') ?></h5>
  <p> <?php print mica_client_commons_get_localized_field($context_population_detail, 'info'); ?></p>
<?php endif; ?>

<?php if (!empty($context_population_detail['dce-tab'])): ?>
  <h5><?php print t('Data Collection Events') ?></h5>
  <?php print $context_population_detail['dce-tab']; ?>
<?php endif; ?>

<?php if (!empty($context_population_detail['dce-modal'])): ?>
  <div><?php print $context_population_detail['dce-modal']; ?></div>
<?php endif; ?>