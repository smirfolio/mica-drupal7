<?php //dpm($list_studies->studySummaries); ?>
<?php print render($node_page) ?>
<div class="clearfix"></div>

<div class="row">
  <div class="col-md-7 ">
    <div class="search-box-items">
      <div class="row">
        <div class="col-md-2">
          <div class="count-item-center">
            <?php print $list_studies->total . ' ' . t('Studies'); ?>
          </div>
        </div>
        <?php print render($form_search); ?>
      </div>
    </div>
  </div>
  <div class="col-md-5 ">
    <div class="advanced-search-link-center">
      <?php print t('Open IN'); ?> : <a href="search?type=studies"><?php print t('Advanced search'); ?></a>
      <!-- | <a href=""><?php print t('Domain Coverage'); ?> </a> -->
    </div>
  </div>
</div>

<div class="clearfix"></div>
<?php //dpm($list_studies); ?>

<div class="list-page">
  <?php if (!empty($list_studies->studySummaries)): ?>
    <?php foreach ($list_studies->studySummaries as $study) : ?>
    <div class="row">
      <div class="col-md-1 col-xs-1">
        <h1 class="big-caracter">
           <span class="t_badge color_S">
           <?php print drupal_substr(mica_client_commons_get_localized_field($study, 'name'), 0, 1); ?>
           </span>
        </h1>
        <!--           <img class="img-responsive"-->
        <!--              src="http://localhost:8082/ws/draft/study/adoquest/file/54188036c4aa7c77915a67fe/_download">-->
        <!--  src="http://localhost:8082/ws/draft/study/adoquest/file/<?php print $study->id ?>/_download">-->
      </div>
      <div class="col-md-11 col-xs-10">
        <h4><a
            href="study/<?php print $study->id ?>"><?php print mica_client_commons_get_localized_field($study, 'acronym'); ?>
            -
            <?php print  mica_client_commons_get_localized_field($study, 'name'); ?> </a></h4>

        <p>
          <?php print  mica_client_commons_get_localized_field($study, 'name'); ?>
          This page displays the list of the consortium's studies. Each study is described in a
          ... <a href="study/<?php print $study->id ?>">Learn more</a>
        </p>

      </div>
    </div>

    <?php endforeach; ?>
    <div><?php print $pager_wrap; ?></div>
  <?php else: print t('No Studies Found'); ?>
  <?php endif; ?>
</div>

