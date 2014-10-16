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

  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 lg-right-indent">
        <h5><?php print t('Overview') ?></h5>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($population->numberOfParticipants->participant->number)): ?>
            <tr>
              <td><h5><?php print t('Number of participants') ?></h5></td>
              <td>
                <p>
                  <?php print $population->numberOfParticipants->participant->number ?>
                  <?php if (!empty($population->numberOfParticipants->participant->noLimit)): ?>
                    (<?php print t('No limit'); ?>)
                  <?php endif; ?>
                  <?php if (!empty($population->numberOfParticipants->info)): ?>

                <p><?php print mica_client_commons_get_localized_field($population->numberOfParticipants, 'info'); ?></p>
                <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->numberOfParticipants->sample->number)): ?>
            <tr>
              <td><h5><?php print t('Number of samples') ?></h5></td>
              <td>
                <p>
                  <?php print $population->numberOfParticipants->sample->number ?>
                  <?php if (!empty($population->numberOfParticipants->sample->noLimit)): ?>
                    (<?php print t('No limit'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><p> <?php print mica_client_commons_get_localized_field($population, 'info'); ?></p></td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>

        <h5><?php print t('Sources of recruitment') ?></h5>

        <table class="table table-striped">
          <tbody>
          <?php if (!empty($population->recruitment->generalPopulationSources)): ?>
            <tr>
              <td><h5><?php print t('General population') ?></h5></td>
              <td><?php mica_client_commons_iterate_field($population->recruitment->generalPopulationSources); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->recruitment->studies)): ?>
            <tr>
              <td><h5><?php print t('Participants from existing studies') ?></h5></td>
              <td>
                <?php
                $studies = mica_client_commons_get_localized_dtos_field($population->recruitment, 'studies');
                ?>
                <?php mica_client_commons_iterate_field($studies); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->recruitment->specificPopulationSources)): ?>
            <tr>
              <td><h5><?php print t('Specific population') ?></h5></td>
              <td><?php mica_client_commons_iterate_field($population->recruitment->specificPopulationSources); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->recruitment->otherSpecificPopulationSource)): ?>
            <tr>
              <td><h5><?php print t('Other specific population') ?></h5></td>
              <td><?php print mica_client_commons_get_localized_field($population->recruitment, 'otherSpecificPopulationSource'); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->recruitment->otherSource)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><?php print mica_client_commons_get_localized_field($population->recruitment, 'otherSource'); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->recruitment->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><?php print mica_client_commons_get_localized_field($population->recruitment, 'info'); ?></td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>
      </div>

      <div class="col-xs-6">
        <h5><?php print t('Selection criteria') ?></h5>

        <table class="table table-striped">
          <tbody>
          <?php if (isset($population->selectionCriteria->gender) && ($population->selectionCriteria->gender === 0 || $population->selectionCriteria->gender === 1)): ?>
            <tr>
              <td><h5><?php print t('Gender') ?></h5></td>
              <td><?php print  mica_client_study_get_gender($population->selectionCriteria->gender); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->ageMin) || !empty($population->selectionCriteria->ageMax)): ?>
            <tr>
              <td><h5><?php print t('Age') ?></h5></td>
              <td>
                <?php !empty($population->selectionCriteria->ageMin) ? print t('Minimum') . ' '
                  . $population->selectionCriteria->ageMin : NULL; ?>,
                <?php !empty($population->selectionCriteria->ageMax) ? print t('Maximum') . ' '
                  . $population->selectionCriteria->ageMax : NULL; ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->countriesIso)): ?>
            <tr>
              <td><h5><?php print t('Country'); ?></h5></td>
              <td>
                <?php mica_client_commons_iterate_field($population->selectionCriteria->countriesIso,
                  'countries_country_lookup', 'iso3', 'name'); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->ethnicOrigin)): ?>
            <tr>
              <td><h5><?php print t('Ethnic origin') ?></h5></td>
              <td>
                <?php $ehtnic_origins = mica_client_commons_get_localized_dtos_field($population->selectionCriteria, 'ethnicOrigin'); ?>
                <?php mica_client_commons_iterate_field($ehtnic_origins); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->healthStatus)): ?>
            <tr>
              <td><h5><?php print t('Health status') ?></h5></td>
              <td>
                <?php $health_status = mica_client_commons_get_localized_dtos_field($population->selectionCriteria, 'healthStatus'); ?>
                <?php mica_client_commons_iterate_field($health_status); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->otherCriteria)): ?>
            <tr>
              <td><h5><?php print t('Other') ?></h5></td>
              <td><?php print mica_client_commons_get_localized_field($population->selectionCriteria, 'otherCriteria'); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><?php print mica_client_commons_get_localized_field($population->selectionCriteria, 'info'); ?></td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>
      </div>

      <div class="col-xs-6">

      </div>
    </div>
  </div>

<?php if (!empty($population['dce-tab'])): ?>
  <h5><?php print t('Data Collection Events') ?></h5>
  <?php print $population['dce-tab']; ?>
<?php endif; ?>

<?php if (!empty($population['dce-modal'])): ?>
  <div><?php print $population['dce-modal']; ?></div>
<?php endif; ?>