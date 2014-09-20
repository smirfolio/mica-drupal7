(function ($) {
  Drupal.behaviors.queries = {
    attach: function (context, settings) {

      var URL_PARAM_QUERY = 'query';

      function getSelectedtermsAggSearchKey(attrAgg, value) {
        return attrAgg.replace("[]", "-terms[]")+value;
      }

      /**
       * Desrializes the form JSON into an array of aggregation values. Only range agg values are formatted
       * @param json
       * @returns {Array}
       */
      function desrializeFormJsonAsKeyValue(json) {
        var formData = {};
        $.each(json, function(type, typeValues){
          $.each(typeValues, function(aggType, aggs){
            $.each(aggs, function (name, values) {
              $.each(values, function (i, value) {
                var formattedName = name + "-" + aggType + "[]";
                var key = type+":"+formattedName + (aggType === "terms" ? value : name);
                formData[key] = aggType === "terms" ? value : name + ".[+" + value.min + "+to+" + value.max + "+]";
              });
            })
          });
        });

        return $.isEmptyObject(formData) ? null : formData;
      }

      function serializeFormAsJson(formData) {

        /**
         * Helper used to extract entry information needed to build the form JSON
         * @param value
         * @returns {{type: *, agg: *, aggType: *, aggValue: *}}
         */
        function extractFormEntry(value) {
          var entry = /(\w+):(.*)-(terms|range)[\\[\\]]*=(.*)$/.exec(value);
          return {type: entry[1], agg: entry[2], aggType: entry[3], aggValue: extractAggValue(entry[4])};
        }

        /**
         * If the agg value has range info, return value as min-max
         * @param value
         * @returns {*}
         */
        function extractAggValue(value) {
          var entry = /\[\+([+-]*\d+)\+to\+([+-]*\d+)\+\]/.exec(value);
          if (entry != null) return {min: entry[1], max: entry[2]};
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
                jsonForm[entry.type][entry.aggType] = {};
              }

              if (!jsonForm[entry.type][entry.aggType].hasOwnProperty(entry.agg)) {
                jsonForm[entry.type][entry.aggType][entry.agg] = [];
              }

              jsonForm[entry.type][entry.aggType][entry.agg].push(entry.aggValue);
            }
          });

          return jsonForm;
        }

        return parse(formData);
      }

      function checkthebox(obj_span) {
        obj_span.removeClass("unchecked");
        obj_span.addClass("checked");
        obj_span.children(":first").removeClass();
        obj_span.children(":first").addClass("glyphicon glyphicon-ok");
      }

      function uncheckthebox(obj_span) {
        obj_span.removeClass("checked");
        obj_span.addClass("unchecked");
        obj_span.children(":first").removeClass();
        obj_span.children(":first").addClass("glyphicon glyphicon-unchecked");
      }

      function rollover(obj_span) {
        obj_span.children(":first").removeClass();
        obj_span.children(":first").toggleClass("glyphicon glyphicon-remove");
      }

      function rollout(obj_span) {
        obj_span.children(":first").removeClass();
        obj_span.children(":first").toggleClass("glyphicon glyphicon-ok");
      }

      function getUrlVars() {
        var pos = window.location.href.indexOf(URL_PARAM_QUERY + "=");
        if (pos === -1) return [];
        return desrializeFormJsonAsKeyValue(JSON.parse(decodeURIComponent($.urlParam(URL_PARAM_QUERY))));
      }

      function sendCheckboxCheckedValues(idcheckbox) {
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

        return JSON.stringify(serializeFormAsJson(serializedData));
      }

      /*******************/
      $.extend({
        checkthebox: checkthebox,
        uncheckthebox: uncheckthebox,
        rollover: rollover,
        rollout: rollout,
        getUrlVars: getUrlVars,
        sendCheckboxCheckedValues: sendCheckboxCheckedValues
      });

      /**************************/
      //deal with tabs
      var tabparam = '';
      var urlTabParam = $.urlParam('type');
      if (urlTabParam) {
        var div = $("div.search-result").find("div.tab-pane");
        div.removeClass("active");
        $("div#" + urlTabParam).addClass("active");
        $('#result-search a[href$="#' + urlTabParam + '"]').tab('show');
        tabparam = '&' + 'type=' + urlTabParam;
      }

      /**********************/
      /*hide main search facet block*/
      $("section#block-mica-client-facet-search-facet-search").find("h2:first").css("display", "none");

      /**
       * Iterates through each hidden input that has been selected/unselected
       * @param selectedVars
       */
      function processTermsAggregationInputs(selectedVars) {
        $('input[type="hidden"]').each(function () {
          var currInputId = $(this).attr('id');
          var currInputName = $(this).attr('name');
          var selectedVar = selectedVars[currInputName + currInputId];
          if (selectedVar) {
            $('#' + currInputId).val(selectedVar.replace(/\+/g, ' '));
          }

        });

        $('span#checkthebox').each(function () {
          var aggregation_name = $(this).attr('value');
          var selectedVar = selectedVars[getSelectedtermsAggSearchKey($(this).attr('aggregation'), aggregation_name)];
          if (selectedVar) {
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
      }

      var selectedVars = $.getUrlVars();
      console.log(selectedVars);
      if (selectedVars) {
        processTermsAggregationInputs(selectedVars);
      }

      function updateCheckboxes() {
        var aggregation_name = $(this).attr('value');
        if ($(this).hasClass("unchecked")) {
          $.checkthebox($(this));
          $("input[id=" + aggregation_name + "]").val($(this).attr("value"));
          updateWindowLocation($.sendCheckboxCheckedValues());
          return false;
        }
        if ($(this).hasClass("checked")) {
          $.uncheckthebox($(this));
          $("input[id=" + aggregation_name + "]").val('');
          updateWindowLocation($.sendCheckboxCheckedValues());
          return false;
        }
      }

      function updateWindowLocation(checkboxValues) {
        if (!checkboxValues || "{}" === checkboxValues) {
          window.location = '?' + (tabparam ? tabparam : '');
        }
        else {
          window.location = '?' + (tabparam ? tabparam + '&' : '') + URL_PARAM_QUERY + '=' + checkboxValues;
        }
      }

      $("span#checkthebox").on("click", updateCheckboxes);

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
        updateWindowLocation($.sendCheckboxCheckedValues());
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