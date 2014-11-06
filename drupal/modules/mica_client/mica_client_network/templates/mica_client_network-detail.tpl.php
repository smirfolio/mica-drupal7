<?php
//dpm($network_dto);
?>

<div>
  <?php if (!empty($network_dto->description)): ?>
  <p><?php print mica_client_commons_get_localized_field($network_dto, 'description'); ?></p>
  <?php endif; ?>
  
  <?php if (!empty($network_dto->studyIds)): ?>
    <div class="pull-right md-bottom-margin">
      <?php
      $query_array = array("variables" => array("terms" => array("studyIds" => $network_dto->studyIds)));
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
  <?php endif; ?>
</div>

<div class="clearfix"></div>

<article>
  <section>
    <h3><?php print t('Overview') ?></h3>

    <div class="container-fluid">
      <div class="row">
        <div class="col-xs-6 right-indent">

          <table class="table table-striped">
            <tbody>
            <?php if (!empty($network_dto->acronym)): ?>
              <tr>
                <td><h5><?php print t('Acronym') ?></h5></td>
                <td><p><?php print mica_client_commons_get_localized_field($network_dto, 'acronym'); ?></p></td>
              </tr>
            <?php endif; ?>

            <?php if (!empty($network_dto->investigators)): ?>
              <tr>
                <td><h5><?php print t('Investigators') ?></h5></td>
                <td>
                  <ul>
                    <?php foreach ($network_dto->investigators as $investigator) : ?>
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

            <?php if (!empty($network_dto->contacts)): ?>
              <tr>
                <td><h5><?php print t('Contacts') ?></h5></td>
                <td>
                  <ul>
                    <?php foreach ($network_dto->contacts as $contact) : ?>
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

            <tr>
              <td></td>
              <td></td>
            </tr>
            </tbody>
          </table>

        </div>
        <div class="col-xs-6">
          <?php if (!empty($network_dto->attributes)): ?>
            <h5><?php print t('Attributes') ?></h5>
            <p><?php print mica_client_dataset_attributes_tab($network_dto->attributes, 'maelstrom'); ?></p>
          <?php endif; ?>
        </div>
      </div>
    </div>
  </section>

  <!-- COVERAGE -->
  <?php if (!empty($coverage)): ?>
    <section>
      <h3><?php print t('Coverage') ?></h3>
      <?php foreach ($coverage as $taxonomy_coverage): ?>
        <h4><?php print mica_client_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'titles'); ?></h4>
        <p class="help-block">
          <?php print mica_client_commons_get_localized_field($taxonomy_coverage['taxonomy'], 'descriptions'); ?>
        </p>
        <?php print render($taxonomy_coverage['chart']); ?>
      <?php endforeach ?>
    </section>
  <?php endif; ?>

  <section>
    <h3><?php print t('Studies') ?></h3>
    <?php print mica_client_network_study_table($network_dto) ?>
  </section>

</article>