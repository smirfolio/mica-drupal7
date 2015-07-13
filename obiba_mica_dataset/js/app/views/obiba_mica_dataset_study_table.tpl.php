<p ng-if="contingency.studyTable.name">
  <span class="control-label">{{'name' | translate}}:</span>
  <label>{{contingency.studyTable.name | localizedValue}}</label>
</p>
<p ng-if="contingency.studyTable.description">
  {{contingency.studyTable.description | localizedValue}}
</p>
