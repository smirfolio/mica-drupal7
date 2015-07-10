/**
 * @file
 * JScript code for common resources - search page
 */

(function ($) {
  $(document).ready(function () {
    $('body').attr('data-spy', 'scroll').attr('data-target', '#scroll-menu').attr('data-offset', '150');
  });
}(jQuery));


(function ($) {
  Drupal.behaviors.obiba_mica_search_common = {
    attach: function (context, settings) {
      var isAjax = context !== document;

      $.urlParam = function (name) {
        var results = isAjax ? new RegExp('[!&]' + name + '=([^&#]*)').exec(window.location.hash):
          new RegExp('[\\?&]' + name + '=([^&#]*)').exec(window.location.search);

        return  results !== null ? results[1] || 0 : null;
      };

      $.urlParamToAdd = function () {
        var url = isAjax ? window.location.hash : window.location.search;
        var type = 'type';
        var page = 'page';
        var urlparts = url.split(isAjax ? '!' : '?');

        if (urlparts.length < 2) {
          return '';
        }

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

        return pars.join('&');
      };

      function trimJson(obj, parent, key) {
        if (obj instanceof Array) {
          if (obj.length === 0) {
            delete parent[key];
          }
        } else if (obj instanceof Object) {
          if ($.isEmptyObject(obj)) {
            delete parent[key];
          }
        } else {
          return;
        }

        $.each(obj, function (k, v) {
          trimJson(v, obj, k);
          if ($.isEmptyObject(obj) && parent) {
            delete parent[key];
          }
        })
      }

      $.trimJson = trimJson;

      function queryParamToJson() {
        var j, q;
        q = isAjax ? window.location.hash.replace(/^#!/, '').trim() :
          window.location.search.replace(/^\?/, '').trim();

        if ("" === q) return {};

        q = q.split("&");
        j = {};
        $.each(q, function(i, arr) {
          arr = arr.split('=');
          return j[arr[0]] = arr[1];
        });

        return j;
      }

      $.queryParamToJson = queryParamToJson;

      $.getParameterByName = function(query, name) {
        name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
        var regex = isAjax ? new RegExp('[!&]?' + name + '=([^&#]*)') : new RegExp('[\\?&]?' + name + '=([^&#]*)'),
          results = regex.exec(query);

        return results === null ? '' : decodeURIComponent(results[1].replace(/\+/g, ' '));
      };

      $.setState = function (key, data) {
        try {
          localStorage.setItem(key, JSON.stringify(data));
        } catch (e) {
          //ignore
        }
      };

      $.getState = function (key, def) {
        try {
          return JSON.parse(localStorage.getItem(key)) || def;
        } catch (e) {
          //ignore
          return def;
        }
      };
    }

  }

}(jQuery));