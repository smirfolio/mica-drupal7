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
          updateQueryOperation: updateQueryOperation,
          getQueryForm: getQueryForm
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

      function getQueryForm() {
        var items = new Array();

        $.each($("form[id^='facet-search'] :input[value!='']"), function(i, input){
          items.push(decodeURIComponent(serializeElement($(input))));
        });

        return {'localized': $.query_serializer.serializeFormAsLocalizedJson(items), 'data': getQueryFromUrl()};
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

      function serializeElement(element) {
        var dataArr = new Array();
        $.each(element.data(), function(att, value) {
          dataArr.push({'name': att, 'value': value});
        })

        return $.param(element.serializeArray().concat(dataArr));
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
          var aggregation_name = $(this).attr('data-value');
          var selectedVar = selectedVars[getSelectedtermsAggSearchKey($(this).attr('aggregation'), aggregation_name)];
          if (selectedVar) {
            var $current_width_percent = $(this).parent().find('.terms_stat:first').attr('witdh-val');

            if ($(this).hasClass("unchecked")) {
              $(this).parents("label.span-checkbox").css("display", "inline");
              $(this).parents("label.span-checkbox").removeClass();

              checkthebox($(this));
              var copy_chekbox = $(this).parent().clone();
              var divtofind = $(this).parents("section:first").find(".checkedterms:first");
              $("input[id=" + getAggregationMoniker(this) + "]").val($(this).attr('value')).attr('data-value', $(this).attr("data-value"));
              copy_chekbox.find('.terms_stat').width($current_width_percent);

              divtofind.append(copy_chekbox);
              $(this).parents("li.facets").remove();
            }
          }
          else {
            if ($(this).hasClass("checked")) {
              uncheckthebox($(this));
              $("input[id=" + aggregation_name + "]").val('').attr('data-value', '');
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
          var entry = /^\w+:(\w+)/.exec(key);
          if (entry && entry[1] === 'range') {
            $("input[name='" + key + "']").val(value);
            var values = getValuesRangeTerms(value);
            if (key.match(/[\[\]']+/g)) {
              var idTermMin = key.replace(/[\[\]']+/g, '').split(':')[2] + '-min';
              var idTermMax = key.replace(/[\[\]']+/g, '').split(':')[2] + '-max';
              $("input[term='" + idTermMin + "']").val(values[0]);
              $("input[term='" + idTermMax + "']").val(values[1]);
            }
          }
        });
      }

      function getAggregationMoniker(aggElement) {
        return "\"" + $(aggElement).attr("aggregation") + "-" + $(aggElement).attr('data-value') + "\"";
      }

      function updateCheckboxes() {
        var json = getQueryFromUrl();
        var aggregation_name = getAggregationMoniker(this);
        var input = $("input[id=" + aggregation_name + "]")
        if ($(this).hasClass("unchecked")) {
          checkthebox($(this));
          input.val($(this).attr('value'));
          input.attr('data-value', $(this).attr("data-value"));
          $.query_serializer.addItem(json, decodeURIComponent(serializeElement(input)));
          updateWindowLocation(JSON.stringify(json));
          return false;
        }
        if ($(this).hasClass("checked")) {
          $.query_serializer.removeItem(json, decodeURIComponent(serializeElement(input)));
          uncheckthebox($(this));
          input.val('');
          input.attr('data-value', '');
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

      function formClickHandler(aggregation) {
        var json = getQueryFromUrl();
        var input = $("input[id='" + aggregation + "']");
        if (input.val()) {
          $.query_serializer.addItem( //
            json, //
            decodeURIComponent(serializeElement(input)) //
          );
        } else {
          $.query_serializer.removeItem( //
            json, //
            decodeURIComponent(serializeElement(input)) //
          );
        }

        updateWindowLocation(JSON.stringify(json));
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

        $("body").keypress(function (event) {
          if (event.which == 13) {
            if ($("input[id*='matches:facet-search-query']").is(":focus")) {
              var element = $(document.activeElement)[0];
              event.preventDefault();
              formClickHandler($(element).attr('id'));
            }
          }
        });

        /*send request search on checking the box or on click go button */
        $("div#checkthebox, button#facet-search-submit").on("click", function () {
          formClickHandler($(this).attr('aggregation'));
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