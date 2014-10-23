<?php //dvm('search var',$studies);
//dpm($variables_result);
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
        <?php if (!empty($variable_charts)): ?>
          <section>
            <?php print $variable_charts; ?>
          </section>
        <?php endif ?>
        <section>
          <h3 class="pull-left"><?php print t('Variables') ?></h3>

          <p class="pull-right">
            <?php print l(t('Coverage'), 'mica/coverage', array(
              'attributes' => array(
                'class' => array(
                  'btn',
                  'btn-primary',
                  'lg-top-margin'
                )
              ),
              'query' => array(
                'query' => $query
              ),
            )); ?>
          </p>

          <div class="clearfix"/>
          <?php print $variables_result['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="datasets">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Datasets') ?></h3>

          <p class="pull-right">
            <?php print l(t('Coverage'), 'mica/coverage', array(
              'attributes' => array(
                'class' => array(
                  'btn',
                  'btn-primary',
                  'lg-top-margin'
                )
              ),
              'query' => array(
                'query' => $query
              ),
            )); ?>
          </p>

          <div class="clearfix"/>
          <?php print $datasets['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="studies">
      <article>
        <?php if (!empty($study_charts)): ?>
          <section>
            <?php print $study_charts; ?>
          </section>
        <?php endif ?>
        <section>
          <h3 class="pull-left"><?php print t('Studies') ?></h3>

          <p class="pull-right">
            <?php print l(t('Coverage'), 'mica/coverage', array(
              'attributes' => array(
                'class' => array(
                  'btn',
                  'btn-primary',
                  'lg-top-margin'
                )
              ),
              'query' => array(
                'query' => $query
              ),
            )); ?>
          </p>

          <div class="clearfix"/>
          <?php print $studies['data']; ?>
        </section>
      </article>
    </div>

    <div class="tab-pane" id="networks">
      <article>
        <section>
          <h3 class="pull-left"><?php print t('Networks') ?></h3>

          <p class="pull-right">
            <?php print l(t('Coverage'), 'mica/coverage', array(
              'attributes' => array(
                'class' => array(
                  'btn',
                  'btn-primary',
                  'lg-top-margin'
                )
              ),
              'query' => array(
                'query' => $query
              ),
            )); ?>
          </p>

          <div class="clearfix"/>
          <?php print $networks['data']; ?>
        </section>
      </article>
    </div>

  </div>
</div>