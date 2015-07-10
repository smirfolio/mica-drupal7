(function ($) {
  Drupal.behaviors.obiba_mica_search_coverage = {
    attach: function (context, settings) {
      $('#download-coverage > a', context).on('click', function(event){
        event.preventDefault();
        $('iframe.coverage-download-helper').remove();
        var $url = 'coverage/download?' + window.location.hash.replace(/#!/, '');
        var iframe = $('<iframe src=' + $url + ' style="display: none;" class="coverage-download-helper">');
        $(this).after(iframe);
      });
    }
  }
}(jQuery));