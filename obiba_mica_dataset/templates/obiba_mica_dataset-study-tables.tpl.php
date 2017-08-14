<!-- ### Individual study table## -->
<?php if (!empty($dataset_type_dto->studyTables)): ?>
  <h2>
    <?php  print $localize->getTranslation('global.individual-studies');    ?>
  </h2>

    <div id="studies-table">
      <div class="row">
        <div class="col-lg-12 col-xs-12">
          <table class="table table-striped" id="table-studies"></table>
        </div>
      </div>
    </div>

<?php endif ?>
<!-- ### Harmonization study table## -->
<?php if (!empty($dataset_type_dto->harmonizationTables)): ?>
  <h2>
    <?php
    print $localize->getTranslation('global.participant-harmonization-studies');
    ?>
  </h2>
  <div id="studies-table">
    <div class="row">
      <div class="col-lg-12 col-xs-12">
        <table class="table table-striped" id="table-harmonization-studies"></table>
      </div>
    </div>
  </div>
<?php endif; ?>