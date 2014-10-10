<?php //dvm('search var',$studies);
//dpm($variables_result);
?>
<div id="search-query"></div>

<div id="search-result">
  <ul class="nav nav-tabs" role="tablist" id="result-search">
    <li class="active"><a href="#variables" role="tab"><?php print t('Variables') ?>
        <small>
          <?php if (!empty($variable_totalHits)) : ?>
            - <?php print $variable_totalHits; ?>
          <?php else : ?>
            - <?php print 0; ?>
          <?php endif; ?>
        </small>
      </a></li>

    <li><a href="#datasets" role="tab"> <?php print t('Datasets') ?>
        <small>
          <?php if (!empty($dataset_totalHits)) : ?>
            - <?php print $dataset_totalHits; ?>
          <?php else : ?>
            - <?php print 0; ?>
          <?php endif; ?>
        </small>
      </a></li>

    <li><a href="#studies" role="tab"> <?php print t('Studies') ?>
        <small>
          <?php if (!empty($study_totalHits)) : ?>
            - <?php print $study_totalHits; ?>
          <?php else : ?>
            - <?php print 0; ?>
          <?php endif; ?>
        </small>
      </a></li>

    <li><a href="#networks" role="tab"> <?php print t('Networks') ?>
        <small>
          <?php if (!empty($network_totalHits)) : ?>
            - <?php print $network_totalHits; ?>
          <?php else : ?>
            - <?php print 0; ?>
          <?php endif; ?>
        </small>
      </a></li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content search-result">
    <div class="tab-pane active" id="variables">
      <article>
        <section>
          <?php print $variable_charts; ?>
        </section>
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
        <section>
          <?php print $study_charts; ?>
        </section>
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