(function ($) {
  Drupal.behaviors.queries = {
    attach: function (context, settings) {

      /**
       * Desrializes the form JSON into an array of aggregation values. Only range agg values are formatted
       * @param json
       * @returns {Array}
       */
      function desrializeFormJsonAsKeyValue(json) {
        var values = [];
        $.each(json, function(type, typeValues){
          $.each(typeValues, function(aggType, aggs){
            $.each(aggs, function(i, keyValue) {
              $.each(keyValue, function(name, value) {
                values.push(aggType === "terms" ? value : name+".[+"+value.min+"+to+"+value.max+"+]");
              });

            })
          });
        });

        return values;
      }

      function serializeFormAsJson(formData) {

        /**
         * Helper used to extract entry information needed to build the form JSON
         * @param value
         * @returns {{type: *, agg: *, aggType: *, aggValue: *}}
         */
        function extractFormEntry(value) {
          var tuple = /(\w+):(.*)-(terms|range)[\\[\\]]*=(.*)$/.exec(value);
          return {type: tuple[1], agg: tuple[2], aggType: tuple[3], aggValue: extractAggValue(tuple[4])};
        }

        /**
         * If the agg value has range info, return value as min-max
         * @param value
         * @returns {*}
         */
        function extractAggValue(value) {
          var tuple = /\[\+([+-]*\d+)\+to\+([+-]*\d+)\+\]/.exec(value);
          if (tuple != null) return {min: tuple[1], max: tuple[2]};
          return value;
        }

        /**
         * Parses the formData serialized as a DOM object and returns it as JSON object
         * @param formData
         * @returns {{}}
         */
        function parse(formData) {
          var jsonForm = {};

          $.each(decodeURIComponent(formData).split('&'), function(i, value) {
            if (value != null && value.length > 0) {
              var entry = extractFormEntry(value);

              if (!jsonForm.hasOwnProperty(entry.type)) {
                jsonForm[entry.type] = {};
              }

              if (!jsonForm[entry.type].hasOwnProperty(entry.aggType)) {
                jsonForm[entry.type][entry.aggType] = [];
              }

              var item = {};
              item[entry.agg] = entry.aggValue;
              jsonForm[entry.type][entry.aggType].push(item);
            }
          });

          return jsonForm;
        }

        return parse(formData);
      }

      /*******************/
      $.extend({
        checkthebox: function (obj_span) {
          obj_span.removeClass("unchecked");
          obj_span.addClass("checked");
          obj_span.children(":first").removeClass();
          obj_span.children(":first").addClass("glyphicon glyphicon-ok");
        },

        uncheckthebox: function (obj_span) {
          obj_span.removeClass("checked");
          obj_span.addClass("unchecked");
          obj_span.children(":first").removeClass();
          obj_span.children(":first").addClass("glyphicon glyphicon-unchecked");
        },
        rollover: function (obj_span) {
          obj_span.children(":first").removeClass();
          obj_span.children(":first").toggleClass("glyphicon glyphicon-remove");
        },
        rollout: function (obj_span) {
          obj_span.children(":first").removeClass();
          obj_span.children(":first").toggleClass("glyphicon glyphicon-ok");
        },

        getUrlVars: function () {
          var pos = window.location.href.indexOf('?');
          if (pos === -1) return [];

          var vars = desrializeFormJsonAsKeyValue(JSON.parse(decodeURIComponent(window.location.href.slice(pos + 1))));
          // TODO until we find out why we have to add empty entry at the end
          vars.push("");
          return vars;
        },
        sendCheckboxCheckedValues: function (idcheckbox) {
          var serializedData = "";
          $('form').each(function () {
            $('input', 'form').each(function () {
              $(this).val() == "" && $(this).remove();
            });
            var SerilizedForm = ($(this).serialize());
            if (SerilizedForm && $(this).attr('id').match(/facet-search/g)) {
              serializedData = serializedData.concat(SerilizedForm).concat('&');
            }
          });

//          return serializedData;
          return JSON.stringify(serializeFormAsJson(serializedData));
        }
      });


      /**************************/
      //deal with tabs
      var tabparam = '';
      var urlTabParam = $.urlParam('type');
      console.log(urlTabParam);
      if (urlTabParam) {
        var NewUrlparameters = $.urlParamToAdd();
        var div = $("div.search-result").find("div.tab-pane");
        div.removeClass("active");
        $("div#" + urlTabParam).addClass("active");
        $('#result-search a[href$="#' + urlTabParam + '"]').tab('show');
        tabparam = '&' + 'type=' + urlTabParam;
      }

      /**********************/
      /*hide main search facet block*/
      $("section#block-mica-client-facet-search-facet-search").find("h2:first").css("display", "none");

      var allVars = $.getUrlVars();

      $('input[type="hidden"]').each(function () {
        var currInputidPattern = $(this).attr('id') + "\\W";
        var currInputid = $(this).attr('id');
        // console.log(currInputid);
        if (allVars.toString().search(new RegExp(currInputidPattern)) != -1) {
          $.grep(allVars, function (element, i) {
            if (!element.indexOf(currInputid)) {
              $('#' + currInputid).val(element.replace(/\+/g, ' '));
            }
          });
        }
      });


      $('span#checkthebox').each(function () {
        var currInputidPattern = $(this).attr('value') + "\\W";
        var currInputid = $(this).attr('value');


        var aggregation_name = $(this).attr('value');

        if (allVars.toString().search(new RegExp(currInputidPattern)) != -1) {
          var $current_width_percent = $(this).parent().find('.terms_stat:first').attr('witdh-val');

          if ($(this).hasClass("unchecked")) {
            $(this).parents("label.span-checkbox").css("display", "inline");
            $(this).parents("label.span-checkbox").removeClass();

            $.checkthebox($(this));
            var copy_chekbox = $(this).parent().clone();
            var divtofind = $(this).parents("section:first").find(".chekedterms:first");
            $("input[id=" + aggregation_name + "]").val($(this).attr("value"));

            copy_chekbox.find('.terms_stat').width($current_width_percent);

            divtofind.append(copy_chekbox);
            $(this).parents("li.facets").remove();
          }
        }
        else {
          if ($(this).hasClass("checked")) {
            $.uncheckthebox($(this));
            $("input[id=" + aggregation_name + "]").val('');
          }
        }
      });

      $("span#checkthebox").on("click", function (e) {
        var aggregation_name = $(this).attr('value');
        if ($(this).hasClass("unchecked")) {
          $.checkthebox($(this));
          $("input[id=" + aggregation_name + "]").val($(this).attr("value"));
          window.location = '?' + $.sendCheckboxCheckedValues() + tabparam;
          return false;
        }
        if ($(this).hasClass("checked")) {
          $.uncheckthebox($(this));
          $("input[id=" + aggregation_name + "]").val('');
          window.location = '?' + $.sendCheckboxCheckedValues() + tabparam;
          //  console.log($.sendCheckboxCheckedValues());
          return false;
        }
      });

      $("span#checkthebox").mouseover(function () {
        if ($(this).hasClass("checked")) {
          $.rollover($(this));
          return false;
        }
      });

      $("span#checkthebox").mouseout(function () {
        if ($(this).hasClass("checked")) {
          $.rollout($(this));
          return false;
        }
      });

      /*send request search on checking the box or on click go button */
      $("div#checkthebox").on("click", function () {
        //  $.sendCheckboxCheckedValues();
        window.location = '?' + $.sendCheckboxCheckedValues();
      });

      $("input[id='range-auto-fill']").on("blur", function () {
        var term = $(this).attr('termselect');
        var minid = term + '-min';
        var maxid = term + '-max';
        var minvalue = $("input[term='" + minid + "']").val();
        var maxvalue = $("input[term='" + maxid + "']").val();

        if (minvalue || maxvalue) {
          $('#' + $(this).attr('termselect')).val(term + '.[ ' + minvalue + ' to ' + maxvalue + ' ]');
        }
        if (!maxvalue && !minvalue) {
          $('#' + $(this).attr('termselect')).val('');
        }

      });

    }
  }
})(jQuery);