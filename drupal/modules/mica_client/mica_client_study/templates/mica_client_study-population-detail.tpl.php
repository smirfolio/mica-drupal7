<?php
//dpm($population);
?>

  <div>
    <?php if (!empty($population->description)): ?>
      <p class="pull-left">
        <?php print mica_client_commons_get_localized_field($population, 'description'); ?>
      </p>
    <?php endif; ?>

    <div class="pull-right md-bottom-margin">
      <?php
      print l(t('Search Variables'), 'mica/search',
        array(
          'query' => array(
            'type' => 'variables',
            'query' => '{"variables":{"terms":{"dceIds":["' . implode('","', $dce_uids) . '"]}}}'
          ),
          'attributes' => array('class' => 'btn btn-primary')
        ));
      ?>
      <?php
      print l(t('Coverage'), 'mica/coverage',
        array(
          'query' => array(
            'type' => 'variables',
            'query' => '{"variables":{"terms":{"dceIds":["' . implode('","', $dce_uids) . '"]}}}'
          ),
          'attributes' => array('class' => 'btn btn-primary indent')
        ));
      ?>
    </div>
  </div>

  <div class="clearfix"></div>

  <h5><?php print t('Selection criteria') ?></h5>
  <ul>
    <?php if (isset($population->selectionCriteria->gender) && ($population->selectionCriteria->gender === 0 || $population->selectionCriteria->gender === 1)): ?>
      <li>
        <i><?php print t('Gender') ?></i> :
        <?php print  mica_client_study_get_gender($population->selectionCriteria->gender); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->ageMin) || !empty($population->selectionCriteria->ageMax)): ?>
      <li>
        <i><?php print t('Age') ?></i> :
        <?php !empty($population->selectionCriteria->ageMin) ? print t('Minimum') . ' '
          . $population->selectionCriteria->ageMin : NULL; ?>,
        <?php !empty($population->selectionCriteria->ageMax) ? print t('Maximum') . ' '
          . $population->selectionCriteria->ageMax : NULL; ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->countriesIso)): ?>
      <li>
        <i><?php print t('Country'); ?></i> :
        <?php mica_client_commons_iterate_field($population->selectionCriteria->countriesIso,
          'countries_country_lookup', 'iso3', 'name'); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->ethnicOrigin)): ?>
      <li>
        <i><?php print t('Ethnic origin') ?></i> :
        <?php $ehtnic_origins = mica_client_commons_get_localized_dtos_field($population->selectionCriteria, 'ethnicOrigin'); ?>
        <?php mica_client_commons_iterate_field($ehtnic_origins); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->healthStatus)): ?>
      <li>
        <i><?php print t('Health status') ?></i> :
        <?php $health_status = mica_client_commons_get_localized_dtos_field($population->selectionCriteria, 'healthStatus'); ?>
        <?php mica_client_commons_iterate_field($health_status); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->otherCriteria)): ?>
      <li>
        <i><?php print t('Other') ?></i> :
        <?php print mica_client_commons_get_localized_field($population->selectionCriteria, 'otherCriteria'); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->selectionCriteria->info)): ?>
      <li>
        <i><?php print t('Supplementary information') ?></i> :
        <?php print mica_client_commons_get_localized_field($population->selectionCriteria, 'info'); ?>
      </li>
    <?php endif; ?>

  </ul>

  <h5><?php print t('Sources of recruitment') ?></h5>
  <ul>
    <?php if (!empty($population->recruitment->generalPopulationSources)): ?>
      <li>
        <i><?php print t('General population') ?></i> :
        <?php mica_client_commons_iterate_field($population->recruitment->generalPopulationSources); ?>
      </li>
    <?php endif; ?>

    <?php if (!empty($population->recruitment->studies)): ?>
      <li>
        <i><?php print t('Participants from existing studies') ?></i> :
        <?php
        $studies = mica_client_commons_get_localized_dtos_field($population->recruitment, 'studies');
        ?>
        <?php mica_client_commons_iterate_field($studies); ?>
      </li>

      <?php if (!empty($population->recruitment->specificPopulationSources)): ?>
        <li>
          <i><?php print t('Specific population') ?></i> :
          <?php mica_client_commons_iterate_field($population->recruitment->specificPopulationSources); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($population->recruitment->otherSpecificPopulationSource)): ?>
        <li>
          <i><?php print t('Other specific population') ?></i> :
          <?php print mica_client_commons_get_localized_field($population->recruitment, 'otherSpecificPopulationSource'); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($population->recruitment->otherSource)): ?>
        <li>
          <i><?php print t('Supplementary information') ?></i> :
          <?php print mica_client_commons_get_localized_field($population->recruitment, 'otherSource'); ?>
        </li>
      <?php endif; ?>

      <?php if (!empty($population->recruitment->info)): ?>
        <li>
          <?php print t('Supplementary information') ?> :
          <p> <?php print mica_client_commons_get_localized_field($population->recruitment, 'info'); ?></p>
        </li>
      <?php endif; ?>

    <?php endif; ?>

  </ul>

<?php if (!empty($population->numberOfParticipants->participant->number)): ?>
  <h5><?php print t('Number of participants') ?></h5>
  <p>
    <?php print $population->numberOfParticipants->participant->number . ' ' . t('participants') ?>
    <?php if (!empty($population->numberOfParticipants->participant->noLimit)): ?>
      (<?php print t('No limit'); ?>)
    <?php endif; ?>
  </p>
<?php endif; ?>

<?php if (!empty($population->numberOfParticipants->sample->number)): ?>
  <h5><?php print t('Number of participants') ?></h5>
  <p>
    <?php print $population->numberOfParticipants->sample->number . ' ' . t('participants') ?>
    <?php if (!empty($population->numberOfParticipants->sample->noLimit)): ?>
      (<?php print t('No limit'); ?>)
    <?php endif; ?>
  </p>
<?php endif; ?>

<?php if (!empty($population->numberOfParticipants->info)): ?>
  <h5><?php print t('Supplementary information') ?></h5>
  <p><?php print mica_client_commons_get_localized_field($population->numberOfParticipants, 'info'); ?></p>
<?php endif; ?>

<?php if (!empty($population->info)): ?>
  <h5><?php print t('Supplementary information') ?></h5>
  <p> <?php print mica_client_commons_get_localized_field($population, 'info'); ?></p>
<?php endif; ?>

<?php if (!empty($population['dce-tab'])): ?>
  <h5><?php print t('Data Collection Events') ?></h5>
  <?php print $population['dce-tab']; ?>
<?php endif; ?>

<?php if (!empty($population['dce-modal'])): ?>
  <div><?php print $population['dce-modal']; ?></div>
<?php endif; ?>