(function ($) {
  Drupal.behaviors.mica_client_facet_search_collapse_tab = {
    attach: function (context, settings) {

      var newst = {};
      var newst1 = {};
      var sectionid;
      var activeTabCooki = $.getCookieDataTabs('activeFacetTab');

      if (jQuery.isEmptyObject(activeTab)) {
        $(".facets-tab>li").each(function (id, state) {
          //   var current_id = this.firstChild().attr('href');
          console.log($(this).attr('class'));
          if ($(this).attr('class') == 'active') {
            console.log($(this).find('a').attr('href'));
            activeTab[$(this).find('a').attr('href')] = 'active';
          }

        });

        $.saveCookieDataTabs(activeTab, 'activeFacetTab');
      }
      else {
        console.log(activeTabCooki);
      }

      if ($.urlParam('type')) {

        var div = $("div.search-result").find("div.tab-pane");
        div.removeClass("active");
        $("div#" + $.urlParam('type')).addClass("active");
        $('#result-search a[href$="#' + $.urlParam('type') + '"]').tab('show');
      }

      $("div#search-result").find('a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
        // e.target // activated tab
        // e.relatedTarget // previous tab
        e.preventDefault();
        var targetPanel = e.target.hash;
        $.saveCookieDataTabs('', 'activeFacetTab');
        activeTab[$(this).find('a').attr('href')] = 'active';
        $.saveCookieDataTabs(activeTab, 'activeFacetTab');
        console.log(activeTab);
        // $.saveCookieDataTabs(activeTab,'activeFacetTab');
        //    window.location = '?' + 'type=' + targetPanel.replace('#', '') + '&' + $.urlParamToAdd();
      })
    }
  }
}(jQuery));