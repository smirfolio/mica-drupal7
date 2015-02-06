(function ($) {
  Drupal.behaviors.obiba_mica_search_coverage = {
    attach: function (context, settings) {
      $('#download-coverage > a', context).on('click', function(event){
        event.preventDefault();
        var $url = 'coverage/download'+ window.location.search;
        var form = $("<form action="+$url+" method='post'>");
        $(this).after(form);
        form.submit().remove();
      });
    }
  }
}(jQuery));