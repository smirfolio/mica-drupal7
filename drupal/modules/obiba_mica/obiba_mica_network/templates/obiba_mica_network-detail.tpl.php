<?php
//dpm($network_dto);
?>

<div>
  <?php if (!empty($network_dto->description)): ?>
    <p class="md-top-margin">
      <?php if (!empty($network_dto->logo->id)): ?>
        <a
          href="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
          class="fancybox-button">
        <img
          src="<?php print obiba_mica_commons_safe_expose_server_url($network_dto->id, $network_dto->logo, 'network') ?>"
          class="imageThumb">
        </a>
      <?php endif; ?>
      <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($network_dto, 'description')); ?>
    </p>
  <?php endif; ?>

  <?php if (!empty($network_dto->studyIds)): ?>
    <div class="pull-right md-bottom-margin">
      <?php
      $query_array = array("networks" => array("terms" => array("networkId" => $network_dto->id)));
      $query = MicaClient::create_query_dto_as_string($query_array);

      print l(t('Search studies'), 'mica/search',
        array(
          'query' => array(
            'type' => 'studies',
            'query' => $query
          ),
          'attributes' => array('class' => 'btn btn-primary')
        ));

      ?>
      <?php print l(t('Search Variables'), 'mica/search',
        array(
          'query' => array(
            'type' => 'variables',
            'query' => $query
          ),
          'attributes' => array('class' => 'btn btn-primary indent')
        ));
      ?>

      <?php
      print l(t('View Coverage'), 'mica/coverage',
        array(
          'query' => array(
            'type' => 'variables',
            'query' => $query
          ),
          'attributes' => array('class' => 'btn btn-primary indent')
        ));
      ?>
    </div>
  <?php endif; ?>
</div>

<div class="clearfix"></div>

<article>

  <section>
    <h2><?php print t('Overview') ?></h2>

    <div class="row">
      <div class="col-lg-6 col-xs-12">

        <table class="table table-striped">
          <tbody>
          <?php if (!empty($network_dto->acronym)): ?>
            <tr>
              <th><?php print t('Acronym') ?></th>
              <td><p><?php print obiba_mica_commons_get_localized_field($network_dto, 'acronym'); ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->website)): ?>
            <tr>
              <th><?php print t('Website') ?></th>
              <td>
                <p><?php
                  print l(obiba_mica_commons_get_localized_field($network_dto, 'acronym') . ' ' . t('website'),
                    $network_dto->website,
                    array('attributes' => array('target' => '_blank')));
                  ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->investigators)): ?>
            <tr>
              <th><?php print t('Investigators') ?></th>
              <td>
                <ul>
                  <?php foreach ($network_dto->investigators as $key_investigator => $investigator) : ?>
                    <li>
                      <a href="#" data-toggle="modal"
                        data-target="#investigator_<?php print $network_dto->id ?>_<?php print $key_investigator ?>">
                        <?php print $investigator->title; ?>
                        <?php print $investigator->firstName; ?>
                        <?php print $investigator->lastName; ?>
                        <?php if (!empty($investigator->academicLevel)) {
                          print ', ' . $investigator->academicLevel;
                        } ?>
                        (<?php print obiba_mica_commons_get_localized_field($investigator->institution, 'name'); ?>)
                      </a>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($network_dto->contacts)): ?>
            <tr>
              <th><?php print t('Contacts') ?></th>
              <td>
                <ul>
                  <?php foreach ($network_dto->contacts as $key_contact => $contact) : ?>
                    <li>
                      <a href="#" data-toggle="modal"
                        data-target="#contact_<?php print $network_dto->id ?>_<?php print $key_contact ?>">
                        <?php print $contact->title; ?>
                        <?php print $contact->firstName; ?>
                        <?php print $contact->lastName; ?>
                        <?php if (!empty($contact->academicLevel)) {
                          print ', ' . $contact->academicLevel;
                        } ?>
                        (<?php print obiba_mica_commons_get_localized_field($contact->institution, 'name'); ?>)
                      </a>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>

          </tbody>
        </table>

      </div>

      <?php if (!empty($network_dto->attributes)): ?>
        <div class="col-lg-6 col-xs-12">
          <h4><?php print t('Attributes') ?></h4>

          <p><?php print obiba_mica_dataset_attributes_tab($network_dto->attributes, 'maelstrom'); ?></p>
        </div>
      <?php endif; ?>
    </div>

  </section>

  <!-- STUDIES -->
  <?php if (!empty($network_dto->studySummaries)): ?>
    <section>
      <h2><?php print t('Studies') ?></h2>

      <div id="studies-table">
        <div class="row">
          <div class="col-lg-12 col-xs-12">
            <table class="table table-striped" id="table-studies"></table>
          </div>
        </div>
      </div>

    </section>
  <?php endif; ?>

  <!-- COVERAGE -->
  <?php if (!empty($coverage)): ?>
    <section>
      <h2 id="coverage"><?php print t('Variable Coverage') ?></h2>

      <?php foreach ($coverage as $taxonomy_coverage): ?>
        <h3><?php print obiba_mica_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'titles'); ?></h3>
        <p class="help-block">
          <?php print obiba_mica_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'descriptions'); ?>
        </p>
        <div class="scroll-content-tab">
          <?php print render($taxonomy_coverage['chart']); ?>
        </div>
      <?php endforeach ?>
    </section>
  <?php endif; ?>


  <div><?php !empty($investigators_modal) ? print $investigators_modal : ''; ?></div>
  <div><?php !empty($contacts_modal) ? print $contacts_modal : ''; ?></div>

</article>