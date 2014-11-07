(function ($) {
  Drupal.behaviors.query_href = {
    attach: function (context, settings) {

      var URL_PARAM_QUERY = 'query';
      var tabparam = '';

      /**
       * Expose these methods to other JS files
       */
      $.extend({
        query_href: {
          getQueryFromUrl: getQueryFromUrl,
          updateQueryOperation: updateQueryOperation
        }
      });

      initializeTabParam();
      process();

      function getSelectedtermsAggSearchKey(attrAgg, value) {
        return attrAgg.replace("[]", "-terms[]") + value;
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
        var currJsonParam = getQueryFromUrl();
        return $.isEmptyObject(currJsonParam) ? [] : $.query_serializer.serializeJsonAsForm(currJsonParam);
      }

      function sendCheckboxCheckedValues() {
        return JSON.stringify($.query_serializer.serializeFormAsJson($("form[id^='facet-search'] :input[value!='']").serialize()));
      }

      function getQueryFromUrl() {
        var jsonParam = (window.location.search.replace(/(^\?)/, '').split("&").map(function (n) {
          return n = n.split("="), this[n[0]] = n[1], this
        }.bind({}))[0])['query'];

        return jsonParam === undefined ? {} : JSON.parse(decodeURIComponent(jsonParam));
      }

      function updateQueryOperation(operationMoniker, value) {
        console.log("Moniker", operationMoniker, value);
        var jsonQuery = getQueryFromUrl();
        if ($.isEmptyObject(jsonQuery)) {
          return;
        }

        var entry = /^(\w+):(\w+):(.*)$/.exec(operationMoniker);

        $.each(jsonQuery, function (type, typeValues) {
          if (type === entry[1]) {
            $.each(typeValues, function (aggType, aggs) {
              if (aggType === entry[2]) {
                $.each(aggs, function (name, agg) {
                  if (name === entry[3]) {
                    agg.op = value;
                    updateWindowLocation(JSON.stringify(jsonQuery));
                    return false;
                  }
                });
              }
            });
          }
        });
      }


      function processMatchesInput(selectedVars) {
        $.each(selectedVars, function (key, value) {
          if (/matches:facet-search-query$/.test(key)) {
            $("input[id='" + key + "']").val(value);
          }
          else {
            $("input[id='" + key + "']").val(value);
          }

        });
      }

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

              checkthebox($(this));
              var copy_chekbox = $(this).parent().clone();
              var divtofind = $(this).parents("section:first").find(".checkedterms:first");
              $("input[id=" + getAggregationMoniker(this) + "]").val($(this).attr("value"));
              copy_chekbox.find('.terms_stat').width($current_width_percent);

              divtofind.append(copy_chekbox);
              $(this).parents("li.facets").remove();
            }
          }
          else {
            if ($(this).hasClass("checked")) {
              uncheckthebox($(this));
              $("input[id=" + aggregation_name + "]").val('');
            }
          }
        });
      }

      function getValuesRangeTerms(valueWrapper) {
        var values = valueWrapper.match(/\[([^}]+)\]/);
        if (values) {
          var numbers = values[1].match(/\d+/g);
          return numbers;
        }
        return null;
      }

      function processRangeAggregationInputs(selectedVars) {
        $.each(selectedVars, function (key, value) {
          $("input[name='" + key + "']").val(value);
          var values = getValuesRangeTerms(value);
          if (key.match(/[\[\]']+/g)) {
            var idTermMin = key.replace(/[\[\]']+/g, '').split(':')[2] + '-min';
            var idTermMax = key.replace(/[\[\]']+/g, '').split(':')[2] + '-max';
            $("input[term='" + idTermMin + "']").val(values[0]);
            $("input[term='" + idTermMax + "']").val(values[1]);
          }
        });
      }

      function getAggregationMoniker(aggElement) {
        return "\"" + $(aggElement).attr("aggregation") + "-" + $(aggElement).attr('value') + "\"";
      }

      function updateCheckboxes() {
        var json = getQueryFromUrl();
        var aggregation_name = getAggregationMoniker(this);
        var input = $("input[id=" + aggregation_name + "]")
        if ($(this).hasClass("unchecked")) {
          checkthebox($(this));
          input.val($(this).attr("value"));
          $.query_serializer.addItem(json, decodeURIComponent(input.serialize()));
          updateWindowLocation(JSON.stringify(json));
          return false;
        }
        if ($(this).hasClass("checked")) {
          $.query_serializer.removeItem(json, decodeURIComponent(input.serialize()));
          uncheckthebox($(this));
          input.val('');
          updateWindowLocation(JSON.stringify(json));
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

      function initializeTabParam() {
        /**************************/
          //deal with tabs
        tabparam = '';
        var urlTabParam = $.urlParam('type');
        if (urlTabParam) {
          var div = $("div.search-result").find("div.tab-pane");
          div.removeClass("active");
          $("div#" + urlTabParam).addClass("active");
          $('#result-search a[href$="#' + urlTabParam + '"]').tab('show');
          tabparam = '&' + 'type=' + urlTabParam;
        }

      }

      function process() {
        /**********************/
        /*hide main search facet block*/
        $("section#block-mica-client-facet-search-facet-search").find("h2:first").css("display", "none");

        var selectedVars = getUrlVars();
        if (selectedVars) {
          processMatchesInput(selectedVars);
          processTermsAggregationInputs(selectedVars);
          processRangeAggregationInputs(selectedVars);
        }

        $("span#checkthebox").on("click", updateCheckboxes);

        $("span#checkthebox").mouseover(function () {
          if ($(this).hasClass("checked")) {
            rollover($(this));
            return false;
          }
        });

        $("span#checkthebox").mouseout(function () {
          if ($(this).hasClass("checked")) {
            rollout($(this));
            return false;
          }
        });

        /*send request search on checking the box or on click go button */
        $("div#checkthebox, button#facet-search-submit").on("click", function () {
          var json = getQueryFromUrl();
          $.query_serializer.addItem( //
            json, //
            decodeURIComponent($("input[id='" + $(this).attr('aggregation') + "']").serialize()) //
          );
          updateWindowLocation(JSON.stringify(json));
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
  }
})(jQuery);