/**
 * @file
 * JScript code for dealing with tabs
 */

(function ($) {
  Drupal.behaviors.obiba_mica_search_collapse_tab = {
    attach: function (context, settings) {
      var activeTabCookie = $.getCookieDataTabs('activeFacetTab');

      if (jQuery.isEmptyObject(activeTabCookie)) {
        $(".facets-tab>li").each(function (id, state) {
          console.log($(this).attr('class'));
          if ($(this).attr('class') == 'active') {
            console.log($(this).find('a').attr('href'));
            activeTabCookie['active'] = $(this).find('a').attr('href');
          }
        });

        $.saveCookieDataTabs(activeTabCookie, 'activeFacetTab');
      }
      else {
        $('#facet-search a[href$="' + activeTabCookie["active"] + '"]').tab('show');
      }

      $('div#search-facets a[data-toggle="tab"]', context).on('shown.bs.tab', function (e) {
        e.preventDefault();
        var targetPanel = e.target.hash;
        $.saveCookieDataTabs('', 'activeFacetTab');
        activeTabCookie['active'] = targetPanel;
        $.saveCookieDataTabs(activeTabCookie, 'activeFacetTab');
      });

      $('#block-system-main a[role="tab"]', context).on('click', function (e) {
        e.preventDefault();
        var targetPanel = e.target.hash.replace('#', '');
        var current_page = $.getCookieDataTabs('page_' + targetPanel) ? 'page=' + $.getCookieDataTabs('page_' + targetPanel) : '';
        window.location.hash = '!' + ['type=' + targetPanel, $.urlParamToAdd(), current_page].filter(function(x) {return x;}).join('&');
      });

      function setActiveTab(type) {
        var div = $("div.search-result").find("div.tab-pane");
        div.removeClass("active");
        $("div#" + type).addClass("active");
        $('#result-search a[href$="#' + type + '"]').tab('show');
      }

      var type = $.getParameterByName(window.location.hash, 'type');

      if (type) {
        setActiveTab(type);
      }
    }
  }
}(jQuery));