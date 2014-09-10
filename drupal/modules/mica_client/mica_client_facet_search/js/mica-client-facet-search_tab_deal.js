(function ($) {
  Drupal.behaviors.mica_client_dataset_collapse = {
    attach: function (context, settings) {

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
          param = 'tab';
          var urlparts = url.split('?');
          if (urlparts.length >= 2) {
            var prefix = encodeURIComponent(param) + '=';
            var pars = urlparts[1].split(/[&;]/g);
            for (var i = pars.length; i-- > 0;) {
              if (pars[i].indexOf(prefix, 0) == 0) {
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

      if ($.urlParam('tab')) {
        var NewUrlparameters = $.urlParamToAdd();
        var div = $("div.search-result").find("div.tab-pane");
        div.removeClass("active");
        $("div#" + $.urlParam('tab')).addClass("active");
        $('#result-search a[href$="#' + $.urlParam('tab') + '"]').tab('show');
      }

      /****Bug displaying studies and variables tab*****/

      $("div#search-result").find('a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
        // e.target // activated tab
        // e.relatedTarget // previous tab

        var targetPanel = e.target.hash;
        window.location = '?' + 'tab=' + targetPanel.replace('#', '') + '&' + $.urlParamToAdd();
        e.preventDefault();
//        var div = $("div.search-result").find("div.tab-pane");
//        //console.log(div);
//        div.removeClass("active");
//        $("div" + targetPanel).addClass("active");

      })
    }
  }
}(jQuery));