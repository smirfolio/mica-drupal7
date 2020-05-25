<?php ?>

<div>
  <h1>
    <span class="label label-info"><?php print $metrics['Network']->title ?>
      <span class="badge"><?php print $metrics['Network']->publishedFormatted ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-warning"><?php print $metrics['Study']->title ?>
      <span class="badge"><?php print $metrics['Study']->publishedFormatted ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-success"><?php print $metrics['HarmonizationStudy']->title ?>
      <span class="badge"><?php print $metrics['HarmonizationStudy']->publishedFormatted ?></span>
    </span>
  </h1>
  <h1>
    <span class="label label-default"><?php print $metrics['DatasetVariable']->title ?>
      <span class="badge"><?php print $metrics['DatasetVariable']->publishedFormatted ?></span>
    </span>
  </h1>
</div>
