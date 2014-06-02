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
                    <?php  print !empty($context_detail['data']->objectives) ?
                        mica_commons_get_localized_field($context_detail['data'], 'objectives') : ''; ?>
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
        <div class="field field-name-field-acroym field-type-text field-label-inline clearfix">
            <div class="field-label"><?php print t('Acronym') ?> :</div>
            <div class="field-items">
                <div class="field-item even">
                    <?php print !empty($context_detail['data']->acronym) ? mica_commons_get_localized_field($context_detail['data'], 'acronym') : ''; ?>
                </div>
            </div>
        </div>
        <div class="field field-name-field-website field-type-link-field field-label-inline clearfix">
            <div class="field-label"><?php print t('Website') ?> :</div>
            <div class="field-items">
                <div class="field-item even"><a href="http://www.adoquest.ca" target="_blank">
                        <?php print !empty($context_detail['data']->website) ? $context_detail['data']->website : ''; ?>
                    </a>
                </div>
            </div>
        </div>
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
        <div class="field field-name-field-study-start-year field-type-number-integer field-label-inline clearfix">
            <div class="field-label"><?php print t('Study Start Year') ?> :</div>
            <div class="field-items">
                <div
                    class="field-item even"><?php print !empty($context_detail['data']->startYear) ? $context_detail['data']->startYear : ''; ?></div>
            </div>
        </div>
        <div class="field field-name-field-networks field-type-node-reference field-label-inline clearfix">
            <div class="field-label"><?php print t('Networks') ?> :</div>
            <div class="field-items">
                <div class="field-item even">
                    <a
                        href=""><?php print !empty($context_detail['data']->networks) ? $context_detail['data']->networks : ''; ?></a>
                </div>
            </div>
        </div>
    </div>

</section>
<section>
    <h2><?php print t('General Design') ?></h2>
</section>
