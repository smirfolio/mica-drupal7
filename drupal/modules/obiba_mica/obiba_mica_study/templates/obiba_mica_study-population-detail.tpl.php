<?php
//dpm($population);
?>

  <div>
    <h4 class="pull-left no-top-margin">
      <?php print  obiba_mica_commons_get_localized_field($population, 'name') ?>
    </h4>

    <?php if (!empty($dce_uids)): ?>
      <div class="pull-right md-bottom-margin">
        <?php
        $query_array = array("variables" => array("terms" => array("dceIds" => $dce_uids)));
        $query = MicaClient::create_query_dto_as_string($query_array);

        print l(t('Search Variables'), 'mica/search',
          array(
            'query' => array(
              'type' => 'variables',
              'query' => $query
            ),
            'attributes' => array('class' => 'btn btn-primary')
          ));
        ?>
        <?php
        print l(t('Coverage'), 'mica/coverage',
          array(
            'query' => array(
              'type' => 'variables',
              'query' => $query
            ),
            'attributes' => array('class' => 'btn btn-primary indent')
          ));
        ?>
      </div>
    <?php endif ?>

  </div>

  <div class="clearfix"></div>

<?php if (!empty($population->description)): ?>
  <p>
    <?php print obiba_mica_commons_get_localized_field($population, 'description'); ?>
  </p>
<?php endif; ?>

  <div class="row ">

    <?php if (!empty($population->numberOfParticipants->participant->number)
      || !empty($population->numberOfParticipants->sample->number)
      || !empty($population->info)
    ): ?>
      <div class="col-lg-6 col-xs-12 ">
        <h5><?php print t('Overview') ?></h5>

        <div class="scroll-content-tab">
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

                  <p><?php print obiba_mica_commons_get_localized_field($population->numberOfParticipants, 'info'); ?></p>
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
                <td><p> <?php print obiba_mica_commons_get_localized_field($population, 'info'); ?></p></td>
              </tr>
            <?php endif; ?>

            </tbody>
          </table>
        </div>

      </div>
    <?php endif; ?>

    <?php if (!empty($population->recruitment->generalPopulationSources)
      || !empty($population->recruitment->studies)
      || !empty($population->recruitment->specificPopulationSources)
      || !empty($population->recruitment->otherSpecificPopulationSource)
      || !empty($population->recruitment->otherSource)
      || !empty($population->recruitment->info)
    ): ?>
      <div class="col-lg-6 col-xs-12 ">
        <h5><?php print t('Sources of recruitment') ?></h5>

        <div class="scroll-content-tab">
          <table class="table table-striped">
            <tbody>
            <?php if (!empty($population->recruitment->generalPopulationSources)): ?>
              <tr>
                <td><h5><?php print t('General population') ?></h5></td>
                <td><?php obiba_mica_commons_iterate_field($population->recruitment->generalPopulationSources); ?></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($population->recruitment->studies)): ?>
              <tr>
                <td><h5><?php print t('Participants from existing studies') ?></h5></td>
                <td>
                  <?php
                  $studies = obiba_mica_commons_get_localized_dtos_field($population->recruitment, 'studies');
                  ?>
                  <?php obiba_mica_commons_iterate_field($studies); ?>
                </td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($population->recruitment->specificPopulationSources)): ?>
              <tr>
                <td><h5><?php print t('Specific population') ?></h5></td>
                <td><?php obiba_mica_commons_iterate_field($population->recruitment->specificPopulationSources); ?></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($population->recruitment->otherSpecificPopulationSource)): ?>
              <tr>
                <td><h5><?php print t('Other specific population') ?></h5></td>
                <td><?php print obiba_mica_commons_get_localized_field($population->recruitment, 'otherSpecificPopulationSource'); ?></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($population->recruitment->otherSource)): ?>
              <tr>
                <td><h5><?php print t('Supplementary information') ?></h5></td>
                <td><?php print obiba_mica_commons_get_localized_field($population->recruitment, 'otherSource'); ?></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($population->recruitment->info)): ?>
              <tr>
                <td><h5><?php print t('Supplementary information') ?></h5></td>
                <td><?php print obiba_mica_commons_get_localized_field($population->recruitment, 'info'); ?></td>
              </tr>
            <?php endif; ?>
            </tbody>
          </table>
        </div>
      </div>
    <?php endif; ?>
  </div>

<?php if ((isset($population->selectionCriteria->gender) && ($population->selectionCriteria->gender === 0 || $population->selectionCriteria->gender === 1))
  || !empty($population->selectionCriteria->ageMin) || !empty($population->selectionCriteria->ageMax)
  || !empty($population->selectionCriteria->countriesIso)
  || !empty($population->selectionCriteria->ethnicOrigin)
  || !empty($population->selectionCriteria->healthStatus)
  || !empty($population->selectionCriteria->otherCriteria)
  || !empty($population->selectionCriteria->info)
): ?>
  <h5><?php print t('Selection criteria') ?></h5>
  <div class="row ">
    <div class="col-lg-12 col-xs-12">
      <div class="scroll-content-tab">
        <table class="table table-striped">
          <tbody>
          <?php if (isset($population->selectionCriteria->gender) && ($population->selectionCriteria->gender === 0 || $population->selectionCriteria->gender === 1)): ?>
            <tr>
              <td><h5><?php print t('Gender') ?></h5></td>
              <td><?php print  obiba_mica_study_get_gender($population->selectionCriteria->gender); ?></td>
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
                <?php obiba_mica_commons_iterate_field($population->selectionCriteria->countriesIso,
                  'countries_country_lookup', 'iso3', 'name'); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->ethnicOrigin)): ?>
            <tr>
              <td><h5><?php print t('Ethnic origin') ?></h5></td>
              <td>
                <?php $ehtnic_origins = obiba_mica_commons_get_localized_dtos_field($population->selectionCriteria, 'ethnicOrigin'); ?>
                <?php obiba_mica_commons_iterate_field($ehtnic_origins); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->healthStatus)): ?>
            <tr>
              <td><h5><?php print t('Health status') ?></h5></td>
              <td>
                <?php $health_status = obiba_mica_commons_get_localized_dtos_field($population->selectionCriteria, 'healthStatus'); ?>
                <?php obiba_mica_commons_iterate_field($health_status); ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->otherCriteria)): ?>
            <tr>
              <td><h5><?php print t('Other') ?></h5></td>
              <td><?php print obiba_mica_commons_get_localized_field($population->selectionCriteria, 'otherCriteria'); ?></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($population->selectionCriteria->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><?php print obiba_mica_commons_get_localized_field($population->selectionCriteria, 'info'); ?></td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if (!empty($population['dce-tab'])): ?>
  <h5><?php print t('Data Collection Events') ?></h5>
  <div class="scroll-content-tab">
    <?php print $population['dce-tab']; ?>
  </div>
<?php endif; ?>

<?php if (!empty($population['dce-modal'])): ?>
  <div><?php print $population['dce-modal']; ?></div>
<?php endif; ?>