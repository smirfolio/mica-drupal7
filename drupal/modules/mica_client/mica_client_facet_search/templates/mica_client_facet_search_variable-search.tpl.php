<?php //dvm('search var',$studies);
?>
<div id="search-query"></div>

<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
    <li><a href="#networks" role="tab"> <?php print t('Networks') ?>
        (<?php print !empty($network_totalHits) ? $network_totalHits : 0; ?>)
      </a>
    </li>

    <li><a href="#studies" role="tab"> <?php print t('Studies') ?>
        (<?php print !empty($study_totalHits) ? $study_totalHits : 0; ?>)
      </a>
    </li>

    <li><a href="#datasets" role="tab"> <?php print t('Datasets') ?>
        (<?php print !empty($dataset_totalHits) ? $dataset_totalHits : 0; ?>)
      </a>
    </li>

    <li class="active"><a href="#variables" role="tab"><?php print t('Variables') ?>
        (<?php print !empty($variable_totalHits) ? $variable_totalHits : 0; ?>)
      </a>
    </li>

  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variables">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Variables') ?></h3>
          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($variable_search_form) ?>
            <p>
              <?php print l(t('Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => empty($query) ? array() : array('query' => $query),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $variables_result['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="datasets">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Datasets') ?></h3>
          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($dataset_search_form) ?>
            <p>
              <?php print l(t('Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query
                ),
              )); ?>
            </p>
          </div>

          <div class="clearfix"/>
          <?php print $datasets['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="studies">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Studies') ?></h3>
          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($study_search_form) ?>
            <p>
              <?php print l(t('Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query
                ),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $studies['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="networks">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Networks') ?></h3>
          <div class="pull-right lg-top-margin facet-search-form">
            <?php print render($network_search_form) ?>
            <p>
              <?php print l(t('Coverage'), 'mica/coverage', array(
                'attributes' => array(
                  'class' => array(
                    'btn',
                    'btn-primary',
                    'indent'
                  )
                ),
                'query' => array(
                  'query' => $query
                ),
              )); ?>
            </p>
          </div>
          <div class="clearfix"/>
          <?php print $networks['data']; ?>
        </section>
      </article>
    </div>

  </div>
</div>