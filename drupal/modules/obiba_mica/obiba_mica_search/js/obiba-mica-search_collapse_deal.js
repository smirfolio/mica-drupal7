/**
 * @file
 * JScript code for dealing with collapsible blocks
 */

(function ($) {
  Drupal.behaviors.obiba_mica_search_collapse_block = {
    attach: function (context, settings) {

      var newst = {};
      var newst1 = {};
      var sectionid;
      var st = $.getCookieDataTabs('activeAccordionGroup');

      if (jQuery.isEmptyObject(st)) {
        $(".block-content").each(function (id, state) {
          var current_id = this.id;
          $("#" + current_id).collapse("show");
          newst1[current_id] = 'in';

        });

        $.saveCookieDataTabs(newst1, 'activeAccordionGroup');
      }
      else {
        $(".block-content").each(function (id, state) {
          var current_id = this.id;

          //show the last visible group
          if (st[current_id]) {
            $("#" + current_id).collapse("show");
            newst1[current_id] = 'in';
          }
          else {
            $("#" + current_id).collapse("hide");
            dealwithhrefico(current_id, 'collapsed');
            delete newst1[current_id];

          }

        });

        $.saveCookieDataTabs(newst1, 'activeAccordionGroup');
      }

//when a group is shown, save it as the active accordion group
      $(".block").on('shown.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';

          }
          else {
            delete newst[current_id];
          }
        });
        $.saveCookieDataTabs(newst, 'activeAccordionGroup');
      });

      //when a group is shown, save it as the active accordion group
      $(".block").on('hidden.bs.collapse', function () {
        $(".block-content").each(function (id, state) {
          //var id_active = $(".panel-collapse .in").attr('id');
          var current_id = this.id;
          if ($("#" + current_id).hasClass("in")) {
            newst[current_id] = 'in';
          }
          else {
            delete newst[current_id];
          }

        });
        $.saveCookieDataTabs(newst, 'activeAccordionGroup')
      });


      /********** Show more show less on search page********/

      $('.charts').on('shown.bs.collapse', function () {
        $('.text-button-field').html(Drupal.t('Show less'));
      });

      $('.charts').on('hidden.bs.collapse', function () {
        $('.text-button-field').html(Drupal.t('Show all'));
      });

      /*********more less in search block ********/
      $(".expand-control").each(function () {
        $('.expand-control-div' + $(this).attr('id')).on('shown.bs.collapse', function () {
          console.log($(this).attr('id'));
          $('.expand-control-link' + $(this).attr('id')).html(Drupal.t('Less'));
        });

        $('.expand-control-div' + $(this).attr('id')).on('hidden.bs.collapse', function () {
          $('.expand-control-link' + $(this).attr('id')).html(Drupal.t('More'));
        });
      });


      /*******************************************/

      function dealwithhrefico(current_id, collapse) {
        if (collapse && current_id) {
          sectionid = current_id.replace("collapse-", "");
          $("#" + sectionid + " h2.block-title a:first").addClass(collapse);
        }
      }

    }
  }
}(jQuery));