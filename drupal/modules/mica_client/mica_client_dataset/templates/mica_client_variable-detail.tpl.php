<?php
dpm($variable_dto);
//dpm($datset_type);
?>
  <article>
    <header>
    </header>
    <footer>
    </footer>
  </article>

<?php if (!empty($variable_dto->datasetName) || !empty($variable_dto->studyIds) ||
  !empty($variable_dto->name) ||
  !empty($variable_dto->valueType) || !empty($variable_dto->attributes) ||
  !empty($variable_dto->description) || !empty($variable_dto->comment) ||
  !empty($variable_dto->label)
): ?>
  <section class="block">
  <h2><?php print t('General Information') ?></h2>

  <div>

    <?php if (!empty($variable_dto->label)): ?>
      <div class="field field-name-field-label field-type-text  clearfix">
        <div class="field-label"><?php print t('Label') ?> :</div>
        <div class="field-items">
          <div class="field-item even">
            <?php print $variable_dto->label; ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($variable_dto->description): ?>
      <div class="field field-name-description field-type-list-boolean clearfix">
        <div class="field-label">
          <?php print t('Description'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php print $variable_dto->description; ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($variable_dto->studyIds): ?>
      <div class="field field-name-field-studyIds field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Studies'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">

            <?php
            foreach ($variable_dto->studyIds as $stuyId) {
              print l($stuyId, 'mica/study/' . $stuyId .
                  '/' . $stuyId) . '</br>';
            }

            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($variable_dto->datasetId): ?>
      <div class="field field-name-field-datasetName field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Dataset'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print l(mica_client_commons_get_localized_field($variable_dto, 'datasetName'), 'mica/dataset/' . mica_client_commons_to_slug(mica_client_commons_get_localized_field($variable_dto, 'datasetName')) .
                '/dataset/' . $variable_dto->datasetId) . '</br>';
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($variable_dto->valueType): ?>
      <div class="field field-name-field-valueType field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Value Type'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print($variable_dto->valueType);
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($variable_dto->comment): ?>
      <div class="field field-name-field-comment field-type-list-boolean  clearfix">
        <div class="field-label">
          <?php print t('Value Type'); ?> :
        </div>
        <div class="field-items">
          <div class="field-item even">
            <?php
            print($variable_dto->comment);
            ?>
          </div>
        </div>
      </div>
    <?php endif; ?>


    <div class="field field-name-field-statistics field-type-list-boolean  clearfix">
      <div class="field-label">
        <?php print t('Statistics'); ?>
      </div>

      <div id="param-statistics" var-id="<?php print $variable_dto->id; ?>">
        <div id="txtblnk"> <?php print t('Please wait loading Statistics table....'); ?> </div>
      </div>
    </div>
  </div>


<?php endif; ?>
<?php //if (!empty($variable_dto->website)): ?>
  <!--        <div class="field field-name-field-website field-type-link-field field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Website') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php
//              print l($variable_dto->website,
//                $context_detail->website,
//                array('attributes' => array('target' => '_blank')));
//
?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->investigators)): ?>
  <!--        <div class="field field-name-field-investigators field-type-node-reference field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Investigators') ?><!-- :</div>-->
  <!--          --><?php //foreach ($context_detail->investigators as $investigator) : ?>
  <!--            <div class="field-items">-->
  <!--              <div class="field-item even"><a href="">-->
  <!--                  --><?php //print $investigator->title; ?>
  <!--                  --><?php //print $investigator->firstName; ?>
  <!--                  --><?php //print $investigator->lastName; ?>
  <!--                  ( --><?php //print mica_client_commons_get_localized_field($investigator->institution, 'name'); ?>
  <!--                  )-->
  <!--                </a></div>-->
  <!--            </div>-->
  <!--          --><?php //endforeach; ?>
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->contacts)): ?>
  <!--        <div class="field field-name-field-contacts-ref field-type-node-reference field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Contacts') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->contacts as $contact) : ?>
  <!--              <div class="field-items">-->
  <!--                <div class="field-item even"><a href="">-->
  <!--                    --><?php //print $contact->title; ?>
  <!--                    --><?php //print $contact->firstName; ?>
  <!--                    --><?php //print $contact->lastName; ?>
  <!--                    ( --><?php //print mica_client_commons_get_localized_field($contact->institution, 'name'); ?>
  <!--                    )-->
  <!--                  </a></div>-->
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->startYear)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-study-start-year field-type-number-integer field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Study Start Year') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div-->
  <!--              class="field-item even">--><?php //print $context_detail->startYear; ?><!--</div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->endYear)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-study-end-year field-type-number-integer field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Study End Year') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div-->
  <!--              class="field-item even">--><?php //print $context_detail->endYear; ?><!--</div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!--      <!---->
  <!--        --><?php //if (!empty($context_detail->networks)): ?>
  <!--        <div class="field field-name-field-networks field-type-node-reference field-label-inline clearfix hide">-->
  <!--            <div class="field-label">--><?php //print t('Networks') ?><!-- :</div>-->
  <!--            <div class="field-items">-->
  <!--                <div class="field-item even">-->
  <!--                    <a href="">--><?php ////print $context_detail->networks; ?><!--</a>-->
  <!--                </div>-->
  <!--            </div>-->
  <!--        </div>-->
  <!--        --><?php //endif; ?>
  <!--        -->-->
  <!--    </div>-->
  <!---->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->methods->designs) ||
//  !empty($context_detail->methods->followUpInfo) ||
//  !empty($context_detail->methods->recruitments) ||
//  !empty($context_detail->numberOfParticipants->participant->number) ||
//  !empty($context_detail->numberOfParticipants->sample->number) ||
//  !empty($context_detail->numberOfParticipants->info)
//):
?>
  <!--  <section>-->
  <!--    <h2>--><?php //print t('General Design') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->designs)): ?>
  <!--        <div class="field field-name-field-design field-type-list-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Study design') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->methods->designs as $design): ?>
  <!--              <div class="field-item">-->
  <!--                --><?php //if ($design == 'other'): ?>
  <!--                  <div class="field-label">-->
  <!--                    --><?php //print $design ?><!-- :-->
  <!--                  </div>-->
  <!--                  <span class="other-sub-value">-->
  <!--                                     --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'otherDesign'); ?>
  <!--                            </span>-->
  <!--                --><?php //else: ?>
  <!--                  --><?php //print $design; ?>
  <!--                --><?php //endif; ?>
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->followUpInfo)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-info-design-follow-up field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('General Information on Follow Up (profile and frequency)') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'followUpInfo'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->recruitments)): ?>
  <!--        <div class="field field-name-field-recruitment field-type-list-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Recruitment target') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->methods->recruitments as $recruitment): ?>
  <!--              <div class="field-item">-->
  <!--                --><?php //if ($recruitment == 'other'): ?>
  <!--                  <div class="field-label">-->
  <!--                    --><?php //print $recruitment ?><!-- :-->
  <!--                  </div>-->
  <!--                  <span class="other-sub-value">-->
  <!--                                     --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'otherRecruitment'); ?>
  <!--                            </span>-->
  <!--                --><?php //else: ?>
  <!--                  --><?php //print $recruitment; ?>
  <!--                --><?php //endif; ?>
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->participant->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-number-participants field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Target number of participants') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->numberOfParticipants->participant->number; ?>
  <!--            </div>-->
  <!--            <div class="field-item odd">-->
  <!--              --><?php //print mica_client_commons_get_if_no_limit($context_detail->numberOfParticipants->participant->noLimit); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->sample->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-number-biosamples field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Target number of participants with biological samples') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->numberOfParticipants->sample->number; ?>
  <!--            </div>-->
  <!--            <div class="field-item odd">-->
  <!--              --><?php //print mica_client_commons_get_if_no_limit($context_detail->numberOfParticipants->sample->noLimit); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->info)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-nb-supp-info field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Supplementary information about target number of participants') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->numberOfParticipants, 'info'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->sample->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-recruitment-supp-info field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Supplementary information') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'info'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (in_array('data', $context_detail->access) ||
//  in_array('bio_samples', $context_detail->access) ||
//  in_array('other', $context_detail->access)
//):
?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Access') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //print t('Access to external researchers or third parties provided or foreseen for'); ?>
  <!---->
  <!--      <div class="field field-name-field-access-data field-type-list-boolean field-label-inline clearfix">-->
  <!--        <div class="field-label">-->
  <!--          --><?php //print t('Data (questionnaire-derived, measured...)'); ?><!-- :-->
  <!--        </div>-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (in_array('data', $context_detail->access)): ?>
  <!--              --><?php //print t('Yes'); ?>
  <!--            --><?php //else : ?>
  <!--              --><?php //print t('No'); ?>
  <!--            --><?php //endif; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      <div class="field field-name-field-access-biosamples field-type-list-boolean field-label-inline clearfix">-->
  <!--        <div class="field-label">-->
  <!--          --><?php //print t('Biological samples'); ?><!-- :-->
  <!--        </div>-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (in_array('bio_samples', $context_detail->access)): ?>
  <!--              --><?php //print t('Yes'); ?>
  <!--            --><?php //else : ?>
  <!--              --><?php //print t('No'); ?>
  <!--            --><?php //endif; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      --><?php //if (in_array('other', $context_detail->access)): ?>
  <!--        <div class="field field-name-field-access-other field-type-list-boolean field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Other'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //if (in_array('other', $context_detail->access)): ?>
  <!--                --><?php //print t('Yes'); ?><!-- ---->
  <!--              --><?php //endif; ?>
  <!--              --><?php //if (!empty($context_detail->otherAccess)): ?>
  <!--                --><?php //print mica_client_commons_get_localized_field($context_detail, 'otherAccess'); ?>
  <!--              --><?php //endif; ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->markerPaper) ||
//  !empty($context_detail->pubmedId)
//):
?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Marker Paper') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->markerPaper)): ?>
  <!--        <div class="field field-name-field-marker-paper field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Marker paper'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->markerPaper; ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->pubmedId)): ?>
  <!--        <div class="field field-name-field-pubmedid field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Pubmed ID'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              <a href="http://www.ncbi.nlm.nih.gov/pubmed/--><?php //print $context_detail->pubmedId; ?><!--">-->
  <!--                PUBMED --><?php //print $context_detail->pubmedId; ?>
  <!--              </a>-->
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->info)): ?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Supplementary Information'); ?><!-- :</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      <div class="field field-name-field-supp-infos field-type-text-long field-label-hidden">-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (!empty($context_detail->info)): ?>
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail, 'info'); ?>
  <!--            --><?php //endif; ?>
  <!---->
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->attachments)): ?>
  <!--        --><?php //print mica_client_study_get_attachment_file($context_detail->id, $context_detail->attachments); ?>
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
  --><?php //if (!empty($variable_dto->website)): ?>
  <!--        <div class="field field-name-field-website field-type-link-field field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Website') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php
//              print l($variable_dto->website,
//                $context_detail->website,
//                array('attributes' => array('target' => '_blank')));
//
?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->investigators)): ?>
  <!--        <div class="field field-name-field-investigators field-type-node-reference field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Investigators') ?><!-- :</div>-->
  <!--          --><?php //foreach ($context_detail->investigators as $investigator) : ?>
  <!--            <div class="field-items">-->
  <!--              <div class="field-item even"><a href="">-->
  <!--                  --><?php //print $investigator->title; ?>
  <!--                  --><?php //print $investigator->firstName; ?>
  <!--                  --><?php //print $investigator->lastName; ?>
  <!--                  ( --><?php //print mica_client_commons_get_localized_field($investigator->institution, 'name'); ?>
  <!--                  )-->
  <!--                </a></div>-->
  <!--            </div>-->
  <!--          --><?php //endforeach; ?>
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->contacts)): ?>
  <!--        <div class="field field-name-field-contacts-ref field-type-node-reference field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Contacts') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->contacts as $contact) : ?>
  <!--              <div class="field-items">-->
  <!--                <div class="field-item even"><a href="">-->
  <!--                    --><?php //print $contact->title; ?>
  <!--                    --><?php //print $contact->firstName; ?>
  <!--                    --><?php //print $contact->lastName; ?>
  <!--                    ( --><?php //print mica_client_commons_get_localized_field($contact->institution, 'name'); ?>
  <!--                    )-->
  <!--                  </a></div>-->
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->startYear)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-study-start-year field-type-number-integer field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Study Start Year') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div-->
  <!--              class="field-item even">--><?php //print $context_detail->startYear; ?><!--</div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->endYear)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-study-end-year field-type-number-integer field-label-inline clearfix">-->
  <!--          <div class="field-label">--><?php //print t('Study End Year') ?><!-- :</div>-->
  <!--          <div class="field-items">-->
  <!--            <div-->
  <!--              class="field-item even">--><?php //print $context_detail->endYear; ?><!--</div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!--      <!---->
  <!--        --><?php //if (!empty($context_detail->networks)): ?>
  <!--        <div class="field field-name-field-networks field-type-node-reference field-label-inline clearfix hide">-->
  <!--            <div class="field-label">--><?php //print t('Networks') ?><!-- :</div>-->
  <!--            <div class="field-items">-->
  <!--                <div class="field-item even">-->
  <!--                    <a href="">--><?php ////print $context_detail->networks; ?><!--</a>-->
  <!--                </div>-->
  <!--            </div>-->
  <!--        </div>-->
  <!--        --><?php //endif; ?>
  <!--        -->-->
  <!--    </div>-->
  <!---->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->methods->designs) ||
//  !empty($context_detail->methods->followUpInfo) ||
//  !empty($context_detail->methods->recruitments) ||
//  !empty($context_detail->numberOfParticipants->participant->number) ||
//  !empty($context_detail->numberOfParticipants->sample->number) ||
//  !empty($context_detail->numberOfParticipants->info)
//):
?>
  <!--  <section>-->
  <!--    <h2>--><?php //print t('General Design') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->designs)): ?>
  <!--        <div class="field field-name-field-design field-type-list-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Study design') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->methods->designs as $design): ?>
  <!--              <div class="field-item">-->
  <!--                --><?php //if ($design == 'other'): ?>
  <!--                  <div class="field-label">-->
  <!--                    --><?php //print $design ?><!-- :-->
  <!--                  </div>-->
  <!--                  <span class="other-sub-value">-->
  <!--                                     --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'otherDesign'); ?>
  <!--                            </span>-->
  <!--                --><?php //else: ?>
  <!--                  --><?php //print $design; ?>
  <!--                --><?php //endif; ?>
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->followUpInfo)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-info-design-follow-up field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('General Information on Follow Up (profile and frequency)') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'followUpInfo'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!---->
  <!--      --><?php //if (!empty($context_detail->methods->recruitments)): ?>
  <!--        <div class="field field-name-field-recruitment field-type-list-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Recruitment target') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            --><?php //foreach ($context_detail->methods->recruitments as $recruitment): ?>
  <!--              <div class="field-item">-->
  <!--                --><?php //if ($recruitment == 'other'): ?>
  <!--                  <div class="field-label">-->
  <!--                    --><?php //print $recruitment ?><!-- :-->
  <!--                  </div>-->
  <!--                  <span class="other-sub-value">-->
  <!--                                     --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'otherRecruitment'); ?>
  <!--                            </span>-->
  <!--                --><?php //else: ?>
  <!--                  --><?php //print $recruitment; ?>
  <!--                --><?php //endif; ?>
  <!--              </div>-->
  <!--            --><?php //endforeach; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->participant->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-number-participants field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Target number of participants') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->numberOfParticipants->participant->number; ?>
  <!--            </div>-->
  <!--            <div class="field-item odd">-->
  <!--              --><?php //print mica_client_commons_get_if_no_limit($context_detail->numberOfParticipants->participant->noLimit); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->sample->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-number-biosamples field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Target number of participants with biological samples') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->numberOfParticipants->sample->number; ?>
  <!--            </div>-->
  <!--            <div class="field-item odd">-->
  <!--              --><?php //print mica_client_commons_get_if_no_limit($context_detail->numberOfParticipants->sample->noLimit); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->info)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-target-nb-supp-info field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Supplementary information about target number of participants') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->numberOfParticipants, 'info'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->numberOfParticipants->sample->number)): ?>
  <!--        <div-->
  <!--          class="field field-name-field-recruitment-supp-info field-type-text-long field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Supplementary information') ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail->methods, 'info'); ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (in_array('data', $context_detail->access) ||
//  in_array('bio_samples', $context_detail->access) ||
//  in_array('other', $context_detail->access)
//):
?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Access') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //print t('Access to external researchers or third parties provided or foreseen for'); ?>
  <!---->
  <!--      <div class="field field-name-field-access-data field-type-list-boolean field-label-inline clearfix">-->
  <!--        <div class="field-label">-->
  <!--          --><?php //print t('Data (questionnaire-derived, measured...)'); ?><!-- :-->
  <!--        </div>-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (in_array('data', $context_detail->access)): ?>
  <!--              --><?php //print t('Yes'); ?>
  <!--            --><?php //else : ?>
  <!--              --><?php //print t('No'); ?>
  <!--            --><?php //endif; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      <div class="field field-name-field-access-biosamples field-type-list-boolean field-label-inline clearfix">-->
  <!--        <div class="field-label">-->
  <!--          --><?php //print t('Biological samples'); ?><!-- :-->
  <!--        </div>-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (in_array('bio_samples', $context_detail->access)): ?>
  <!--              --><?php //print t('Yes'); ?>
  <!--            --><?php //else : ?>
  <!--              --><?php //print t('No'); ?>
  <!--            --><?php //endif; ?>
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      --><?php //if (in_array('other', $context_detail->access)): ?>
  <!--        <div class="field field-name-field-access-other field-type-list-boolean field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Other'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //if (in_array('other', $context_detail->access)): ?>
  <!--                --><?php //print t('Yes'); ?><!-- ---->
  <!--              --><?php //endif; ?>
  <!--              --><?php //if (!empty($context_detail->otherAccess)): ?>
  <!--                --><?php //print mica_client_commons_get_localized_field($context_detail, 'otherAccess'); ?>
  <!--              --><?php //endif; ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->markerPaper) ||
//  !empty($context_detail->pubmedId)
//):
?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Marker Paper') ?><!--</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->markerPaper)): ?>
  <!--        <div class="field field-name-field-marker-paper field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Marker paper'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              --><?php //print $context_detail->markerPaper; ?>
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--      --><?php //if (!empty($context_detail->pubmedId)): ?>
  <!--        <div class="field field-name-field-pubmedid field-type-text field-label-inline clearfix">-->
  <!--          <div class="field-label">-->
  <!--            --><?php //print t('Pubmed ID'); ?><!-- :-->
  <!--          </div>-->
  <!--          <div class="field-items">-->
  <!--            <div class="field-item even">-->
  <!--              <a href="http://www.ncbi.nlm.nih.gov/pubmed/--><?php //print $context_detail->pubmedId; ?><!--">-->
  <!--                PUBMED --><?php //print $context_detail->pubmedId; ?>
  <!--              </a>-->
  <!--            </div>-->
  <!--          </div>-->
  <!--        </div>-->
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>
  <!---->
<?php //if (!empty($context_detail->info)): ?>
  <!--  <section>-->
  <!--    <h2 class="block-title">--><?php //print t('Supplementary Information'); ?><!-- :</h2>-->
  <!---->
  <!--    <div>-->
  <!---->
  <!--      <div class="field field-name-field-supp-infos field-type-text-long field-label-hidden">-->
  <!--        <div class="field-items">-->
  <!--          <div class="field-item even">-->
  <!--            --><?php //if (!empty($context_detail->info)): ?>
  <!--              --><?php //print mica_client_commons_get_localized_field($context_detail, 'info'); ?>
  <!--            --><?php //endif; ?>
  <!---->
  <!--          </div>-->
  <!--        </div>-->
  <!--      </div>-->
  <!---->
  <!--      --><?php //if (!empty($context_detail->attachments)): ?>
  <!--        --><?php //print mica_client_study_get_attachment_file($context_detail->id, $context_detail->attachments); ?>
  <!--      --><?php //endif; ?>
  <!---->
  <!--    </div>-->
  <!--  </section>-->
<?php //endif; ?>