<div>
    <div ng-if="loading" class="loading"></div>
    <div ng-show="!loading">
        <p class="help-block" ng-if="!summaries || !summaries.length" translate>
            search.study.noResults</p>
        <div class="table-responsive" ng-if="summaries && summaries.length">

            <table class="table " ng-init="lang = $parent.$parent.lang">
                <thead>
                <tr>
                    <th width="15%"></th>
                    <th>Name & Description</th>
                    <th width="15%"># Participants</th>
                </tr>
                </thead>
                <tbody>
                <tr ng-repeat="summary in summaries"
                    ng-init="lang = $parent.$parent.lang; studyPath= summary.studyResourcePath=='collection-study'?'study':summary.studyResourcePath" >
                    <td><img ng-if="summary.logo" src="" alt="">

                        <img src="{{summary.logoUrl}}"
                             class="img-responsive"/>

                        <h1 ng-if="!summary.logo" src="" alt=""
                            class="big-character">
                            <span class="t_badge color_light i-obiba-S"></span>
                        </h1></td>
                    <td>
                        <h4><a href="{{studyPath + '/' + summary.id | getBaseUrl}}">
                                <localized value="summary.name"
                                           lang="lang"></localized>
                            </a></h4>
                        <p ng-if="options.studiesListOptions.studiesTrimedDescrition">
                            <localized value="summary.objectives" lang="lang"
                                       ellipsis-size="250"></localized>
                        </p>
                        <p ng-if="!options.studiesListOptions.studiesTrimedDescrition">
                            <localized value="summary.objectives" lang="lang"></localized>
                        </p>
                        <div ng-if="options.studiesListOptions.studiesSupplInfoDetails">
                            <blockquote-small
                                    ng-if="summary.designs || summary.targetNumber.noLimit"
                                    class="help-block">
                                <span ng-if="summary.designs">
                                {{"search.study.design" | translate}} :<localized
                                            ng-repeat="d in summary.designs"
                                            value="designs[d]"
                                            lang="lang"></localized>
                                </span>
                                <span ng-if="summary.targetNumber.noLimit">
                                    <span ng-if="summary.designs">; </span>
                                    {{"numberOfParticipants.participants" | translate}} : {{"numberOfParticipants.no-limit" | translate}}
                                </span>
                            </blockquote-small>
                            <div class="sm-top-margin">
                                {{counts=summary['obiba.mica.CountStatsDto.studyCountStats'];""}}
                                <a ng-if="counts.networks" href="{{'networks' | doSearchQuery:'network(in(Mica_network.studyIds,' + summary.id +  '))' }}"
                                   class="btn btn-default btn-xxs"
                                   test-ref="networkCount">
                                    <localized-number
                                            value="counts.networks"></localized-number>
                                    {{counts.networks>1?"networks":"network.label"
                                    | translate}}
                                </a>
                                {{datasetsCount=counts.studyDatasets +
                                counts.harmonizationDatasets;""}}
                                <a ng-if="datasetsCount" href="{{'datasets' | doSearchQuery:'study(in(Mica_study.id,' + summary.id + '))'}}"
                                   class="btn btn-default btn-xxs"
                                   test-ref="datasetCount">
                                    <localized-number
                                            value="datasetsCount"></localized-number>
                                    {{datasetsCount>1?"datasets":"dataset.details"
                                    | translate}}
                                </a>
                                <a ng-if="counts.variables" href="{{'variables' | doSearchQuery:'study(in(Mica_study.id,' + summary.id + '))'}}"
                                   class="btn btn-default btn-xxs"
                                   test-ref="variableCount">
                                    <localized-number
                                            value="counts.variables"></localized-number>
                                    {{counts.variables>1?"variables":"search.variable.facet-label"
                                    | translate}}
                                </a>
                                <a ng-if="counts.studyVariables" href="{{'variables' | doSearchQuery:'study(in(Mica_study.id,' + summary.id + ')),variable(in(Mica_variable.variableType,Study))'}}"
                                   class="btn btn-default btn-xxs"
                                   test-ref="studyVariableCount">
                                    <localized-number
                                            value="counts.studyVariables"></localized-number>
                                    {{counts.studyVariables>1?"client.label.study-variables":"client.label.study-variable"
                                    | translate}}
                                </a>
                                <a ng-if="counts.dataschemaVariables" href="{{'variables' | doSearchQuery:'study(in(Mica_study.id,' + summary.id + ')),variable(in(Mica_variable.variableType,Dataschema))'}}"
                                   class="btn btn-default btn-xxs"
                                   test-ref="dataSchemaVariableCount">
                                    <localized-number
                                            value="counts.dataschemaVariables"></localized-number>
                                    {{counts.dataschemaVariables>1?"client.label.dataschema-variables":"client.label.dataschema-variable"
                                    | translate}}
                                </a>
                            </div>
                        </div>
                        <div class="clear-fix"></div>
                        <a href="{{'study/' + summary.id | getBaseUrl}}"
                           class="btn btn-primary btn-xs sm-top-margin">Read
                            More</a>
                    </td>
                    <td ng-if="summary.targetNumber.number">
                        <localized-number
                                value="summary.targetNumber.number"></localized-number>
                    </td>
                </tr>
                </tbody>
            </table>
        </div>
    </div>
</div>
