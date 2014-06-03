<?php //dpm($context_detail['data']);?>
<article>
    <header>
    </header>
    <span class="print-link"></span>

    <div class="field field-name-field-logo field-type-image field-label-hidden">
        <div class="field-items">
            <div class="field-item even">
                <img typeof="foaf:Image"
                     src="https://www.maelstrom-research.org/sites/default/files/styles/study_logo/public/CLSA_Logo_NoWordmark_2colour_RGB.jpg?itok=yXZJMeCk"
                     width="120" height="96" alt="">
            </div>
        </div>
    </div>
    <div class="field field-name-body field-type-text-with-summary field-label-hidden">
        <div class="field-items">
            <div class="field-item even" property="content:encoded">
                <p>
                    <?php print mica_commons_get_localized_field($context_detail['data'], 'objectives'); ?>
                </p>
            </div>
        </div>
    </div>
    <footer>
    </footer>
</article>
<section>
    <h2><?php print t('General Information') ?></h2>

    <div>

        <?php if(!empty($context_detail['data']->acronym)): ?>
        <div class="field field-name-field-acroym field-type-text field-label-inline clearfix">
            <div class="field-label"><?php print t('Acronym') ?> :</div>
            <div class="field-items">
                <div class="field-item even">
                    <?php print mica_commons_get_localized_field($context_detail['data'], 'acronym'); ?>
                </div>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->website)): ?>
        <div class="field field-name-field-website field-type-link-field field-label-inline clearfix">
            <div class="field-label"><?php print t('Website') ?> :</div>
            <div class="field-items">
                <div class="field-item even"><a href=" <?php print $context_detail['data']->website; ?>"
                                                target="_blank">
                        <?php print $context_detail['data']->website; ?>
                    </a>
                </div>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->investigators)): ?>
        <div class="field field-name-field-investigators field-type-node-reference field-label-inline clearfix">
            <div class="field-label"><?php print t('Investigators') ?> :</div>
            <?php foreach ($context_detail['data']->investigators as $investigator) : ?>
                <div class="field-items">
                    <div class="field-item even"><a href="">
                            <?php print $investigator->title; ?>
                            <?php print $investigator->firstName; ?>
                            <?php print $investigator->lastName; ?>
                            ( <?php print mica_commons_get_localized_field($investigator->institution, 'name'); ?>)
                        </a></div>
                </div>
            <?php endforeach; ?>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->contacts)): ?>
        <div class="field field-name-field-contacts-ref field-type-node-reference field-label-inline clearfix">
            <div class="field-label"><?php print t('Contacts') ?> :</div>
            <div class="field-items">
                <?php foreach ($context_detail['data']->contacts as $contact) : ?>
                    <div class="field-items">
                        <div class="field-item even"><a href="">
                                <?php print $contact->title; ?>
                                <?php print $contact->firstName; ?>
                                <?php print $contact->lastName; ?>
                                ( <?php print mica_commons_get_localized_field($contact->institution, 'name'); ?>)
                            </a></div>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->startYear)): ?>
        <div class="field field-name-field-study-start-year field-type-number-integer field-label-inline clearfix">
            <div class="field-label"><?php print t('Study Start Year') ?> :</div>
            <div class="field-items">
                <div
                    class="field-item even"><?php print $context_detail['data']->startYear; ?></div>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->endYear)): ?>
            <div class="field field-name-field-study-end-year field-type-number-integer field-label-inline clearfix">
                <div class="field-label"><?php print t('Study End Year') ?> :</div>
                <div class="field-items">
                    <div
                        class="field-item even"><?php print $context_detail['data']->endYear; ?></div>
                </div>
            </div>
        <?php endif; ?>
        <!--
        <?php if(!empty($context_detail['data']->networks)): ?>
        <div class="field field-name-field-networks field-type-node-reference field-label-inline clearfix hide">
            <div class="field-label"><?php print t('Networks') ?> :</div>
            <div class="field-items">
                <div class="field-item even">
                    <a href=""><?php //print $context_detail['data']->networks; ?></a>
                </div>
            </div>
        </div>
        <?php endif; ?>
        -->
    </div>

</section>
<section>
    <h2><?php print t('General Design') ?></h2>

    <div>

        <?php if(!empty($context_detail['data']->methods->designs)): ?>
        <div class="field field-name-field-design field-type-list-text field-label-inline clearfix">
            <div class="field-label">
                <?php print t('Study design') ?> :
            </div>
            <div class="field-items">
                <?php foreach ($context_detail['data']->methods->designs as $design): ?>
                    <div class="field-item">
                        <?php if ($design == 'other'): ?>
                            <div class="field-label">
                                <?php print $design ?> :
                            </div>
                            <span class="other-sub-value">
                                     <?php print mica_commons_get_localized_field($context_detail['data']->methods, 'otherDesign'); ?>
                            </span>
                        <?php else: ?>
                            <?php print $design; ?>
                        <?php endif; ?>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->methods->followUpInfo)): ?>
        <div class="field field-name-field-info-design-follow-up field-type-text-long field-label-inline clearfix">
            <div class="field-label">
                <?php print t('General Information on Follow Up (profile and frequency)') ?> :
            </div>
            <div class="field-items">
                <div class="field-item even">
                    <?php print mica_commons_get_localized_field($context_detail['data']->methods, 'followUpInfo'); ?>
                </div>
            </div>
        </div>
        <?php endif; ?>


        <?php if(!empty($context_detail['data']->methods->recruitments)): ?>
        <div class="field field-name-field-recruitment field-type-list-text field-label-inline clearfix">
            <div class="field-label">
                <?php print t('Recruitment target') ?> :
            </div>
            <div class="field-items">
                <?php foreach ($context_detail['data']->methods->recruitments as $recruitment): ?>
                    <div class="field-item">
                        <?php if ($recruitment == 'other'): ?>
                            <div class="field-label">
                                <?php print $recruitment ?> :
                            </div>
                            <span class="other-sub-value">
                                     <?php print mica_commons_get_localized_field($context_detail['data']->methods, 'otherRecruitment'); ?>
                            </span>
                        <?php else: ?>
                            <?php print $recruitment; ?>
                        <?php endif; ?>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->numberOfParticipants->participant->number)): ?>
        <div class="field field-name-field-target-number-participants field-type-text field-label-inline clearfix">
            <div class="field-label">
                <?php print t('Target number of participants') ?> :
            </div>
            <div class="field-items">
                <div class="field-item even">
                    <?php print $context_detail['data']->numberOfParticipants->participant->number; ?>
                </div>
                <div class="field-item odd">
                    <?php print get_if_no_limite($context_detail['data']->numberOfParticipants->participant->noLimit); ?>
                </div>
            </div>
        </div>
        <?php endif; ?>

        <?php if(!empty($context_detail['data']->numberOfParticipants->sample->number)): ?>
        <div class="field field-name-field-target-number-biosamples field-type-text field-label-inline clearfix">
            <div class="field-label">
                <?php print t('Target number of participants with biological samples') ?> :
            </div>
            <div class="field-items">
                <div class="field-item even">
                    <?php print $context_detail['data']->numberOfParticipants->sample->number; ?>
                </div>
                <div class="field-item odd">
                    <?php print get_if_no_limite($context_detail['data']->numberOfParticipants->sample->noLimit); ?>
                </div>
            </div>
        </div>
        <?php endif; ?>



    </div>


</section>