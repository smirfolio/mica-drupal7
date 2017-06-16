<form class="form-horizontal form-inline">
  <label>{{"sort.by" | translate}}</label> :
  <div class="form-group form-group-sm">
    <select  class="form-control form-select"  id="edit-search-sort" name="search-sort"
             ng-options="option.label for option in selectSort.options track by option.value"
             ng-model="selectedSort"
             ng-change="onChanged()" >
    </select>
    <select  class="form-control form-select"  id="edit-search-order" name="search-order"
             ng-options="option.label for option in selectOrder.options track by option.value"
             ng-model="selectedOrder"
             ng-change="onChanged()" >
    </select>
  </div>
</form>
