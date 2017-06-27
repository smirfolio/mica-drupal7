<form class="form-horizontal form-inline">
  <label>{{"filter.by" | translate}}</label> :
  <div class="form-group form-group-sm">
    <div class="input-group">
      <input  class="form-control form-input"  id="edit-search-filter" name="search-filter"
              ng-model="searchFilter"
              ng-keyup="onKeypress($event)" >
      </input>
      <div class="input-group-addon bg-primary"><i class="glyphicon glyphicon-search"></i></div>
    </div>
</form>