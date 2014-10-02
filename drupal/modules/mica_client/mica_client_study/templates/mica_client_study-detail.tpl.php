<?php
//dpm($study_dto);
//dpm($study_variables_aggs);
?>
<p>
  <?php if (!empty($study_dto->logo->id)): ?>
    <img src="<?php print mica_client_commons_safe_expose_server_url($study_dto->id, $study_dto->logo, 'study') ?>"
         class="imageThumb">
  <?php endif; ?>
  <?php print mica_client_commons_get_localized_field($study_dto, 'objectives'); ?>
</p>
<div class="clearfix"></div>
<article>

<section>
  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 right-indent">
        <!-- GENERAL INFORMATION -->
        <?php if (!empty($study_dto->acronym) || !empty($study_dto->website) ||
          !empty($study_dto->investigators) || !empty($study_dto->contacts) ||
          !empty($study_dto->startYear) || !empty($study_dto->endYear) ||
          !empty($study_dto->networks)
        ): ?>
          <h3><?php print t('Overview') ?></h3>

          <?php if (!empty($study_dto->acronym)): ?>
            <h5><?php print t('Acronym') ?></h5>
            <p><?php print mica_client_commons_get_localized_field($study_dto, 'acronym'); ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->website)): ?>
            <h5><?php print t('Website') ?></h5>
            <p><?php
              print l($study_dto->website,
                $study_dto->website,
                array('attributes' => array('target' => '_blank')));
              ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->investigators)): ?>
            <h5><?php print t('Investigators') ?></h5>
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
          <?php endif; ?>

          <?php if (!empty($study_dto->contacts)): ?>
            <h5><?php print t('Contacts') ?></h5>
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
          <?php endif; ?>

          <?php if (!empty($study_dto->startYear)): ?>
            <h5><?php print t('Study Start Year') ?></h5>
            <p><?php print $study_dto->startYear; ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->endYear)): ?>
            <h5><?php print t('Study End Year') ?></h5>
            <p><?php print $study_dto->endYear; ?></p>
          <?php endif; ?>

          <!--
        <?php if (!empty($study_dto->networks)): ?>
        <h5><?php print t('Networks') ?> :</h5>
        <p>
          <a href=""><?php //print $study_dto->networks; ?></a>
        </p>
        </div>
        <?php endif; ?>
        -->
        <?php endif; ?>
      </div>
      <div class="col-xs-6">
        <!-- GENERAL DESIGN -->
        <?php if (!empty($study_dto->methods->designs) ||
          !empty($study_dto->methods->followUpInfo) ||
          !empty($study_dto->methods->recruitments) ||
          !empty($study_dto->numberOfParticipants->participant->number) ||
          !empty($study_dto->numberOfParticipants->sample->number) ||
          !empty($study_dto->numberOfParticipants->info)
        ): ?>
          <h3><?php print t('Design') ?></h3>

          <?php if (!empty($study_dto->methods->designs)): ?>
            <h5><?php print t('Study Designs') ?></h5>
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
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->followUpInfo)): ?>
            <h5><?php print t('General Information on Follow Up (profile and frequency)') ?></h5>
            <p><?php print mica_client_commons_get_localized_field($study_dto->methods, 'followUpInfo'); ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->recruitments)): ?>
            <h5><?php print t('Recruitment Target') ?></h5>
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
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->participant->number)): ?>
            <h5><?php print t('Target number of participants') ?></h5>
            <p>
              <?php print $study_dto->numberOfParticipants->participant->number; ?>
              <?php if (!empty($study_dto->numberOfParticipants->participant->noLimit)): ?>
                (<?php print t('No limit'); ?>)
              <?php endif; ?>
            </p>
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->sample->number)): ?>
            <h5><?php print t('Target number of participants with biological samples') ?></h5>
            <p>
              <?php print $study_dto->numberOfParticipants->sample->number; ?>
              <?php if (!empty($study_dto->numberOfParticipants->sample->noLimit)): ?>
                (<?php print t('No limit'); ?>)
              <?php endif; ?>
            </p>
          <?php endif; ?>

          <?php if (!empty($study_dto->numberOfParticipants->info)): ?>
            <h5><?php print t('Supplementary information about target number of participants') ?></h5>
            <p><?php print mica_client_commons_get_localized_field($study_dto->numberOfParticipants, 'info'); ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->methods->info)): ?>
            <h5><?php print t('Supplementary information') ?></h5>
            <p><?php print mica_client_commons_get_localized_field($study_dto->methods, 'info'); ?></p>
          <?php endif; ?>

        <?php endif; ?>
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

          <h5><?php print t('Data (questionnaire-derived, measured...)'); ?></h5>

          <p>
            <?php if (in_array('data', $study_dto->access)): ?>
              <?php print t('Yes'); ?>
            <?php else : ?>
              <?php print t('No'); ?>
            <?php endif; ?>
          </p>

          <h5><?php print t('Biological samples'); ?></h5>

          <p>
            <?php if (in_array('bio_samples', $study_dto->access)): ?>
              <?php print t('Yes'); ?>
            <?php else : ?>
              <?php print t('No'); ?>
            <?php endif; ?>
          </p>

          <?php if (in_array('other', $study_dto->access)): ?>
            <h5><?php print t('Other'); ?></h5>
            <p>
              <?php if (in_array('other', $study_dto->access)): ?>
                <?php print t('Yes'); ?> --
              <?php endif; ?>
              <?php if (!empty($study_dto->otherAccess)): ?>
                <?php print mica_client_commons_get_localized_field($study_dto, 'otherAccess'); ?>
              <?php endif; ?>
            </p>
          <?php endif; ?>
        <?php else : ?>
          <p><?php print t('Access to external researchers or third parties neither provided nor foreseen.'); ?></p>
        <?php endif; ?>
      </div>
      <div class="col-xs-6">
        <!-- MARKER PAPER -->
        <?php if (!empty($study_dto->markerPaper) || !empty($study_dto->pubmedId)): ?>
          <h3><?php print t('Marker Paper') ?></h3>

          <?php if (!empty($study_dto->markerPaper)): ?>
            <h5><?php print t('Marker paper'); ?></h5>
            <p><?php print $study_dto->markerPaper; ?></p>
          <?php endif; ?>

          <?php if (!empty($study_dto->pubmedId)): ?>
            <h5><?php print t('Pubmed ID'); ?></h5>
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

<section>
  <div class="container-fluid">
    <div class="row">
      <div class="col-xs-6 right-indent">
        <!-- SUPPLEMENTARY INFORMATION -->
        <h3><?php print t('Supplementary Information'); ?></h3>
        <?php if (!empty($study_dto->info)): ?>
          <p><?php print mica_client_commons_get_localized_field($study_dto, 'info'); ?></p>
        <?php else : ?>
          <i><?php print t('None'); ?></i>
        <?php endif; ?>
      </div>
      <div class="col-xs-6">
        <!-- DOCUMENTS -->
        <?php if (!empty($study_dto->attachments)): ?>
          <h3><?php print t('Documents'); ?></h3>
          <div>
            <?php if (!empty($study_attachements)): ?>
              <ul class="list-group">
                <?php print $study_attachements; ?>
              </ul>
            <?php endif; ?>
          </div>
        <?php endif; ?>
      </div>
    </div>
  </div>
</section>

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