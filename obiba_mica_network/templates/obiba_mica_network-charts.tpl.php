<?php
$network_name = $network_acronym?$network_acronym:$network_id;
?>
  <!-- Nav tabs -->
  <ul class="nav nav-pills nav-justified" role="tablist">
    <li role="charts" class="active">
      <?php print l('Geographical distribution','',
        array('attributes'=>array(
          'aria-controls' => 'studiesGeoChart',
          'role' => 'tab',
          'data-toggle' => 'tab'
        ),
          'fragment' => 'studiesGeoChart')); ?>
    </li>
    <li role="charts">
      <?php print l('Recruitment Source','',
        array('attributes'=>array(
          'aria-controls' => 'studiesRecruitmentSource',
          'role' => 'tab',
          'data-toggle' => 'tab',
          'class' => 'PiChart'
        ),
          'fragment' => 'studiesRecruitmentSource')); ?>
    </li>
    <li role="charts">
      <?php print l('Study designs','',
        array('attributes'=>array(
          'aria-controls' => 'studiesStudyDesign',
          'role' => 'tab',
          'data-toggle' => 'tab',
          'class' => 'PiChart'
        ),
          'fragment' => 'studiesStudyDesign')); ?>
    </li>
    <li role="charts">
      <?php print l('Biological samples','',
        array('attributes'=>array(
          'aria-controls' => 'studiesCollectedBiologicalSamples',
          'role' => 'tab',
          'data-toggle' => 'tab',
          'class' => 'PiChart'
        ),
          'fragment' => 'studiesCollectedBiologicalSamples')); ?>
    </li>
    <li role="charts">
      <?php print l('Access','',
        array('attributes'=>array(
          'aria-controls' => 'studiesAccessToData',
          'role' => 'tab',
          'data-toggle' => 'tab',
          'class' => 'PiChart'
        ),
          'fragment' => 'studiesAccessToData')); ?>
    </li>
  </ul>

  <!-- Tab panes -->
  <div class="tab-content statistics-tab">
    <div role="tabpanel" class="tab-pane active" id="studiesGeoChart">
      <h5><strong><?php print t('Distribution of '.$network_name.' studies by participants\' countries of residence');; ?></strong></h5>
      <div id="regions_div"></div>
    </div>
    <div role="tabpanel" class="tab-pane" id="studiesRecruitmentSource">
      <div class="row">
        <div class="col-md-6">
          <div id="recruitmentTargetTable_div"></div>
        </div>
        <div class="col-md-6">
          <div class="scroll-content-tab">
            <div id="recruitmentSourcePieChart_div"></div>
          </div>
        </div>
      </div>
    </div>
    <div role="tabpanel" class="tab-pane" id="studiesStudyDesign">
      <div class="row">
        <div class="col-md-6">
          <div id="studiesStudyDesignTable_div"></div>
        </div>
        <div class="col-md-6">
          <div class="scroll-content-tab">
            <div id="studiesStudyDesignPieChart_div"></div>
          </div>
        </div>
      </div>

    </div>
    <div role="tabpanel" class="tab-pane" id="studiesCollectedBiologicalSamples">
      <div class="row">
        <div class="col-md-6">
          <div id="studiesCollectedBiologicalSamplesTable_div"></div>
        </div>
        <div class="col-md-6">
          <div class="scroll-content-tab">
            <div id="studiesCollectedBiologicalSamplesPieChart_div"></div>
          </div>
        </div>
      </div>

    </div>
    <div role="tabpanel" class="tab-pane" id="studiesAccessToData">
      <div class="row">
        <div class="col-md-6">
          <div id="studiesAccessToDataTable_div"></div>
        </div>
        <div class="col-md-6">
          <div class="scroll-content-tab">
            <div id="studiesAccessToDataPieChart_div"></div>
          </div>
        </div>
      </div>
    </div>
  </div>

