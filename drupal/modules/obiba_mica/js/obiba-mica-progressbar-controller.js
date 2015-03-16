(function ($) {

  var hasAjax = false;
  var ready = false;

  $(document).ready(function () {
    console.log('Document ready');
    if (!hasAjax) bar.finish();
    ready = true;
  });

  $(document).ajaxStart(function () {
    console.log('Document ajax started');
    hasAjax = true;
    if (ready) bar.start();
  });

  $(document).ajaxSend(function () {
    console.log('Document ajax send');
  });

  $(document).ajaxComplete(function () {
    console.log('Document ajax complete');
    bar.inc(5);
  });

  $(document).ajaxStop(function () {
    console.log('Document ajax stop');
    hasAjax = false
    bar.finish();
  });

  Drupal.behaviors.progress_bar = {
    attach: function (context, settings) {
      if (document === context) {
        console.log('Drupal attach');
        bar = new $.ObibaProgressBar();
        console.log('Bar', bar);
        bar.start();
      }
    }
  }

})(jQuery);
