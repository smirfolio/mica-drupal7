<?php //dpm($context_population_detail); ?>

<div class="field field-name-body field-type-text-with-summary field-label-hidden">
    <div class="field-items">
        <div class="field-item even" property="content:encoded">
            <p>
                <?php print mica_commons_get_localized_field($context_population_detail, 'description'); ?>
            </p>

        </div>
    </div>
</div>

<div class="field field-name-field-pop-select-criteria field-type-list-text field-label-above">
    <div class="field-label">
        <?php print t('Selection criteria') ?> :
    </div>
    <div class="field-items">
        <?php if (isset($context_population_detail->selectionCriteria->gender)): ?>
            <?php if ($context_population_detail->selectionCriteria->gender === 0 || $context_population_detail->selectionCriteria->gender === 1): ?>
                <div class="field-item odd">
                    <div class="inner-label">
                        <?php print t('Gender') ?> :
                    </div>
                    <div class="inner-value">
                        <?php print  mica_commons_get_gender($context_population_detail->selectionCriteria->gender); ?>
                    </div>
                </div>
            <?php endif; ?>
        <?php endif; ?>
        <?php if (!empty($context_population_detail->selectionCriteria->ageMin) || !empty($context_population_detail->selectionCriteria->ageMax)): ?>
            <div class="field-item even">
                <div class="inner-label">
                    <?php print t('Age') ?> :
                </div>
                <div class="inner-value">
                    <?php !empty($context_population_detail->selectionCriteria->ageMin) ? print t('Minimum') . ' '
                        . $context_population_detail->selectionCriteria->ageMin : NULL; ?>,
                    <?php !empty($context_population_detail->selectionCriteria->ageMax) ? print t('Maximum') . ' '
                        . $context_population_detail->selectionCriteria->ageMax : NULL; ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->selectionCriteria->countriesIso)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Country'); ?> :
                </div>
                <div class="inner-value">
                    <?php mica_commons_iterate_field($context_population_detail->selectionCriteria->countriesIso,
                        'countries_country_lookup', 'iso3', 'name'); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->selectionCriteria->ethnicOrigin)): ?>
            <div class="field-item even">
                <div class="inner-label">
                    <?php print t('Ethnic origin') ?> :
                </div>
                <div class="inner-value">
                    <?php $ehtnic_origins = mica_commons_get_localized_dtos_field($context_population_detail->selectionCriteria, 'ethnicOrigin'); ?>
                    <?php mica_commons_iterate_field($ehtnic_origins); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->selectionCriteria->healthStatus)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Health status') ?> :
                </div>
                <div class="inner-value">
                    <?php $health_status = mica_commons_get_localized_dtos_field($context_population_detail->selectionCriteria, 'healthStatus'); ?>
                    <?php mica_commons_iterate_field($health_status); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->selectionCriteria->otherCriteria)): ?>
            <div class="field-item even">
                <div class="inner-label">
                    <?php print t('Other') ?> :
                </div>
                <div class="inner-value">
                    <?php print mica_commons_get_localized_field($context_population_detail->selectionCriteria, 'otherCriteria'); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->selectionCriteria->info)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Supplementary information') ?> :
                </div>
                <div class="inner-value">
                    <?php print mica_commons_get_localized_field($context_population_detail->selectionCriteria, 'info'); ?>
                </div>
            </div>
        <?php endif; ?>

    </div>
</div>

<div class="field field-name-field-pop-select-criteria field-type-list-text field-label-above">
    <div class="field-label">
        <?php print t('Sources of recruitment') ?> :
    </div>
    <div class="field-items">

        <?php if (!empty($context_population_detail->recruitment->generalPopulationSources)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('General population') ?> :
                </div>
                <div class="inner-value">
                    <?php mica_commons_iterate_field($context_population_detail->recruitment->generalPopulationSources); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->recruitment->studies)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Participants from existing studies') ?> :
                </div>
                <div class="inner-value">
                    <?php
                    $studies = mica_commons_get_localized_dtos_field($context_population_detail->recruitment, 'studies');
                    ?>
                    <?php mica_commons_iterate_field($studies); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->recruitment->specificPopulationSources)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Specific population') ?> :
                </div>
                <div class="inner-value">
                    <?php mica_commons_iterate_field($context_population_detail->recruitment->specificPopulationSources); ?>

                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->recruitment->otherSpecificPopulationSource)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Other specific population') ?> :
                </div>
                <div class="inner-value">
                    <?php print mica_commons_get_localized_field($context_population_detail->recruitment, 'otherSpecificPopulationSource'); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->recruitment->otherSource)): ?>
            <div class="field-item odd">
                <div class="inner-label">
                    <?php print t('Supplementary information') ?> :
                </div>
                <div class="inner-value">
                    <?php print mica_commons_get_localized_field($context_population_detail->recruitment, 'otherSource'); ?>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->recruitment->info)): ?>
            <div class="field-item odd ">
                <div class="inner-label">
                    <?php print t('Supplementary information') ?> :
                </div>
                <div class="inner-value">
                    <p> <?php print mica_commons_get_localized_field($context_population_detail->recruitment, 'info'); ?></p>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->numberOfParticipants->participant->number)): ?>
            <div class="field field-label-inline clearfix">
                <div class="field-label">
                    <?php print t('Number of participants') ?> :
                </div>
                <div class="field-items">
                    <div class="field-item even">
                        <?php print $context_population_detail->numberOfParticipants->participant->number . ' ' . t('participants') ?>
                    </div>
                    <div class="field-item odd">
                        <?php print mica_commons_get_if_no_limite($context_population_detail->numberOfParticipants->participant->noLimit) ?>
                    </div>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->numberOfParticipants->sample->number)): ?>
            <div class="field field-label-inline clearfix">
                <div class="field-label">
                    <?php print t('Number of participants with biological samples') ?> :
                </div>
                <div class="field-items">
                    <div class="field-item even">
                        <?php print $context_population_detail->numberOfParticipants->sample->number . ' ' . t('participants') ?>
                    </div>
                    <div class="field-item odd">
                        <?php print mica_commons_get_if_no_limite($context_population_detail->numberOfParticipants->sample->noLimit) ?>
                    </div>
                </div>
            </div>
        <?php endif; ?>

        <?php if (!empty($context_population_detail->numberOfParticipants->info)): ?>
            <div class="field-item odd ">
                <div class="inner-label">
                    <?php print t('Supplementary information') ?> :
                </div>
                <div class="inner-value">
                    <p> <?php print mica_commons_get_localized_field($context_population_detail->numberOfParticipants, 'info'); ?></p>
                </div>
            </div>
        <?php endif; ?>
    </div>
</div>

<?php if (!empty($context_population_detail->info)): ?>
    <div class="field-item odd ">
        <div class="inner-label">
            <?php print t('Supplementary information') ?> :
        </div>
        <div class="inner-value">
            <p> <?php print mica_commons_get_localized_field($context_population_detail, 'info'); ?></p>
        </div>
    </div>
<?php endif; ?>
<h2>----- fake DCE -----</h2>
<table class="sticky-header" style="position: fixed; top: 65px; left: 267.5px; visibility: hidden;">
    <thead style="">
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Start</th>
        <th>End</th>
    </tr>
    </thead>
</table>
<table class="pop-dce table table-striped sticky-enabled tableheader-processed sticky-table">
    <caption>Data Collection Events:</caption>
    <thead>
    <tr>
        <th>Name</th>
        <th>Description</th>
        <th>Start</th>
        <th>End</th>
    </tr>
    </thead>
    <tbody>
    <tr class="node-unpublished odd">
        <td><a href="http://localhost/mica-dev/?q=content/tilda-wave-1">TILDA Wave 1</a></td>
        <td><p>Computer Assisted Personal Interview, Self-completed questionnaire, and Health Assessment&nbsp;</p></td>
        <td>2009 (October)</td>
        <td>2011 (February)</td>
    </tr>
    <tr class="node-unpublished even">
        <td><a href="http://localhost/mica-dev/?q=content/tilda-wave-2">TILDA Wave 2</a></td>
        <td><p>Computer Assisted Personal Interview and&nbsp;Self-completed questionnaire</p></td>
        <td>2012 (April)</td>
        <td>2013 (January)</td>
    </tr>
    <tr class="node-unpublished odd">
        <td><a href="http://localhost/mica-dev/?q=content/tilda-wave-3">TILDA Wave 3</a></td>
        <td><p>Computer Assisted Personal Interview, Self-completed questionnaire, and Health Assessment&nbsp;</p></td>
        <td>2014 (January)</td>
        <td>2014 (December)</td>
    </tr>
    <tr class="node-unpublished even">
        <td><a href="http://localhost/mica-dev/?q=content/tilda-wave-4">TILDA Wave 4</a></td>
        <td><p>Computer Assisted Personal Interview and&nbsp;Self-completed questionnaire.</p></td>
        <td>2016 (January)</td>
        <td>2016 (December)</td>
    </tr>
    </tbody>
</table>