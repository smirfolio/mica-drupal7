(function ($) {
  Drupal.behaviors.obiba_mica_search_coverage = {
    attach: function (context, settings) {
      $("#download-coverage > a").on('click', function(event){
        var $url = 'coverage/download'+ window.location.search;
        var form = $("<form action="+$url+" method='post'>");
        $(this).after(form);
        form.submit().remove();
        event.preventDefault();
      });
    }
  }
}(jQuery));