<?php //dvm('search var',$studies);
?>
<div class="alert alert-info">
  <div id="search-help">
    <i class="glyphicon glyphicon-arrow-left"></i>
    <span class="indent">
      <?php print t('Start searching by selecting a facet'); ?>
    </span>
  </div>
  <div id="search-query"></div>
  <div id="query-help" style="display:none;" class="md-top-margin help-inline">
    <i class="glyphicon glyphicon-question-sign"></i>
    <span class="indent">
      <?php print t('Tips: click on a criteria to remove it, click on AND/OR to switch it.'); ?>
    </span>
  </div>
</div>

<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">

    <?php if (!empty($search_param['search_networks'])): ?>
      <li><a href="#networks" role="tab"> <?php print t('Networks') ?>
          (<?php print !empty($network_total_hits) ? $network_total_hits : 0; ?>)
        </a>
      </li>
    <?php endif; ?>

    <?php if (!empty($search_param['search_studies'])): ?>
      <li><a href="#studies" role="tab"> <?php print t('Studies') ?>
          (<?php print !empty($study_total_hits) ? $study_total_hits : 0; ?>)
        </a>
      </li>
    <?php endif; ?>

    <?php if (!empty($search_param['search_datasets'])): ?>
      <li><a href="#datasets" role="tab"> <?php print t('Datasets') ?>
          (<?php print !empty($dataset_total_hits) ? $dataset_total_hits : 0; ?>)
        </a>
      </li>
    <?php endif; ?>

    <?php if (!empty($search_param['search_variables'])): ?>
      <li class="active"><a href="#variables" role="tab"><?php print t('Variables') ?>
          (<?php print !empty($variable_total_hits) ? $variable_total_hits : 0; ?>)
        </a>
      </li>
    <?php endif; ?>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">

    <?php if (!empty($search_param['search_variables'])): ?>
      <div class="tab-pane active" id="variables">
        <article>
          <section>
            <h2 class="pull-left"><?php print t('Variables') ?></h2>

            <div class="pull-right lg-top-margin facet-search-form">
              <?php print render($variable_search_form) ?>
              <p>
                <?php
                if (variable_get_value('mica_statistics_coverage')) {
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::COVERAGE,
                    t(variable_get_value('variable_coverage_label')),
                    array('class' => 'btn btn-primary indent'),
                    array('query' => $query, 'group-by' => 'studyIds')
                  );
                }
                ?>
              </p>
            </div>
            <div class="clearfix"/>
            <?php print $variables_result['data']; ?>
          </section>
        </article>
      </div>
    <?php endif; ?>

    <?php if (!empty($search_param['search_datasets'])): ?>
      <div class="tab-pane" id="datasets">
        <article>
          <section>
            <h2 class="pull-left"><?php print t('Datasets') ?></h2>

            <div class="pull-right lg-top-margin facet-search-form">
              <?php print render($dataset_search_form) ?>
              <p>
                <?php
                if (variable_get_value('mica_statistics_coverage')) {
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::COVERAGE,
                    t(variable_get_value('variable_coverage_label')),
                    array('class' => 'btn btn-primary indent'),
                    array('query' => $query, 'group-by' => 'datasetId')
                  );
                }
                ?>
              </p>
            </div>

            <div class="clearfix"/>
            <?php print $datasets['data']; ?>
          </section>
        </article>
      </div>
    <?php endif; ?>

    <?php if (!empty($search_param['search_studies'])): ?>
      <div class="tab-pane" id="studies">
        <article>
          <section>
            <h2 class="pull-left"><?php print t('Studies') ?></h2>

            <div class="pull-right lg-top-margin facet-search-form">
              <?php print render($study_search_form) ?>
              <p>
                <?php
                if (variable_get_value('mica_statistics_coverage')) {
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::COVERAGE,
                    t(variable_get_value('variable_coverage_label')),
                    array('class' => 'btn btn-primary indent'),
                    array('query' => $query, 'group-by' => 'studyIds')
                  );
                }
                ?>
              </p>
            </div>
            <div class="clearfix"/>
            <?php print $studies['data']; ?>
          </section>
        </article>
      </div>
    <?php endif; ?>

    <?php if (!empty($search_param['search_networks'])): ?>
      <div class="tab-pane" id="networks">
        <article>
          <section>
            <h2 class="pull-left"><?php print t('Networks') ?></h2>

            <div class="pull-right lg-top-margin facet-search-form">
              <?php print render($network_search_form) ?>
              <p>
                <?php
                if (variable_get_value('mica_statistics_coverage')) {
                  print MicaClientAnchorHelper::ajax_friendly_anchor(
                    MicaClientPathProvider::COVERAGE,
                    t(variable_get_value('variable_coverage_label')),
                    array('class' => 'btn btn-primary indent'),
                    array('query' => $query, 'group-by' => 'studyIds')
                  );
                }
                ?>
              </p>
            </div>
            <div class="clearfix"/>
            <?php print $networks['data']; ?>
          </section>
        </article>
      </div>
    <?php endif; ?>

  </div>

</div>