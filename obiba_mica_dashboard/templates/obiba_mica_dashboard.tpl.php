<?php ?>

<div>
  <h1>
    <span class="label label-info"><?php print $metrics['Network']->title ?>
      <span class="badge"><?php print $metrics['Network']->published ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-warning"><?php print $metrics[DrupalMicaDatasetResource::COLLECTED_VARIABLE]->title ?>
      <span class="badge"><?php print $metrics[DrupalMicaDatasetResource::COLLECTED_VARIABLE]->published ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-success"><?php print $metrics['StudyWithVariable']->title ?>
      <span class="badge"><?php print $metrics['StudyWithVariable']->published ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-default"><?php print $metrics['DatasetVariable']->title ?>
      <span class="badge"><?php print $metrics['DatasetVariable']->published ?></span>
    </span>
  </h1>
</div>
