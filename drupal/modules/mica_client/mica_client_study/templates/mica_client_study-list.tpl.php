<?php dpm($list_studies); ?>



<div class="list-page">

  <?php foreach ($list_studies['data'] as $study) : ?>


    <div class="study-item">
      <div class="col-xs-2 col-md-2">
        <h1 class="big-caracter">
           <span class="t_badge color_S">
           <?php print drupal_substr(mica_client_commons_get_localized_field($study, 'name'), 0, 1); ?>
           </span>
        </h1>
        <!--        <img class="img-responsive"-->
        <!--             src="http://localhost:8082/ws/draft/study/adoquest/file/54173315c4aac4d2f380d516/_download">-->
      </div>
      <div class="col-xs-10 col-md-10">
        <h4><a
            href="study/<?php print $study->id ?> "><?php print mica_client_commons_get_localized_field($study, 'acronym'); ?>
            -
            <?php print  mica_client_commons_get_localized_field($study, 'name'); ?> </a></h4>

        <p>
          <?php print  mica_client_commons_get_localized_field($study, 'name'); ?>
          This page displays the list of the consortium's studies. Each study is described in a
          Learn more ..
        </p>

        <p>
          Member of the <a>BioShare</a>, <a>NODN</a> , and <a>CPTP</a> study networks
        </p>

        <p>
          Includes [8000 variables] from [5 study] and [2 harmonized] datasets
        </p>
      </div>
    </div>

  <?php endforeach; ?>
</div>