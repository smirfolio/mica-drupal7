<?php
//dpm($dce);
?>

<div id="dce-<?php print $dce_id_target ?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
<div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title"><?php print mica_client_commons_get_localized_field($dce, 'name'); ?></h4>
      </div>
      <div class="modal-body">

        <section>
          <div>
            <?php if (!empty($dce->description)): ?>
              <p>
                <?php print mica_client_commons_get_localized_field($dce, 'description'); ?>
              </p>
            <?php endif; ?>

            <div class="pull-right md-bottom-margin">
              <?php
              $query_array = array("variables" => array("terms" => array("dceIds" => $dce_uid)));
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
          </div>

          <div class="clearfix"></div>

          <table class="table table-striped">
            <tbody>
            <?php if (!empty($dce->startYear)): ?>
              <tr>
                <td><h5><?php print t('Start Year') ?></h5></td>
                <td><p><?php print mica_client_commons_format_year($dce->startYear, $dce->startMonth); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->endYear)): ?>
              <tr>
                <td><h5><?php print t('End Year') ?></h5></td>
                <td><p><?php print mica_client_commons_format_year($dce->endYear, $dce->endMonth); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->dataSources)): ?>
              <tr>
                <td><h5><?php print t('Data Sources') ?></h5></td>
                <td>
                  <ul>
                    <?php foreach ($dce->dataSources as $dataSource): ?>
                      <li>
                        <?php print t($dataSource); ?>
                      </li>
                    <?php endforeach; ?>
                    <?php if (!empty($dce->otherDataSources)): ?>
                      <li>
                        <?php print mica_client_commons_get_localized_field($dce, 'otherDataSources'); ?>
                      </li>
                    <?php endif; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->administrativeDatabases)): ?>
              <tr>
                <td><h5><?php print t('Administrative Databases') ?></h5></td>
                <td>
                  <ul>
                    <?php foreach ($dce->administrativeDatabases as $database): ?>
                      <li>
                        <?php print $database; ?>
                      </li>
                    <?php endforeach; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->bioSamples)): ?>
              <tr>
                <td><h5><?php print t('Bio Samples') ?>:</h5></td>
                <td>
                  <ul>
                    <?php foreach ($dce->bioSamples as $samples): ?>
                      <li>
                        <?php print $samples; ?>
                      </li>
                    <?php endforeach; ?>
                    <?php if (!empty($dce->otherBioSamples)): ?>
                      <li>
                        <?php print mica_client_commons_get_localized_field($dce, 'otherBioSamples'); ?>
                      </li>
                    <?php endif; ?>
                  </ul>
                </td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($dce->tissueTypes)): ?>
              <tr>
                <td><h5><?php print t('Tissue Types') ?></h5></td>
                <td><p><?php print mica_client_commons_get_localized_field($dce, 'tissueTypes'); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($attachements)): ?>
              <tr>
                <td><h5><?php print t('Documents') ?></h5></td>
                <td>
                  <ul class="list-group">
                    <?php print $attachements; ?>
                  </ul>
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
