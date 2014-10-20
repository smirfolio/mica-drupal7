(function ($) {
  $(document).ready(function() {
    $('body').attr('data-spy', 'scroll').attr('data-target', '#scroll-menu').attr('data-offset', '150');
  });
}(jQuery));


(function ($) {
  Drupal.behaviors.mica_client_facet_search_common = {
    attach: function (context, settings) {
      /********************/
      $.saveCookieDataTabs = function (newst, cookieName) {

        // Stringify the object in JSON format for saving in the cookie.
        var cookieString = '{ ';
        var cookieParts = [];

        $.each(newst, function (id, setting) {
          cookieParts[cookieParts.length] = '"' + id + '": "' + setting + '"';
        });

        cookieString += cookieParts.join(', ') + ' }';
        // console.log(cookieString);
        $.cookie(cookieName, cookieString, {
          time: 1,
          path: window.location.pathname
        });
      }

      $.getCookieDataTabs = function (nameCookie) {
        if ($.cookie) {
          var cookieString = $.cookie(nameCookie);
          return cookieString ? $.parseJSON(cookieString) : '';
        }
        else {
          return '';
        }
      }
      /******************************/
      $.urlParam = function (name) {
        var results = new RegExp('[\?&]' + name + '=([^&#]*)').exec(window.location.href);
        if (results == null) {
          return null;
        }
        else {

          return results[1] || 0;
        }
      };

      $.urlParamToAdd = function () {
        {
          var url = window.location.href;
          var type = 'type';
          var page = 'page';
          var urlparts = url.split('?');
          if (urlparts.length >= 2) {
            var typeParam = encodeURIComponent(type) + '=';
            var pageParam = encodeURIComponent(page) + '=';
            var pars = urlparts[1].split(/[&;]/g);
            for (var i = pars.length; i-- > 0;) {
              if (pars[i].indexOf(typeParam, 0) == 0) {
                pars.splice(i, 1);
              }
            }
            for (var i = pars.length; i-- > 0;) {
              if (pars[i].indexOf(pageParam, 0) == 0) {
                pars.splice(i, 1);
              }
            }

            if (pars.length > 0) {
              return pars.join('&');
            }
            else {
              return '';
            }
          }
          else {
            return '';
          }
        }
      };
    }}

}(jQuery));