/**
 * @file
 * JScript code for query builder serializing
 */

(function ($) {
  Drupal.behaviors.query_serializer = {
    attach: function (context, settings) {
      /**
       * Desrializes the form JSON into an array of aggregation values. Only range agg values are formatted
       * @param json
       * @returns {Array}
       */
      function serializeJsonAsForm(json) {
        function getName(aggType, name) {
          return (aggType === 'terms' ? name + "-" + aggType : name) + "[]";
        }

        function getKey(type, aggType, name, value) {
          return type + ":" + (aggType === 'terms' ? name + value : aggType + ":" + name);
        }

        var formData = {};
        $.each(json, function (type, typeValues) {
          $.each(typeValues, function (aggType, aggs) {

            if (aggType === 'matches') {
              var key = type + ":matches:facet-search-query";
              formData[key] = aggs;
              return;
            }

            $.each(aggs, function (name, agg) {

              if (!$.isEmptyObject(agg.values) && agg.values.length > 0) {
                formData[type + ":" + aggType + ":" + name + ":op"] = agg.op;
                $.each(agg.values, function (i, value) {
                  var formattedName = getName(aggType, name);
                  var key = getKey(type, aggType, formattedName, value);
                  formData[key] = aggType === "terms" ? value : name + ".[+" + value.min + "+to+" + value.max + "+]";
                });
              }

            })
          });
        });

        return $.isEmptyObject(formData) ? null : formData;
      }

      /**
       * Helper used to extract entry information needed to build the form JSON
       * @param value
       * @returns {{type: *, agg: *, aggType: *, aggValue: *}}
       */
      function extractTermsFormEntry(value) {
        var entry = /^(\w+):(terms|range):(.*)[\\[\\]]*=(.*)&value=(.*)$/.exec(value);
        return entry === null ? null : {
          type: entry[1],
          aggType: entry[2],
          agg: entry[3],
          aggValue: entry[4],
          aggDataValue: extractAggValue(entry[5])
        };
      }

      /**
       * Helper used to extract entry information needed to build the form JSON
       * @param value
       * @returns {{type: *, agg: *, aggType: *, aggValue: *}}
       */
      function extractFormEntry(value) {
        var entry;

        if (/:terms:/.exec(value)) {
          return extractTermsFormEntry(value);
        }
        var entry = /^(\w+):(terms|range):(.*)[\\[\\]]*=(.*)$/.exec(value);
        return entry === null ? null : {
          type: entry[1],
          aggType: entry[2],
          agg: entry[3],
          aggValue: extractAggValue(entry[4]),
          aggDataValue: extractAggValue(entry[4])
        };
      }

      /**
       * Helper used to extract entry information needed to build the form JSON
       * @param value
       * @returns {{type: *, agg: *, aggType: *, aggValue: *}}
       */
      function extractOperator(value) {
        var entry = /^(\w+):(\w+):(.*):op=(and|or)$/.exec(value);
        return entry === null ? null : {
          type: entry[1],
          aggType: entry[2],
          agg: entry[3],
          op: entry[4]
        };
      }

      /**
       * Helper used to extract query string 'matches' value
       * @param value
       * @returns {{matches: *}}
       */
      function extractMatchesEntry(value) {
        var entry = /^(\w+):matches:facet-search-query=([^&]*)/.exec(value);
        return entry === null ? null : {type: entry[1], matches: entry[2]};
      }

      /**
       * If the agg value has range info, return value as min-max
       * @param value
       * @returns {*}
       */
      function extractAggValue(value) {
        var entry = /\[\+([+-]?(?:\d+(?:\.\d*)?|\.\d+))\+to\+([+-]?(?:\d+(?:\.\d*)?|\.\d+))\+\]/.exec(value);
        if (entry !== null) return {min: entry[1], max: entry[2]};
        return value;
      }

      function addItem(jsonForm, entry) {

        /**
         * Parses the formData serialized as a DOM object and returns it as JSON object
         * @param formData
         * @returns {{}}
         */
        function parse(jsonForm, item) {
          if (!jsonForm) jsonForm = {};
          if (item != null && item.length > 0) {
            var entry = extractOperator(item) || extractFormEntry(item) || extractMatchesEntry(item);
            if (entry === null) return;

            if (!jsonForm.hasOwnProperty(entry.type)) {
              jsonForm[entry.type] = {};
            }

            if (entry.hasOwnProperty('matches')) {
              jsonForm[entry.type]['matches'] = entry.matches;
              return;
            }

            if (!jsonForm[entry.type].hasOwnProperty(entry.aggType)) {
              jsonForm[entry.type][entry.aggType] = {};
            }

            if (!jsonForm[entry.type][entry.aggType].hasOwnProperty(entry.agg)) {
              jsonForm[entry.type][entry.aggType][entry.agg] = {'values': [], 'op': 'or'};
            }

            if (entry.hasOwnProperty('op')) {
              jsonForm[entry.type][entry.aggType][entry.agg].op = entry.op;
            } else {
              if (entry.aggType == 'range' && jsonForm[entry.type][entry.aggType][entry.agg].values.length > 0) {
                jsonForm[entry.type][entry.aggType][entry.agg].values.splice(0, 1);
              }
              jsonForm[entry.type][entry.aggType][entry.agg].values.push(entry.aggDataValue);
            }
          }
        }

        return parse(jsonForm, entry);
      }

      function removeItem(jsonForm, item) {
        if ($.isEmptyObject(jsonForm)) return;

        var entry = extractOperator(item) || extractFormEntry(item) || extractMatchesEntry(item);
        if (entry === null) return;

        $.each(jsonForm, function (type, typeValues) {
          if (type === entry.type) {
            $.each(typeValues, function (aggType, aggs) {
              if (aggType === 'matches' && entry.hasOwnProperty('matches') && aggType !== 'range') {
                delete typeValues[aggType];

                $.trimJson(jsonForm);
                return false;
              }

              if (aggType === entry.aggType) {
                $.each(aggs, function (name, agg) {
                  if (name === entry.agg) {

                    if (aggType === 'range') {
                      agg.values = [];
                    }
                    else {
                      agg.values = $.grep(agg.values, function (value) {
                        return entry.aggDataValue !== value
                      });
                    }
                    if (agg.values.length === 0) {
                      // do not keep incomplete agg object
                      delete agg['op'];
                    }

                    $.trimJson(jsonForm);
                    return false;
                  }
                });
              }
            });
          }
        });
      }

      $.extend({
        query_serializer: {
          serializeJsonAsForm: serializeJsonAsForm,
          addItem: addItem,
          removeItem: removeItem
        }
      });

    }
  }

}(jQuery));