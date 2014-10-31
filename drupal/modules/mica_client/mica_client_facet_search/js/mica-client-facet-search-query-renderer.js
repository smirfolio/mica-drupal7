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
    updateQuery(jsonQuery);
    updateWindowLocation($.isEmptyObject(jsonQuery) ? '' : JSON.stringify(jsonQuery));
  }

  /**
   * Recursively scans the query and removes empty elements
   * @param obj
   * @param parent
   * @param key
   */
  function updateQuery(obj, parent, key) {
    if (obj instanceof Array) {
      if (obj.length === 0) {
        delete parent[key];
      }
    } else if (obj instanceof Object) {
      if ($.isEmptyObject(obj)) {
        delete parent[key];
      }
    } else {
      return;
    }

    $.each(obj, function (k, v) {
      updateQuery(v, obj, k);
      if ($.isEmptyObject(obj) && parent) {
        delete parent[key];
      }
    })
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
    htmlMatchesElement.click(function () {
      delete jsonQuery[type]['matches'];
      update();
      return false;
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
    return $("<span class='clickable'></span>").append(and).append(or).click(function() {
      $('[id^=and-]', this).toggle();
      $('[id^=or-]', this).toggle();
      $.query_href.updateQueryOperation(moniker, toggleOperation(operator));
      return false;
    });
  }

  function toggleOperation(op) {
    return OR_OPERATOR === op ? AND_OPERATOR : OR_OPERATOR;
  }

  function renderAggregate(type, typeValues, aggType, name) {
    var aggregate = $("<span class='aggregate'></span>").text(translateAggregation(name)).click(function () {
      delete jsonQuery[type][aggType][name];
      update();
      return false;
    });

    var htmlAggregate = $("<li></li>").append(aggregate);

    return htmlAggregate;
  }

  function renderTermsAggregationValue(value, hiddenParent) {
    var value = $("<span class='aggregate-value'></span>").text(value);
    return hiddenParent === null ? value : hiddenParent.append(value);
  }

  function renderRangeAggregationValue(value, hiddenParent) {
    var value = $("<span class='aggregate-value'></span>").text(value.min + " - " + value.max);
    return hiddenParent === null ? value : hiddenParent.append(value);
  }

  function renderAggregateValue(aggType, agg, i, value, valuesContaier, hiddenValuesContainer) {
    if (i > 0 && i < MAX_VIISBLE_AGG_VALUE) valuesContaier.append(renderComma());

    valuesContaier.append(aggType === "terms" //
        ? renderTermsAggregationValue(value, hiddenValuesContainer) //
        : renderRangeAggregationValue(value, hiddenValuesContainer)); //

    valuesContaier.click(function () {
      agg.values.splice(i, 1);
      if (agg.values.length === 0) delete agg['op'];
      update();
      return false;
    });
  }

  function getOperation(op) {
    if ('and' === op || 'or' === op) return op;
    return AND_OPERATOR;
  }

  function renderPlusMinus(parent) {
    var hiddens = $("<span hidden id='hidden-values'></span>");
    var plusMinus = $("<span> + </span>").append(hiddens).click(function() {
      $(this).text($(this).text() === ' + ' ? ' - ' : ' + ');
      $('[id^=hidden-values]').toggle();
      return false;
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
          if (agg.values.length > 0) {
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
      var qParam = $.query_href.getQueryFromUrl();
      if ($.isEmptyObject(qParam)) return;
      var view = //
        new $.QueryViewRenderer(Drupal.settings.mica_client_facet.facet_conf) //
          .render(JSON.parse(decodeURIComponent(qParam)));

      $('#search-query').append(view);
    }
  }
})(jQuery);

