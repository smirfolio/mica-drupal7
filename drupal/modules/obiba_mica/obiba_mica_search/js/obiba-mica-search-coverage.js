(function ($) {
  Drupal.behaviors.obiba_mica_search_coverage = {
    attach: function (context, settings) {
      $('#download-coverage > a', context).on('click', function(event){
        event.preventDefault();
        var $url = 'coverage/download?' + window.location.hash.replace(/#!/, '');
        var form = $("<form action="+$url+" method='get'>");
        $(this).after(form);
        form.submit().remove();
      });
    }
  }
}(jQuery));