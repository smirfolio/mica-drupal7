(function ($) {

  "use strict";

  var container;
  var jsonQuery;
  var translation;

  var AND_OPERATOR = 'and';
  var OR_OPERATOR = 'or';
  var MAX_VIISBLE_AGG_VALUE = 3;

  /**
   * Constructor
   * @constructor
   */
  $.QueryViewRenderer = function (translationMap) {
    container = $("<ul class='facet-query-list'></ul>");
    translation = translationMap;
  };

  /**
   * renders a query view based on selected aggregations
   * @type {{render: render}}
   */
  $.QueryViewRenderer.prototype = {
    render: function (json) {
      jsonQuery = json;
      return parseAndRender();
    }
  };


  /**
   * Updates the query and url
   */
  function update() {
    $.trimJson(jsonQuery);
    updateWindowLocation($.isEmptyObject(jsonQuery) ? '' : JSON.stringify(jsonQuery));
  }

  function updateWindowLocation(query) {
    window.location.search = //
      window.location.search.replace(/([&]*query=)[^&]*([&]*)/g, query.length === 0 ? '' : "$1" + query + "$2");
  }

  function renderRefresh() {
    return $("<li><button type='button' class='refresh-button'><i class='flaticon-undo9'></i></button></li>")
      .on("click", function () {
        updateWindowLocation('');
      });
  }

  function renderMatches(type, value) {
     var matches = renderMatchesElement('matches', type, translate(type));
     var matchesValue = renderValuesContainer().append(renderMatchesElement('matches-value', type, value));
    container.append(matches.append(renderMatch()).append(matchesValue));
  }

  function renderMatchesElement(cssClass, type, text) {
    var htmlMatchesElement = $("<li></li>").append($("<span class='"+cssClass+"'></span>").text(text));
    htmlMatchesElement.click(function (e) {
      delete jsonQuery[type]['matches'];
      update();
      e.stopPropagation();
    });

    return htmlMatchesElement;
  }

  function renderMatch() {
    return $("<span class='match'>"+translate('match')+"</span>");
  }


  function renderValuesContainer() {
    return $("<ul class='facet-query-list'></ul>");
  }

  function leftParenthesis() {
    return $("<span class='unclickable'>(</span>");
  }

  function rightParenthesis(content) {
    return $("<span class='unclickable'>)</span>");
  }

  function renderComma() {
    return $("<span class='comma'>,</span>");
  }

  function createOpMoniker(type, aggType, name) {
    return type + ":" + aggType + ":" + name;
  }

  function renderIn() {
    return $("<span>in</span>")
  }

  function renderAggregationContainer(type, typeValues, aggType, name, op) {
    var aggContainer = renderAggregate(type, typeValues, aggType, name);
    var aggValueContainer = renderValuesContainer();
    aggContainer.append(renderAndOrOperation(op, createOpMoniker(type, aggType, name)))
      .append(leftParenthesis()).append(aggValueContainer).append(rightParenthesis());

    container.append(aggContainer);

    return aggValueContainer;
  }

  function renderOrOperation(show, moniker) {
    return $("<span data-op='or' id='or-" + moniker + "' " + (show ? "" : "hidden") + "  class='or-operation'>"+translate('or').toUpperCase()+"</span>");
  }

  function renderAndOperation(show, moniker) {
    return $("<span data-op='and' id='and-" + moniker + "' " + (show ? "" : "hidden") + "  class='and-operation'>"+translate('and').toUpperCase()+"</span>");
  }

  function renderAndOrOperation(operator, moniker) {

    var and = renderAndOperation(operator == AND_OPERATOR);
    var or = renderOrOperation(operator == OR_OPERATOR, moniker);
    return $("<span class='clickable'></span>").append(and).append(or).click(function(e) {
      $('[id^=and-]', this).toggle();
      $('[id^=or-]', this).toggle();
      $.query_href.updateQueryOperation(moniker, toggleOperation(operator));
      e.stopPropagation();
    });
  }

  function toggleOperation(op) {
    return OR_OPERATOR === op ? AND_OPERATOR : OR_OPERATOR;
  }

  function renderAggregate(type, typeValues, aggType, name) {
    var aggregate = $("<span class='aggregate'></span>").text(translateAggregation(name)).click(function (e) {
      delete jsonQuery[type][aggType][name];
      update();
      e.stopPropagation();
    });

    var htmlAggregate = $("<li></li>").append(aggregate);

    return htmlAggregate;
  }

  function renderTermsAggregationValue(value) {
    return $("<span class='aggregate-value'></span>").text(value);
  }

  function renderRangeAggregationValue(value) {
    return $("<span class='aggregate-value'></span>").text(value.min + " - " + value.max);
  }

  function renderAggregateValue(aggType, agg, i, value, valuesContaier, hiddenValuesContainer) {
    if (i > 0 && i < MAX_VIISBLE_AGG_VALUE) valuesContaier.append(renderComma());

    var htmlValue =
      aggType === "terms" //
          ? renderTermsAggregationValue(value) //
          : renderRangeAggregationValue(value); //

    htmlValue.click(function (e) {
      agg.values.splice(i, 1);
      if (agg.values.length === 0) delete agg['op'];
      update();
      e.stopPropagation();
    });

    valuesContaier.append(hiddenValuesContainer === null ? htmlValue : hiddenValuesContainer.append(htmlValue));
  }

  function getOperation(op) {
    if ('and' === op || 'or' === op) return op;
    return AND_OPERATOR;
  }

  function renderPlusMinus(parent) {
    var hiddens = $("<span hidden class='no-text-decoration' id='hidden-values'></span>");
    var plusMinus = $("<span class='plus-minus glyphicon glyphicon-plus'></span>").append(hiddens)
      .click(function(e) {
        if ($(this).hasClass('glyphicon-plus')) {
          $(this).removeClass('glyphicon-plus').addClass('glyphicon-minus');
        } else {
          $(this).removeClass('glyphicon-minus').addClass('glyphicon-plus');
        }

        $('[id^=hidden-values]').toggle();
        e.stopPropagation();
    });

    parent.append(plusMinus.append(hiddens));
    return hiddens;
  }

  function getHiddenAttribute(hide) {
    return hide ? "hidden" : "";
  }

  function translate(key) {
    return translation.general[key];
  }

  function translateAggregation(key) {
    var result = key;
    $.each(translation, function (i, v) {
      $.each(v, function (j, o) {
        if (o.aggs === key) {
          result = o.title.replace(/[^-]+-/, '');
          return false;
        }
      });
    });

    return result;
  }

  function parseAndRender() {
    container.append(renderRefresh());
    $.each(jsonQuery, function (type, typeValues) {
      $.each(typeValues, function (aggType, aggs) {

        if (aggType === 'matches') {
          if (container.children().length > 1) container.append(renderAndOperation(true, ""));
          renderMatches(type, aggs);
          return;
        }

        $.each(aggs, function (name, agg) {
          if (!$.isEmptyObject(agg.values) && agg.values.length > 0) {
            var aggValueContainer = renderAggregationContainer(type, typeValues, aggType, name, getOperation(agg.op));
            var valuesContainer = $("<li></li>");
            var hiddenValuesContainer = null;
            $(aggValueContainer).append(valuesContainer);


            $.each(agg.values, function (i, value) {
              if (i >= MAX_VIISBLE_AGG_VALUE && hiddenValuesContainer === null) {
                hiddenValuesContainer = renderPlusMinus(valuesContainer);
                valuesContainer.append(hiddenValuesContainer);
              }

              renderAggregateValue(aggType, //
                agg, //
                i, //
                value, //
                valuesContainer, //
                hiddenValuesContainer); //
            });
          }
        })
      });
    });

    return container;
  }

}(jQuery));

/**
 * client-server bridge
 */
(function ($) {

  Drupal.behaviors.query_builder = {
    attach: function (context, settings) {
      var jsonQuery = $.query_href.getQueryFromUrl();
      if ($.isEmptyObject(jsonQuery)) return;
      var view = //
        new $.QueryViewRenderer(Drupal.settings.mica_client_facet.facet_conf) //
          .render(jsonQuery);

      $('#search-query').append(view);
    }
  }
})(jQuery);

