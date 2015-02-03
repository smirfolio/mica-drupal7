/**
 * @file
 * JScript code for query builder parser
 */

(function ($) {

    "use strict";

    var container;
    var contentQuery;
    var contentReset;
    var jsonQuery;
    var translation;
    var termsDictionary;

    var AND_OPERATOR = 'and';
    var OR_OPERATOR = 'or';
    var MAX_VISIBLE_AGG_VALUE = 3;

    /**
     * Constructor
     * @constructor
     */
    $.QueryViewRenderer = function (translationMap, dictionary) {
        contentReset = $("<div class='facet-query-reset'></div>");
        contentQuery = $("<ul class='facet-query-list no-margin'></ul>");
        container = $("<table class='facet-query'></table>");
        var row = $("<tr></tr>");
        row.append($("<td></td>").css("vertical-align","top").append(contentReset));
        row.append($("<td></td>").append(contentQuery));
        container.append(row);
        translation = translationMap;
        termsDictionary = dictionary;
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
        $.query_href.updateJsonQuery(jsonQuery);
    }

    function renderReset() {
        return $("<button type='button' class='btn btn-warning' title='" + Drupal.t('Clear query') + "'><span class='flaticon-undo9'></span></button>")
            .on("click", function () {
                $.query_href.updateWindowLocation(null);
            });
    }

    function renderMatches(type, value) {
        var matches = renderMatchesElement('matches', type, translate(type));
        var matchesValue = renderMatchesElement('matches-value', type, value);

        var htmlContainer = $("<div class='aggregate'></div>");
        htmlContainer.append(matches).append(renderMatch()).append(matchesValue);
        return htmlContainer;
    }

    function renderMatchesElement(cssClass, type, text) {
        var htmlMatchesElement = $("<span class='" + cssClass + "' title='" + Drupal.t('Click to remove') + "'></span>").text(text);
        htmlMatchesElement.click(function (e) {
            delete jsonQuery[type]['matches'];
            update();
            e.stopPropagation();
        });

        return htmlMatchesElement;
    }

    function renderMatch() {
        return $("<span class='match'>" + translate('match') + "</span>");
    }


    function renderValuesContainer() {
        return $("<div class='facet-query-list no-margin'></div>");
    }

    function leftParenthesis() {
        return $("<span class='grouping-symbol'>(</span>");
    }

    function rightParenthesis() {
        return $("<span class='grouping-symbol'>)</span>");
    }

    function leftBracket() {
        return $("<span class='grouping-symbol'>[</span>");
    }

    function rightBracket() {
        return $("<span class='grouping-symbol'>]</span>");
    }

    function renderComma() {
        return $("<span class='comma'>,</span>");
    }

    function createTermsMoniker(type, name, value) {
        return type + ":" + name + ":" + value;
    }

    function createOpMoniker(type, aggType, name) {
        return type + ":" + aggType + ":" + name;
    }

    function renderIn() {
        return $("<span class='operation'>" + Drupal.t('in') + "</span>");
    }

    function renderAggregationContainer(type, typeValues, aggType, name, op, showOp, aggValueContainer) {
        var htmlContainer = $("<div></div>");
        var aggContainer = renderAggregate(type, typeValues, aggType, name);
        aggContainer
            .append(renderIn())
            .append(aggValueContainer);

        htmlContainer.append(aggContainer);
        if (!showOp) htmlContainer.append(renderAndOrOperation(op, createOpMoniker(type, aggType, name)));

        return htmlContainer;
    }

    function renderOrOperation(show, moniker) {
        var title = moniker ? "title='" + Drupal.t('Switch to AND') + "'" : "";
        return $("<span data-op='or' id='or-" + moniker + "' " + (show ? "" : "hidden") + "  class='or-operation' " + title + ">" + translate('or').toUpperCase() + "</span>");
    }

    function renderAndOperation(show, moniker) {
        var title = moniker ? "title='" + Drupal.t('Switch to OR') + "'" : "";
        var cls = moniker ? 'and-operation' : 'no-operation';
        return $("<span data-op='and' id='and-" + moniker + "' " + (show ? "" : "hidden") + "  class='" + cls + "' " + title + ">" + translate('and').toUpperCase() + "</span>");
    }

    function renderAndOrOperation(operator, moniker) {

        var and = renderAndOperation(operator == AND_OPERATOR, moniker);
        var or = renderOrOperation(operator == OR_OPERATOR, moniker);
        return $("<span class='clickable'></span>").append(and).append(or).click(function (e) {
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
        var aggregate = $("<span class='aggregate-field' title='" + Drupal.t('Click to remove') + "'></span>").text(translateAggregation(name)).click(function (e) {
            delete jsonQuery[type][aggType][name];
            update();
            e.stopPropagation();
        });

        var htmlAggregate = $("<div class='aggregate'></div>").append(aggregate);

        return htmlAggregate;
    }

    function renderTermsAggregationValue(value) {
        return $("<span class='aggregate-value' title='" + Drupal.t('Click to remove') + "'></span>").text(value);
    }

    function renderRangeAggregationValue(value) {
        return $("<span class='aggregate-value' title='" + Drupal.t('Click to remove') + "'></span>").text(value.min + " - " + value.max);
    }

    function renderAggregateValue(aggType, agg, i, value, valuesContainer, hiddenValuesContainer) {
        if (i > 0 && i < MAX_VISIBLE_AGG_VALUE) {
            valuesContainer.append(renderComma());
        } else if (i > MAX_VISIBLE_AGG_VALUE) {
            hiddenValuesContainer.append(renderComma());
        }

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

        valuesContainer.append(hiddenValuesContainer === null ? htmlValue : hiddenValuesContainer.append(htmlValue));
    }

    function getOperation(op) {
        if ('and' === op || 'or' === op) return op;
        return AND_OPERATOR;
    }

    function renderPlusMinus(parent) {
        var hiddens = $("<span hidden class='no-text-decoration' id='hidden-values'></span>");
        var plusMinus = $("<span class='plus-minus glyphicon glyphicon-plus'></span>").append(hiddens)
            .click(function (e) {
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
                    result = o.title;
                    return false;
                }
            });
        });

        return result;
    }

    function parseAndRender() {
        contentReset.append(renderReset());
        var prevType = null;

        var types = ['networks', 'studies', 'datasets', 'variables'];

        $.each(types, function (index, type) {
            var typeValues = jsonQuery[type];
            if (jsonQuery[type]) {
                var contentQueryItem = $('<li></li>');
                var typeContentQuery = parseAndRenderType(type, typeValues);
                if (prevType == null || prevType != type) {
                    if (prevType != null) {
                        contentQueryItem.append($("<div class='facet-query-conjunction'></div>").append(translate('and').toUpperCase()));
                    }
                    var where = $("<div class='facet-query-where'></div>");
                    where.append(type.charAt(0).toUpperCase() + type.slice(1)).append(' ').append(Drupal.t('where'));
                    contentQueryItem.append(where);
                }
                contentQueryItem.append(typeContentQuery);
                contentQuery.append(contentQueryItem);
                // save for line break
                prevType = type;
            }
        });

        return container;
    }

    function parseAndRenderType(type, typeValues) {
        var i = 0;
        var total = 0;
        var typeContentQuery = $("<div class='facet-query facet-query-" + type + "'></div>");

        $.each(typeValues, function (aggType, aggs) {
            if (aggType !== 'matches') {
                total += Object.keys(typeValues[aggType]).length;
            }
        });

        $.each(typeValues, function (aggType, aggs) {
            if (aggType !== 'matches') {
                var last = total - 1;


                $.each(aggs, function (name, agg) {
                    if (!$.isEmptyObject(agg.values) && agg.values.length > 0) {

                        var aggValueContainer = renderValuesContainer();
                        var valuesContainer = $("<span></span>");
                        $(aggValueContainer).append(valuesContainer);

                        typeContentQuery.append(renderAggregationContainer(type, typeValues, aggType, name, getOperation(agg.op), i === last, aggValueContainer));

                        var hiddenValuesContainer = null;
                        $.each(agg.values, function (i, value) {
                            var caption = termsDictionary[createTermsMoniker(type, name, value)] || value;
                            if (i >= MAX_VISIBLE_AGG_VALUE && hiddenValuesContainer === null) {
                                hiddenValuesContainer = renderPlusMinus(valuesContainer);
                                valuesContainer.append(hiddenValuesContainer);
                            }

                            renderAggregateValue(aggType, //
                                agg, //
                                i, //
                                $.type(caption) === "string" ? caption.replace(/\+/g, ' ') : caption, //
                                valuesContainer, //
                                hiddenValuesContainer); //
                        });
                    }

                    i++;
                });
            }
        });

        $.each(typeValues, function (aggType, aggs) {
            if (aggType === 'matches') {
                var opAdded = false;
                if (typeContentQuery.children().length > 0) {
                    typeContentQuery.append(renderAndOperation(true, ""));
                    opAdded = true;
                }
                typeContentQuery.append(renderMatches(type, aggs.replace(/\+/g, ' ')));
                if (!opAdded && total > 0) {
                    typeContentQuery.append(renderAndOperation(true, ""));
                }

            }
        });

        return typeContentQuery;
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

      var view = new $.QueryViewRenderer(
        Drupal.settings.obiba_mica_facet.facet_conf, Drupal.settings.terms_dictionary).render(jsonQuery);

      $('#search-query').append(view);
      $('#search-help').hide();
    }
  };
})(jQuery);

