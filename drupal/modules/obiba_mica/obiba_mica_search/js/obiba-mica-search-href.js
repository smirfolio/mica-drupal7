/**
 * @file
 * JScript code for dealing with checkboxes facet
 */
(function ($) {
  var updateCollapsibleUI = false;

  $(document).ready(function () {
    updateCollapsibleUI = true;
  });

  Drupal.behaviors.query_href = {
    attach: function (context, settings) {
      var isAjax = context !== document;
      var delIcon = $('<i class="remove-icon clickable glyphicon glyphicon-remove-circle"></i>');
      var undoIcon = $('<span class="remove-icon clickable flaticon-undo9" aggregation=""></span>');

      if (Drupal.settings.UrlErrorsQuery) {
        console.log('error on page session error');
        setTimeout(function () {
          updateWindowLocation();
        }, 2000);
      }

      var tabparam = '';

      /*override autocomplete Drupal function */
      if (Drupal.jsAC) {

        /*select On press enter action */
        Drupal.jsAC.prototype.onkeydown = function (input, e) {
          if (!e) {
            e = window.event;
          }
          switch (e.keyCode) {
            case 13: // Enter.
              e.preventDefault();
              var selectedValue = $(this.selected).data('autocompleteValue');
              updateCheckboxesByChekbox(
                $(this.input).closest('section').find('span#checkthebox[data-value="' + selectedValue + '"]')[0]);
              return true;
            case 40: // down arrow.
              this.selectDown();
              return false;
            case 38: // up arrow.
              this.selectUp();
              return false;
            default: // All other keys.
              return true;
          }
        };

        Drupal.jsAC.prototype.select = function (node) {
          var selectedValue = $(node).data('autocompleteValue');
          updateCheckboxesByChekbox(
            $(this.input).closest('section').find('span#checkthebox[data-value="' + selectedValue + '"]')[0]);
        };
      }

      function updateCheckboxesByChekbox(checkboxSpan) {
        var json = getQueryFromUrl();
        var aggregation_name = getAggregationMoniker(checkboxSpan);
        var input = $("input[id=" + aggregation_name + "]");

        if ($(checkboxSpan).hasClass("unchecked")) {
          checkthebox($(checkboxSpan));
          input.val($(checkboxSpan).attr('value'));
          input.attr('data-value', $(checkboxSpan).attr("data-value"));
          $.query_serializer.addItem(json, decodeURIComponent(serializeElement(input)));
          updateWindowLocation(JSON.stringify(json));
        }

        return false;
      }

      function initSearchTerms() {
          initializeTabParam();
          process();
          /*************Deal with icon for clearing the full text search input field *******/
          //range input initializing reset
          //  var input_ranges = $('.form-item-range-from');
          var input_ranges = $("input[type='hidden'].form-item-range-from");

          input_ranges.each(function () {
              var input_form_container = $(this).parent();
              var content_icon = input_form_container.find('.remove-icon-content');
              var Hidden_input_form = input_form_container.find("input[type='hidden'].form-item-range-from");
              var aggregation = Hidden_input_form.attr('id');
              var input_range_val_to_reset = input_form_container.find('.form-item-range-from');
              var defaultMinvalue, defaultMaxvalue;
              if ($(this).val() && content_icon.find('span.remove-icon').length === 0) {
                var current_undo_icon = undoIcon.clone().appendTo(content_icon);
                current_undo_icon.attr('aggregation', aggregation);
                current_undo_icon.off('click').on("click", function () {
                    var clearButton = $(this);

                    input_range_val_to_reset.each(function () {
                        $(this).val('');
                        if ($(this).attr('term') == aggregation + '-min') {
                            defaultMinvalue = $(this).attr('placeholder');

                        }
                        if ($(this).attr('term') == aggregation + '-max') {
                            defaultMaxvalue = $(this).attr('placeholder');
                        }
                    });

                    Hidden_input_form.attr("value", '');
                    Hidden_input_form.val('');

                    formClickHandler($(clearButton).attr('aggregation'));
                });
              }
          });

          //free search initializing reset
          var inputSearch = $("input[id*='matches:facet-search-query']");
          inputSearch.each(function () {
              inputHaveValue($(this));
              if ($(this).val()) {
                  var divInput = inputSearch.parent().parent();
                  divInput.append(delIcon);
                  bindOnClikIcone(delIcon, $(this));
              } else {
                  delIcon.remove();
              }

              $(this).off('keyup').on('keyup', function () {
                  if ($(this).val()) {
                      inputHaveValue($(this));
                  } else {
                      formClickHandler($(this).attr('id'));
                  }
              });
          });
      }

      function getSelectedtermsAggSearchKey(attrAgg, value) {
        return attrAgg.replace("[]", "-terms[]") + value;
      }

      /**
       * Checks the element
       * @param obj_span
       * @param delayChecked - used for elements with no server-side clones
       */
      function checkthebox(obj_span, delayChecked) {
        obj_span.removeClass("unchecked");
        obj_span.addClass("checked");
        obj_span.data('delayChecked', delayChecked ? true : undefined);
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

      function getQueryFromUrl() {
        var messageError = '<div class="alert alert-block alert-warning">' +
          '<a class="close" data-dismiss="alert" href="#">×</a>' +
          '<h3 class="element-invisible">Warning message</h3> ' + Drupal.settings.ErrorMessage +
          ' </div>';
        var qs = window.location.search.length === 0 ?  window.location.hash.replace(/^#!/, '') :
          window.location.search.replace(/^\?/, '');
        var jsonParam = (qs.split("&")
            .map(
            function (n) {
              return n = n.split("="), this[n[0]] = n[1], this
            }.bind({}))[0]
        )['query'];

        //if not valid jsonParam (url manually tampered by user) the scrip crash MK-201
        if (jsonParam === undefined || jsonParam === '') {
            return {};
        }

        try {
          return JSON.parse(decodeURIComponent(jsonParam));
        } catch (e) {
          $(".region-content").before(messageError);
          setTimeout(function () {
            updateWindowLocation();
          }, 2000);

          return {};
        }
      }

      function updateQueryOperation(operationMoniker, value) {
        // console.log("Moniker", operationMoniker, value);
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
        $.each(element.data(), function (att, value) {
          if (value) {
            dataArr.push({'name': att, 'value': value});
          }
        });
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

            if ($(this).hasClass("unchecked") || $(this).data('delayChecked')) {
              $(this).parents("label.span-checkbox").css("display", "inline");
              $(this).parents("label.span-checkbox").removeClass();

              checkthebox($(this));

              var checkbox = $(this).parents("li.facets");
              $("input[id=" + getAggregationMoniker(this) + "]").val($(this).attr('value')).attr('data-value', $(this).attr("data-value"));
              checkbox.find('.terms_stat').width($current_width_percent);
              var divtofind = $(this).parents("section:first").find(".checkedterms:first");
              checkbox.appendTo(divtofind);
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
          var numbers = values[1].match(/\d+(?:\.\d*)?|\.\d+/g);
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
          checkthebox($(this), true);
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
        return false;
      }

      function updateJsonQuery(jsonQuery) {
        $.trimJson(jsonQuery);
        $.query_href.updateWindowLocation(JSON.stringify(jsonQuery));
      }

      function updateWindowLocation(jsonQuery) {
        var searchUrl = $.queryParamToJson();
        delete searchUrl['with-facets']; //only used when the query does not change
        delete searchUrl['page'];

        if (tabparam) {
          searchUrl.type = tabparam;
        }

        if ($.isEmptyObject(jsonQuery) || '{}' === jsonQuery) {
          delete searchUrl['query'];
        } else {
          searchUrl.query = jsonQuery;
        }

        window.location.hash = $.isEmptyObject(searchUrl) ? '' : '!' + decodeURIComponent($.param(searchUrl));
      }

      function initializeTabParam() {
        tabparam = '';
        var urlTabParam = $.urlParam('type');

        if (urlTabParam) {
          var div = $("div.search-result").find("div.tab-pane");
          div.removeClass("active");
          $("div#" + urlTabParam).addClass("active");
          $('#result-search a[href$="#' + urlTabParam + '"]').tab('show');
          tabparam = urlTabParam;
        }
      }

      function validateRangeValues(input) {
        var value = $(input).val();
        var matches = value &&value.match(/\[\s*(\d+(?:\.\d*)?|\.\d+)\s*to\s*(\d+(?:\.\d*)?|\.\d+)\s*\]/);

        if (matches) {
          var id = $(input).attr("id");
          var minid = id + '-min';
          var maxid = id + '-max';
          var minvalue = $("input[term='" + minid + "']").attr("placeholder");
          var maxvalue = $("input[term='" + maxid + "']").attr('placeholder');

          if (matches[1].length === 0) {
            matches[1] = minvalue;
          }
          if (matches[2].length === 0) {
            matches[2] = maxvalue;
          }

          $(input).val(id + '.[ ' + matches[1] + ' to ' + matches[2] + ' ]');
        }
      }

      function formClickHandler(aggregation) {
        var json = getQueryFromUrl();
        var input = $("input[id='" + aggregation + "']");

        if (input.val()) {
          if ($(input).attr('name').match(/:range:/)) {
            validateRangeValues(input);
          }

          $.query_serializer.addItem( //
            json, //
            decodeURIComponent(serializeElement(input)) //
          );
        }
        else {
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
        $("section#block-obiba-mica-search-facet-search").find("h2:first").css("display", "none");

        var selectedVars = getUrlVars();

        if (selectedVars) {
          processMatchesInput(selectedVars);
          processTermsAggregationInputs(selectedVars);
          processRangeAggregationInputs(selectedVars);
        }

        $("span#checkthebox", context).off('click').on('click', updateCheckboxes);

        $("span#checkthebox", context).off('mouseover').on('mouseover', function () {
          if ($(this).hasClass("checked")) {
            rollover($(this));
            return false;
          }
        });

        $("span#checkthebox", context).off('mouseout').on('mouseout', function () {
          if ($(this).hasClass("checked")) {
            rollout($(this));
            return false;
          }
        });

        /*send request search on checking the box or on click go button */
        $("div#checkthebox, button#facet-search-submit", context).off('click').on('click', function () {
          formClickHandler($(this).attr('aggregation'));
        });

        $("input[id='range-auto-fill']", context).off('blur').on('blur', function () {
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

      function inputHaveValue(inputSearch) {
        var divInput = inputSearch.parent().parent();
        if (inputSearch.val()) {
          divInput.append(delIcon);
          bindOnClikIcone(delIcon, inputSearch);
        }
        else {
          delIcon.remove();
        }
      }

      function bindOnClikIcone(icon, inputSearch) {
        icon.off('click').on("click", function () {
          inputSearch.val('');
          formClickHandler(inputSearch.attr('id'));
        });
      }

      function populateFacetTabs(facetsHtml) {
        var sections = $('#search-facets').find('section');
        var temp = $('<div></div>').html(facetsHtml);

        $('#search-facets').addClass('hide');
        $.each($('div.panel-title>a', temp), function (i, anchor) {
          var newText = $('span', anchor).text();
          $('a[href="' + $(anchor).attr('href') + '"]', document).find('span').text(newText);
        });

        if (!Drupal.settings.ShowStudiesFacets) {
          if (Drupal.settings.ConfigTaxonomiesCount === 1) {
            $('#search-facets #facet-search').remove();
          } else {
            // Removme study related facet TAB and content
            $('#study-facet').remove();
            $('li>a[href="#study-facet"]').remove();
            $('li>a[href="#variable-facet"]').remove();
          }

          $('#variable-facet').addClass('active');
        }

        if (sections.length) {  //This is a workaround to avoid blinking collapsed section
          var selectedVars = getUrlVars();
          sections.each(function () {
            var section = $(this);
            var termsBlockTitles = section.find('.block-titles > a');
            var termsBlock = section.find('.block-content');
            var newTermsBlockTitle = temp.find('#' + section.attr('id') + ' .block-titles > a').text();
            var newTermsBlock = temp.find('#' + section.attr('id') + ' .block-content');

            section.find('.checkedterms li.facets') .each(function() {
              // upon the server response, especially when there are no data returned, elements that were checked or
              // unchecked must get cleaned up

              var span = $(this).find('span#checkthebox');
              var data_value = span.data('value');
              var unchecked = span.hasClass('unchecked');

              if (newTermsBlock.length > 0) {
                if (newTermsBlock.find('span#checkthebox[data-value="' + data_value + '"]').length > 0) {
                  // server has provided a clone of this element, remove it from the previous checked elements
                  $(this).remove();
                }
              } else {
                // there is no corresponding element from the server, reparent the element that was unchecked either
                // via the facets search UI or the query renderer (will be missing from url query)
                var selectedVar =
                  selectedVars && selectedVars[getSelectedtermsAggSearchKey(span.attr('aggregation'), data_value)];

                if (unchecked || !selectedVar) {
                  $(this).appendTo($('form[id="'+$(this).data('formId')+'"]'));
                }
              }
            });

            if (newTermsBlockTitle.length > 0) {
              $(termsBlockTitles[0]).text(newTermsBlockTitle);
              $(termsBlock[0]).html(newTermsBlock.html());
            }
          });
        } else { //first page load does not have facet sections
          $('#search-facets')
            .find('#variable-facet')
            .html(temp.find('#variable-facet').html());

          if (Drupal.settings.ShowStudiesFacets) {
            // add study related facet TAB and content
            $('#search-facets')
              .find('#study-facet')
              .html(temp.find('#study-facet').html());
          }
        }

        $('#search-facets').removeClass('hide');
      }

      function cleanupPagingState() {
        try {
          for(var k in localStorage) {
            if (k.startsWith('page_')) {
              localStorage.removeItem(k);
            }
          }
        } catch (e) {
          //ignore
        }
      }

      function loadCoverageTaxonomies(url, taxonomies) {
        if (taxonomies.length) {
          $.ajax({
            url: url + '&taxonomy=' + taxonomies[0],
            success: function (data) {
              var e = $('<div>').html(data.coverageTaxonomyResult);
              $('#coverages').append(e);
              taxonomies.splice(0, 1);
              loadCoverageTaxonomies(url, taxonomies);
            }
          });
        }
      }

      function loadSearchResult(url, forceFacets) {
        $('#block-system-main').fadeTo(300, 0.5);
        var url = url.replace(/^!/, '');

        if (forceFacets) {
          url = url.replace(/with-facets=false/, '');
        }

        if (url.indexOf('with-facets') < 0) {
          cleanupPagingState();
        }

        url = '?' + url;

        $.ajax({
          url: url,
          success: function (data) {
            var searchType = $.getParameterByName(url, 'type'),
              searchPage = $.getParameterByName(url, 'page');

            if ( searchType!== '' &&  searchPage!== '') {
              $.setState('page_' + searchType, searchPage);
            }

            $('#block-system-main>.block-content').html(data.searchResult);


            if(data.aggsDictionary) {
              Drupal.settings.aggs_dictionary = !Drupal.settings.aggs_dictionary.length ? {} : Drupal.settings.aggs_dictionary;
              $.extend(Drupal.settings.aggs_dictionary, data.aggsDictionary);
            }

            if(data.facets) {
              populateFacetTabs(data.facets);
            }

            Drupal.attachBehaviors($('div.main-container.container')[0], settings);

            if (updateCollapsibleUI) {
              Drupal.behaviors.obiba_mica_facet_search_collapse_block.updateUI(context, Drupal.settings);
              updateCollapsibleUI = false // do this only once the page is loaded to preserve the collapsible UI state
            }

            $('html, body').animate({scrollTop: 0}, 'fast');

            if (data.coverageTaxonomies) {
              loadCoverageTaxonomies(url, data.coverageTaxonomies);
            }
          },
          complete : function () {
            $('div.tooltip').remove();
            $('#block-system-main').fadeTo(300, 1.0);
          }
        });
      }

      if(!isAjax) { //events attached when page is first loaded
        $(window).bind('hashchange', function () {
          loadSearchResult(window.location.hash.replace(/^#/, ''), false);
        });

        loadSearchResult(window.location.hash.replace(/^#/, ''), true);
      }

      $('form[id^=facet-search-query-form]', context).off('submit').on('submit', function (e) {
        e.preventDefault();
        var el = $(this).find('input[id*="matches:facet-search-query"]')[0];
        formClickHandler($(el).attr('id'));
      });

      $('#search-result .pagination a', context).off('click').on('click', function(e) {
         e.preventDefault();
         var url = '!' + $(this).attr('href').split('?')[1];

        if ($.getParameterByName(url, 'with-facets') !== 'false') {
          url += '&with-facets=false';
        }

         window.location.hash = url;
      });

      initSearchTerms();

      /**
       * Expose these methods to other JS files
       */
      $.extend({
        query_href: {
          updateJsonQuery: updateJsonQuery,
          updateWindowLocation: updateWindowLocation,
          updateQueryOperation: updateQueryOperation,
          getQueryFromUrl: getQueryFromUrl
        }
      });
    }
  }
})(jQuery);