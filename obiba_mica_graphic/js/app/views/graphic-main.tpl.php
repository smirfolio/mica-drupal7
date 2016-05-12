<div>
  <uib-tabset active="activeTab" class="voffset5">

    <uib-tab ng-click="selectTab('geoCharts')"
             heading="{{'graphics.geo-charts' | translate}}">
    </uib-tab>
    
    <uib-tab ng-click="selectTab('studyDesign')"
             heading="{{'graphics.study-design' | translate}}">
    </uib-tab>
    
    <uib-tab ng-click="selectTab('nbrParticipants')"
             heading="{{'graphics.number-participants' | translate}}">
    </uib-tab>
    
    <uib-tab ng-click="selectTab('bioSamples')"
             heading="{{'graphics.bio-samples' | translate}}">
    </uib-tab>
    
  </uib-tabset>
  <!-- Content -->
  <graphic-chart-container type="activeTab"></graphic-chart-container>
</div>
