(function ($) {

  "use strict";

  var container;
  var jsonQuery;
  var translation;

  var AND_OPERATOR = 'and';
  var OR_OPERATOR = 'or';

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

  function parenthesize(content) {
    return $("<span style='display: inline-block'></span>").append("<span class='is-a'>(</span>").append(content).append("<span class='is-a'>)</span>");
  }

  function renderComma() {
    return $("<span class='is-a'>,</span>");
  }

  function renderIsA() {
    return $("<span class='is-a'>"+translate('is')+"</span>");
  }

  function createOpMoniker(type, aggType, name) {
    return type + ":" + aggType + ":" + name;
  }

  function renderAggregationContainer(type, typeValues, aggType, name, op) {
    var aggContainer = renderAggregate(type, typeValues, aggType, name);
    var aggValueContainer = renderValuesContainer();
    aggContainer.append(renderAndOrOperation(op, createOpMoniker(type, aggType, name))).append(parenthesize(aggValueContainer));

    //if (container.children().length > 1) {
    //  container.append(renderAndOrOperation(op, createOpMoniker(type, aggType, name)));
    //}
    container.append(aggContainer);

    return aggValueContainer;
  }

  function renderAggOrOperation() {
    return $("<span class='agg-or-operation'>"+translate('or')+"</span>");
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
    var htmlAggregate = $("<li></li>").append($("<span class='aggregate'></span>").text(translateAggregation(name)));
    htmlAggregate.click(function () {
      delete jsonQuery[type][aggType][name];
      update();
      return false;
    });

    return htmlAggregate;
  }

  function renderTermsAggregationValue(value) {
    return $("<span class='aggregate-value'></span>").text(value);
  }

  function renderRangeAggregationValue(value) {
    return $("<span class='aggregate-value'></span>").text(value.min + " - " + value.max);
  }

  function renderAggregateValue(aggType, values, i, value) {
    var id = aggType + i + value;
    var htmlValue = $("<li></li>");
    if (i > 0) htmlValue.append(renderComma());

    htmlValue.append(aggType === "terms" ? renderTermsAggregationValue(value) : renderRangeAggregationValue(value));
    htmlValue.click(function () {
      values.splice(i, 1);
      update();
      return false;
    });

    return htmlValue;
  }

  function getOperation(op) {
    if ('and' === op || 'or' === op) return op;
    return AND_OPERATOR;
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
            $.each(agg.values, function (i, value) {
              $(aggValueContainer).append(renderAggregateValue(aggType, agg.values, i, value));
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

