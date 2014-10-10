<?php
//dpm($study_dto);
//dpm($study_variables_aggs);
?>
<div>
  <p>
    <?php if (!empty($study_dto->logo->id)): ?>
      <img src="<?php print mica_client_commons_safe_expose_server_url($study_dto->id, $study_dto->logo, 'study') ?>"
           class="imageThumb">
    <?php endif; ?>
    <?php print mica_client_commons_get_localized_field($study_dto, 'objectives'); ?>
  </p>

  <div class="pull-right md-bottom-margin">
    <?php
    print l(t('Search Variables'), 'mica/search',
      array(
        'query' => array(
          'type' => 'variables',
          'query' => '{"variables":{"terms":{"studyIds":["' . $study_dto->id . '"]}}}'
        ),
        'attributes' => array('class' => 'btn btn-primary')
      ));
    ?>
    <?php
    print l(t('Coverage'), 'mica/coverage',
      array(
        'query' => array(
          'type' => 'variables',
          'query' => '{"variables":{"terms":{"studyIds":["' . $study_dto->id . '"]}}}'
        ),
        'attributes' => array('class' => 'btn btn-primary indent')
      ));
    ?>
  </div>
</div>

<div class="clearfix"></div>
<article>

<section>
  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 lg-right-indent">
        <!-- GENERAL INFORMATION -->
        <h3><?php print t('Overview') ?></h3>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($study_dto->acronym)): ?>
            <tr>
              <td><h5><?php print t('Acronym') ?></h5></td>
              <td><p><?php print mica_client_commons_get_localized_field($study_dto, 'acronym'); ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->website)): ?>
            <tr>
              <td><h5><?php print t('Website') ?></h5></td>
              <td>
                <p><?php
                  print l($study_dto->website,
                    $study_dto->website,
                    array('attributes' => array('target' => '_blank')));
                  ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->investigators)): ?>
            <tr>
              <td><h5><?php print t('Investigators') ?></h5></td>
              <td>
                <ul>
                  <?php foreach ($study_dto->investigators as $investigator) : ?>
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
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->contacts)): ?>
            <tr>
              <td><h5><?php print t('Contacts') ?></h5></td>
              <td>
                <ul>
                  <?php foreach ($study_dto->contacts as $contact) : ?>
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
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->startYear)): ?>
            <tr>
              <td><h5><?php print t('Study Start Year') ?></h5></td>
              <td><p><?php print $study_dto->startYear; ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->endYear)): ?>
            <tr>
              <td><h5><?php print t('Study End Year') ?></h5></td>
              <td><p><?php print $study_dto->endYear; ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->networks)): ?>
            <tr>
              <td><h5><?php print t('Networks') ?> :</h5></td>
              <td>
                <p>
                  <a href=""><?php //print $study_dto->networks; ?></a>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>
      </div>
      <div class="col-xs-6">
        <!-- GENERAL DESIGN -->
        <h3><?php print t('Design') ?></h3>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($study_dto->methods->designs)): ?>
            <tr>
              <td><h5><?php print t('Study Designs') ?></h5></td>
              <td>
                <ul>
                  <?php foreach ($study_dto->methods->designs as $design): ?>
                    <li>
                      <?php print t($design); ?>
                      <?php if ($design == 'other'): ?>
                        : <?php print mica_client_commons_get_localized_field($study_dto->methods, 'otherDesign'); ?>
                      <?php endif; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->followUpInfo)): ?>
            <tr>
              <td><h5><?php print t('General Information on Follow Up (profile and frequency)') ?></h5></td>
              <td><p><?php print mica_client_commons_get_localized_field($study_dto->methods, 'followUpInfo'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->recruitments)): ?>
            <tr>
              <td><h5><?php print t('Recruitment Target') ?></h5></td>
              <td>
                <ul>
                  <?php foreach ($study_dto->methods->recruitments as $recruitment): ?>
                    <li>
                      <?php print t($recruitment) ?>
                      <?php if ($recruitment == 'other'): ?>
                        : <?php print mica_client_commons_get_localized_field($study_dto->methods, 'otherRecruitment'); ?>
                      <?php endif; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->participant->number)): ?>
            <tr>
              <td><h5><?php print t('Target number of participants') ?></h5></td>
              <td>
                <p>
                  <?php print $study_dto->numberOfParticipants->participant->number; ?>
                  <?php if (!empty($study_dto->numberOfParticipants->participant->noLimit)): ?>
                    (<?php print t('No limit'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->sample->number)): ?>
            <tr>
              <td><h5><?php print t('Target number of participants with biological samples') ?></h5></td>
              <td>
                <p>
                  <?php print $study_dto->numberOfParticipants->sample->number; ?>
                  <?php if (!empty($study_dto->numberOfParticipants->sample->noLimit)): ?>
                    (<?php print t('No limit'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information about target number of participants') ?></h5></td>
              <td>
                <p><?php print mica_client_commons_get_localized_field($study_dto->numberOfParticipants, 'info'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->info)): ?>
            <tr>
              <td><h5><?php print t('Supplementary information') ?></h5></td>
              <td><p><?php print mica_client_commons_get_localized_field($study_dto->methods, 'info'); ?></p></td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>

      </div>
    </div>
  </div>
</section>

<section>
  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 right-indent">
        <!-- ACCESS -->
        <h3><?php print t('Access') ?></h3>

        <?php if (!empty($study_dto->access) && (in_array('data', $study_dto->access) ||
            in_array('bio_samples', $study_dto->access) ||
            in_array('other', $study_dto->access))
        ): ?>

          <p><?php print t('Access to external researchers or third parties provided or foreseen for:'); ?></p>
        <?php else : ?>
          <p><?php print t('Access to external researchers or third parties neither provided nor foreseen.'); ?></p>
        <?php endif; ?>

        <table class="table table-striped">
          <tbody>
          <tr>
            <td><h5><?php print t('Data (questionnaire-derived, measured...)'); ?></h5></td>
            <td>
              <p>
                <?php if (in_array('data', $study_dto->access)): ?>
                  <span class="glyphicon glyphicon-ok"></span>
                <?php else : ?>
                  <span class="glyphicon glyphicon-remove"></span>
                <?php endif; ?>
              </p>
            </td>
          </tr>

          <tr>
            <td><h5><?php print t('Biological samples'); ?></h5></td>
            <td>
              <p>
                <?php if (in_array('bio_samples', $study_dto->access)): ?>
                  <span class="glyphicon glyphicon-ok"></span>
                <?php else : ?>
                  <span class="glyphicon glyphicon-remove"></span>
                <?php endif; ?>
              </p>
            </td>
          </tr>

          <?php if (in_array('other', $study_dto->access)): ?>
            <tr>
              <td><h5><?php print t('Other'); ?></h5></td>
              <td>
                <p>
                  <?php if (in_array('other', $study_dto->access)): ?>
                    <span class="glyphicon glyphicon-ok right-indent"></span>
                  <?php endif; ?>
                  <?php if (!empty($study_dto->otherAccess)): ?>
                    (<?php print mica_client_commons_get_localized_field($study_dto, 'otherAccess'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>


      </div>
      <div class="col-xs-6">
        <!-- MARKER PAPER -->
        <?php if (!empty($study_dto->markerPaper) || !empty($study_dto->pubmedId)): ?>
          <h3><?php print t('Marker Paper') ?></h3>
          <?php if (!empty($study_dto->markerPaper)): ?>
            <p><?php print $study_dto->markerPaper; ?></p>
          <?php endif; ?>
          <?php if (!empty($study_dto->pubmedId)): ?>
            <p>
              <a href="http://www.ncbi.nlm.nih.gov/pubmed/<?php print $study_dto->pubmedId; ?>">
                PUBMED <?php print $study_dto->pubmedId; ?>
              </a>
            </p>
          <?php endif; ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
</section>

<!-- SUPPLEMENTARY INFORMATION -->
<?php if (!empty($study_dto->info)): ?>
  <section>
    <h3><?php print t('Supplementary Information'); ?></h3>

    <p><?php print mica_client_commons_get_localized_field($study_dto, 'info'); ?></p>
  </section>
<?php endif; ?>

<!-- DOCUMENTS -->
<?php if (!empty($study_dto->attachments)): ?>
  <section>
    <h3><?php print t('Documents'); ?></h3>

    <div>
      <?php if (!empty($study_attachements)): ?>
        <ul class="list-group">
          <?php print $study_attachements; ?>
        </ul>
      <?php endif; ?>
    </div>
  </section>
<?php endif; ?>

<!-- TIMELINE -->
<?php if (!empty($timeline)): ?>
  <section>
    <h3><?php print t('Timeline'); ?></h3>

    <p>
      <?php print t('Each colour in the timeline graph below represents a separate Study Population, while each segment in the graph represents a separate Data Collection Event. Clicking on a segment gives more detailed information on a Data Collection Event.') ?>
    </p>
    <?php print $timeline; ?>
  </section>
<?php endif; ?>

<!-- POPULATIONS -->
<?php if (!empty($populations)): ?>
  <section>
    <h3><?php print t('Populations'); ?></h3>
    <?php print $populations; ?>
  </section>
<?php endif; ?>

<!-- NETWORKS -->
<?php if (!empty($networks)): ?>
  <section>
    <h3><?php print t('Networks'); ?></h3>
    <?php print $networks; ?>
  </section>
<?php endif; ?>

<!-- DATASETS -->
<?php if (!empty($datasets)): ?>
  <section>
    <h3><?php print t('Datasets'); ?></h3>
    <?php print render($datasets['dataset-tab']); ?>
  </section>
<?php endif; ?>

<!-- VARIABLES -->
<?php if (!empty($datasets) && !empty($study_variables_aggs)): ?>
  <section>
    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-3 right-indent">
          <h3><?php print t('Variables') ?></h3>

          <h5><?php print t('Number of variables') ?></h5>

          <p>
            <?php print $study_variables_aggs['totalHits']; ?>
          </p>

          <?php
          print l(t('Search Variables'), 'mica/search',
            array(
              'query' => array(
                'type' => 'variables',
                'parent:id[]' => 'id.' . $study_dto->id
              ),
              'attributes' => array('class' => 'btn btn-primary')
            ));
          ?>
        </div>
        <div class="col-xs-9">
          <h3><?php print t('Domain Coverage') ?></h3>
          <!-- Variable aggregations can be reported here -->
          <div class="alert alert-info" role="alert"><strong>TODO</strong> charts here</div>
        </div>
      </div>
    </div>
  </section>
<?php endif; ?>

</article>