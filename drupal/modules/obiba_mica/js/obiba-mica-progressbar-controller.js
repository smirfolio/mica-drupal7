(function ($) {

  var hasAjax = false;
  var ready = false;

  $(document).ready(function () {
    if (!hasAjax) bar.finish();
    ready = true;
  });

  $(document).ajaxStart(function () {
    hasAjax = true;
    if (ready) bar.start();
  });

  $(document).ajaxSend(function () {
  });

  $(document).ajaxComplete(function () {
    bar.inc(5);
  });

  $(document).ajaxStop(function () {
    hasAjax = false
    bar.finish();
  });

  Drupal.behaviors.progress_bar = {
    attach: function (context, settings) {
      if (document === context) {
        bar = new $.ObibaProgressBar();
        bar.start();
      }
    }
  }

})(jQuery);
