<?php
/**
 * Copyright (c) 2017 OBiBa. All rights reserved.
 *
 * This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
?>
<?php if (!empty($populations)): ?>
  <?php foreach ($populations as $key => $population): ?>
    <?php if (!empty($population['data']) && !empty($population['data']['dce-modal'])): ?>
      <div><?php print $population['data']['dce-modal']; ?></div>
    <?php endif; ?>
  <?php endforeach ?>
<?php endif; ?>
<div>
  <div class="row md-bottom-margin">
    <?php if (!empty($study_dto->logo->id)): ?>
      <div class="col-xs-12 col-md-6">
        <?php if (!empty($logo_study)): ?>
          <?php print render($logo_study); ?>
        <?php endif; ?>
      </div>
    <?php endif; ?>
    <div class="md-top-margin col-xs-12">
      <?php print obiba_mica_commons_markdown(obiba_mica_commons_get_localized_field($study_dto, 'objectives')); ?>
    </div>

  </div>

  <div class="pull-right md-bottom-margin">
    <?php if ($can_edit_draf_document): ?>
      <a title="<?php print $localize->getTranslation('edit') ?>"
         target="_blank"
         href="<?php print MicaClientPathProvider::study_draft_url($study_dto->id) ?>"
         class="btn btn-default">
        <i class="fa fa-pencil-square-o"></i> <?php print $localize->getTranslation('edit')?></a>
    <?php endif; ?>

    <?php if (variable_get_value('study_detail_show_search_button') && $draft_view === FALSE): ?>
        <?php print MicaClientAnchorHelper::studyVariables(NULL, $study_dto->id, TRUE) ?>
    <?php endif; ?>
  </div>
</div>

<div class="clearfix"></div>

<article class="bordered-article">

  <section>
    <div class="row">
      <div class="col-lg-6 col-xs-12 ">
        <!-- GENERAL INFORMATION -->
        <h2 id="overview"><?php print $localize->getTranslation('client.label.overview') ?></h2>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($study_dto->acronym)): ?>
            <tr>
              <th><?php print $localize->getTranslation('study.acronym') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($study_dto, 'acronym'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->website)): ?>
            <tr>
              <th><?php print $localize->getTranslation('website') ?></th>
              <td>
                <p><?php
                  print l(obiba_mica_commons_get_localized_field($study_dto, 'acronym') . ' ' . $localize->getTranslation('website'),
                    $study_dto->model->website,
                    array('attributes' => array('target' => '_blank')));
                  ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($ordered_membership)): ?>
            <?php print theme('obiba_mica_study-detail-members', array(
                    'ordered_membership' => $ordered_membership,
                    'study_dto' => $study_dto)); ?>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->startYear)): ?>
            <tr>
              <th><?php print $localize->getTranslation('study.start-year') ?></th>
              <td><p><?php print $study_dto->model->startYear; ?></p></td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->endYear)): ?>
            <tr>
              <th><?php print $localize->getTranslation('study.end-year') ?></th>
              <td><p><?php print $study_dto->model->endYear; ?></p></td>
            </tr>
          <?php endif; ?>
          <?php if (!empty($study_dto->model->funding)): ?>
            <tr>
              <th><?php print $localize->getTranslation('funding') ?></th>
              <td><p><?php print obiba_mica_commons_get_localized_field($study_dto->model, 'funding'); ?></p></td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>

      </div>
      <div class="col-lg-6  col-xs-12">
        <!-- GENERAL DESIGN -->
        <h2 id="design"><?php print $localize->getTranslation('study.design') ?></h2>

        <table class="table table-striped">
          <tbody>

          <?php if (!empty($study_dto->model->methods->design)): ?>
            <tr>
              <th><?php print $localize->getTranslation('search.study.design') ?></th>
              <td>
                <?php print $localize->getTranslation("study_taxonomy.vocabulary.methods-design.term." . $study_dto->model->methods->design . ".title"); ?>
                  <?php if (!empty($study_dto->model->methods->otherDesign)): ?>
                    : <?php print obiba_mica_commons_get_localized_field($study_dto->model->methods->otherDesign); ?>
                  <?php endif; ?>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->methods->followUpInfo)): ?>
            <tr>
              <th><?php print $localize->getTranslation('study.follow-up-help') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($study_dto->model->methods, 'followUpInfo'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->methods->recruitments)): ?>
            <tr>
              <th><?php print $localize->getTranslation('study.recruitment-target') ?></th>
              <td>
                <ul class="list-unstyled">
                  <?php foreach ($study_dto->model->methods->recruitments as $recruitment): ?>
                    <li>
                      <?php print $localize->getTranslation('study_taxonomy.vocabulary.methods-recruitments.term.' . $recruitment . '.title') ; ?>
                      <?php if (stristr($recruitment, 'other') && !empty($study_dto->model->methods->otherRecruitment)): ?>
                         : <?php print obiba_mica_commons_get_localized_field($study_dto->model->methods, 'otherRecruitment'); ?>
                      <?php endif; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              </td>
            </tr>
          <?php endif; ?>
          <?php if (!empty($study_dto->model->numberOfParticipants->participant->number) || !empty($study_dto->model->numberOfParticipants->participant->noLimit)): ?>
            <tr>
              <th><?php print $localize->getTranslation('numberOfParticipants.participants') ?></th>
              <td>
                <p>
                  <?php if (!empty($study_dto->model->numberOfParticipants->participant->number)) {
                    print obiba_mica_commons_format_number($study_dto->model->numberOfParticipants->participant->number);
                  } ?>
                  <?php if (!empty($study_dto->model->numberOfParticipants->participant->noLimit)): ?>
                    (<?php print $localize->getTranslation('numberOfParticipants.no-limit'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->numberOfParticipants->sample->number) || !empty($study_dto->model->numberOfParticipants->sample->noLimit)): ?>
            <tr>
              <th><?php print $localize->getTranslation('numberOfParticipants.sample') ?></th>
              <td>
                <p>
                  <?php if (!empty($study_dto->model->numberOfParticipants->sample->number)) {
                    print obiba_mica_commons_format_number($study_dto->model->numberOfParticipants->sample->number);
                  } ?>
                  <?php if (!empty($study_dto->model->numberOfParticipants->sample->noLimit)): ?>
                    (<?php print $localize->getTranslation('numberOfParticipants.no-limit'); ?>)
                  <?php endif; ?>
                </p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty(obiba_mica_commons_get_localized_field($study_dto->model->numberOfParticipants, 'info'))): ?>
            <tr>
              <th><?php print $localize->getTranslation('numberOfParticipants.suppl-info') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($study_dto->model->numberOfParticipants, 'info'); ?></p>
              </td>
            </tr>
          <?php endif; ?>

          <?php if (!empty($study_dto->model->methods->info)): ?>
            <tr>
              <th><?php print $localize->getTranslation('suppl-info') ?></th>
              <td>
                <p><?php print obiba_mica_commons_get_localized_field($study_dto->model->methods, 'info'); ?></p>
              </td>
            </tr>
          <?php endif; ?>
          </tbody>
        </table>

      </div>
    </div>

  </section>

  <section>

    <div class="row">
      <div class="col-lg-6 col-xs-12">
        <!-- ACCESS -->
        <h2 id="access"><?php print $localize->getTranslation('study.access.label') ?></h2>

        <?php if (!empty($study_dto->model->access) && (in_array('data', $study_dto->model->access) ||
            in_array('bio_samples', $study_dto->model->access) ||
            in_array('other', $study_dto->model->access))
        ): ?>

          <p><?php print $localize->getTranslation('study.access.for'); ?></p>
        <?php else : ?>
          <p><?php print $localize->getTranslation('study.access.none'); ?></p>
        <?php endif; ?>
        <div class="table-responsive">
          <table class="table table-striped valign-table-column">
            <tbody>
            <tr>
              <th><?php print $localize->getTranslation('study.access.data'); ?></th>
              <td>
                <p>
                  <?php if (!empty($study_dto->model->access) && in_array('data', $study_dto->model->access)): ?>
                    <span class="glyphicon glyphicon-ok"></span>
                  <?php else : ?>
                    <span class="glyphicon glyphicon-remove"></span>
                  <?php endif; ?>
                </p>
              </td>
            </tr>

            <tr>
              <th><?php print $localize->getTranslation('study.access.biosamples'); ?></th>
              <td>
                <p>
                  <?php if (!empty($study_dto->model->access) && in_array('bio_samples', $study_dto->model->access)): ?>
                    <span class="glyphicon glyphicon-ok"></span>
                  <?php else : ?>
                    <span class="glyphicon glyphicon-remove"></span>
                  <?php endif; ?>
                </p>
              </td>
            </tr>

            <?php if (!empty($study_dto->model->access) && !empty($study_dto->model->otherAccess)): ?>
              <tr>
                <th><?php print $localize->getTranslation('study.access.other'); ?></th>
                <td>
                  <?php if (!empty($study_dto->model->otherAccess)): ?>
                     <?php print obiba_mica_commons_get_localized_field($study_dto->model, 'otherAccess'); ?>
                  <?php endif; ?>
                </td>
              </tr>
            <?php endif; ?>
            </tbody>
          </table>
        </div>
      </div>
      <div class="col-lg-6 col-xs-12">
        <!-- MARKER PAPER -->
        <?php if (!empty($study_dto->model->markerPaper) || !empty($study_dto->model->pubmedId)): ?>
          <h2 id="marker"><?php print $localize->getTranslation('study.marker-paper') ?></h2>
          <?php if (!empty($study_dto->model->markerPaper)): ?>
            <p><?php print filter_xss($study_dto->model->markerPaper, obiba_mica_commons_allowed_filter_xss_tags()); ?></p>
          <?php endif; ?>
          <?php if (!empty($study_dto->model->pubmedId)): ?>
            <p>
              <a
                href="http://www.ncbi.nlm.nih.gov/pubmed/<?php print $study_dto->model->pubmedId; ?>"
                target="_blank">
                PUBMED <?php print filter_xss($study_dto->model->pubmedId, obiba_mica_commons_allowed_filter_xss_tags()); ?>
              </a>
            </p>
          <?php endif; ?>
        <?php endif; ?>
      </div>
    </div>

  </section>

  <!-- SUPPLEMENTARY INFORMATION -->
  <?php if (!empty($study_dto->model->info)): ?>
    <section>
      <h2 id="info"><?php print $localize->getTranslation('suppl-info'); ?></h2>

      <p><?php print obiba_mica_commons_get_localized_field($study_dto->model, 'info'); ?></p>
    </section>
  <?php endif; ?>

  <!-- DOCUMENTS -->

  <!-- TODO find a way not to show browser if there are no files -->
  <?php if (!empty($file_browser)): ?>
    <section>
      <h2><?php print variable_get_value('files_documents_label'); ?></h2>
      <?php print $file_browser ; ?>
    </section>
  <?php endif; ?>

  <!-- TIMELINE -->
  <?php if (!empty($timeline)): ?>
    <section>
      <h2 id="timeline"><?php print $localize->getTranslation('study.timeline'); ?></h2>

      <p class="help-block">
        <?php print t('Each colour in the timeline graph below represents a separate Study Population, while each segment in the graph represents a separate Data Collection Event. Clicking on a segment gives more detailed information on a Data Collection Event.') ?>
      </p>

      <div class="scroll-content-tab">
        <?php print $timeline; ?>
      </div>
    </section>
  <?php endif; ?>

  <!-- POPULATIONS -->
  <?php if (!empty($populations)): ?>
    <section>
      <h2 id="populations"><?php if (count($populations) > 1) {
          print $localize->getTranslation('study.populations');
        }
        else print '<span id="population-' . $key . '">' . $localize->getTranslation('study.population') . '</span>' ?></h2>
      <?php if (count($populations) == 1): ?>
        <?php print array_pop($populations)['html']; ?>
      <?php else: ?>

        <div class="row tabbable tabs-left">
          <div class="col-lg-2 col-xs-12  ">
            <ul class="nav nav-pills nav-stacked" id="tab-pane">
              <?php foreach ($populations as $key => $population): ?>
                <li test-ref="population-tab" <?php if ($key == array_keys($populations)[0]) {
                  print 'class="active"';
                } ?>>
                  <a href="#population-<?php print $key; ?>" data-toggle="pill">
                    <?php print obiba_mica_commons_get_localized_field($population['data']['data'], 'name'); ?>
                  </a>
                </li>

              <?php endforeach ?>
            </ul>
          </div>
          <div class="col-lg-10 col-xs-12  ">
            <div class="tab-content indent" test-ref="population-tab-content">
              <?php foreach ($populations as $key => $population): ?>
                <?php $active_population_tab = $key == array_keys($populations)[0]; ?>
                <div
                  class="tab-pane  <?= $active_population_tab ? 'active' : '' ?>"
                  id="population-<?= $key ?>"
                  <?= $population['html']; ?>
                </div>
              <?php endforeach ?>
            </div>
          </div>
        </div>

      <?php endif ?>
    </section>
  <?php endif; ?>

  <!-- NETWORKS placeholder -->
  <section id="networks">
    <div><?php print $localize->getTranslation('loading') ?></div>
  </section>

  <!-- DATASETS placeholder -->
  <section id="datasets">
    <div><?php print $localize->getTranslation('loading') ?></div>
  </section>

  <!-- COVERAGE placeholder -->
  <div ng-controller="VariableCoverageChartController">
    <section id="coverage" ng-if="d3Configs && d3Configs.length">
      <h2><?php print $localize->getTranslation('variable-classifications') ?></h2>

      <div ng-repeat="d3Config in d3Configs">
        <obiba-nv-chart chart-config="d3Config"></obiba-nv-chart>
      </div>
    </section>
  </div>
  

  <div><?php !empty($investigators_modal) ? print $investigators_modal : ''; ?></div>
  <div><?php !empty($contacts_modal) ? print $contacts_modal : ''; ?></div>
  <div><?php !empty($members_modal) ? print $members_modal : ''; ?></div>
</article>
<div class="back-to-top t_badge"><i class="glyphicon glyphicon-arrow-up"></i>
</div>
