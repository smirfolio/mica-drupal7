<table id="data-access-request-history" class="table table-striped">
  <thead>
  <tr>
    <th class="status-icon"></th>
    <th translate>status</th>
    <th translate>changed-by</th>
    <th translate>Changed On</th>
  </tr>
  </thead>
  <tbody>
  <tr ng-repeat="status in dataAccessRequest.statusChangeHistory"
    ng-init="info = getStatusHistoryInfo[getStatusHistoryInfoId(status)]">
    <td><span><i class="{{info.icon}} hoffset"></i></span></td>
    <td>{{info.msg}}</span></span></td>
    <td>{{status.author}}</td>
    <td><span>{{status.changedOn | fromNow}}</span></td>
  </tr>
  </tbody>
</table>
