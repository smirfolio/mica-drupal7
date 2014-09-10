(function ($) {
  Drupal.behaviors.mica_client_dataset_collapse = {
    attach: function (context, settings) {
      /****Bug displaying studies and variables tab*****/
      $("div#search-result").find('a[data-toggle="tab"]').on('shown.bs.tab', function (e) {
        // e.target // activated tab
        // e.relatedTarget // previous tab
        var targetPanel = e.target.hash;
        var div = $("div.search-result").find("div.tab-pane");
        //console.log(div);
        div.removeClass("active");
        $("div" + targetPanel).addClass("active");
      })

    }
  }
}(jQuery));