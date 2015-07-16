<span>
  <a href="<?php print base_path(); ?>/mica/study/{{contingency.studyTable.studyId}}">{{contingency.studyTable.studySummary.acronym | localizedValue}}</a>
  <span>
  {{contingency.studyTable.name | localizedValue}}
  </span>
</span>

<div class="lg-top-margin" ng-if="showDetails" ng-init="info = extractStudySummaryInfo(contingency.studyTable)">
  <small>
    <p class="text-muted no-margin">{{info.population}}</p>
    <p class="text-muted indent">{{info.dce}}</p>
    <p class="text-muted no-margin">{{info.project}}</p>
    <p class="text-muted indent">{{info.table}}</p>
  </small>
</div>
