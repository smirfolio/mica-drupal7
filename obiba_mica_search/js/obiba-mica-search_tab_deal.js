/**
 * @file
 * JScript code for dealing with tabs
 */

(function ($) {
  Drupal.behaviors.obiba_mica_search_collapse_tab = {
    attach: function (context, settings) {
      var activeTabCookie = $.getState('activeFacetTab', {});

      if (jQuery.isEmptyObject(activeTabCookie)) {
        $(".facets-tab>li").each(function (id, state) {
          if ($(this).attr('class') == 'active') {
            activeTabCookie['active'] = $(this).find('a').attr('href');
          }
        });

        $.setState('activeFacetTab', activeTabCookie);
      }
      else {
        $('#facet-search a[href$="' + activeTabCookie["active"] + '"]').tab('show');
      }

      $('div#search-facets a[data-toggle="tab"]', context).on('shown.bs.tab', function (e) {
        e.preventDefault();
        var targetPanel = e.target.hash;
        activeTabCookie['active'] = targetPanel;
        $.setState('activeFacetTab', activeTabCookie);
      });

      $('#block-system-main a[role="tab"]', context).on('click', function (e) {
        e.preventDefault();
        var targetPanel = e.target.hash.replace('#', '');
        var current_page = $.getState('page_' + targetPanel) ? 'page=' + $.getState('page_' + targetPanel) : '';
        var url = ['type=' + targetPanel, $.urlParamToAdd(), current_page].filter(function (x) {return x;}).join('&');

        if (url.indexOf('with-facets') < 0) {
          url += '&with-facets=false'
        }

        window.location.hash = '!' + url;
        return false;
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
