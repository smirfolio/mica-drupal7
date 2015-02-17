<div id="population-<?php print $population->id?>" class="modal fade" xmlns="http://www.w3.org/1999/html">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h3 class="modal-title"><?php print obiba_mica_commons_get_localized_field($population, 'name'); ?></h3>
      </div>
      <div class="modal-body">
        <section>
          <?php print render($population_content) ?>
        </section>
      </div>
    </div>
  </div>
</div>