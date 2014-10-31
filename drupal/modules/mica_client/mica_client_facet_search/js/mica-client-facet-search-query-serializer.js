(function ($) {
  Drupal.behaviors.query_serializer = {
    attach: function (context, settings) {
      /**
       * Desrializes the form JSON into an array of aggregation values. Only range agg values are formatted
       * @param json
       * @returns {Array}
       */
      function serializeJsonAsForm(json) {
        var formData = {};
        $.each(json, function (type, typeValues) {
          $.each(typeValues, function (aggType, aggs) {
            $.each(aggs, function (name, agg) {

              if (aggType === 'matches') {
                var key = type + "::matches:facet-search-query";
                formData[key] = aggs;
                return;
              }

              if (agg.values.length > 0) {
                formData[type + ":" + aggType + ":" + name + ":op"] = agg.op;
                $.each(agg.values, function (i, value) {
                  var formattedName = name + "-" + aggType + "[]";
                  var key = type + ":" + formattedName + (aggType === "terms" ? value : name);
                  formData[key] = aggType === "terms" ? value : name + ".[+" + value.min + "+to+" + value.max + "+]";
                });
              }

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
          var entry = /^(\w+):(.*)-(terms|range)[\\[\\]]*=(.*)$/.exec(value);
          return entry === null ? null : {
            type: entry[1],
            agg: entry[2],
            aggType: entry[3],
            aggValue: extractAggValue(entry[4])
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
          var entry = /^(\w+)::matches:(.*)=(.*)$/.exec(value);
          return entry === null ? null : {type: entry[1], matches: entry[2]};
        }

        /**
         * If the agg value has range info, return value as min-max
         * @param value
         * @returns {*}
         */
        function extractAggValue(value) {
          var entry = /\[\+([+-]*\d+)\+to\+([+-]*\d+)\+\]/.exec(value);
          if (entry !== null) return {min: entry[1], max: entry[2]};
          return value;
        }

        /**
         * Parses the formData serialized as a DOM object and returns it as JSON object
         * @param formData
         * @returns {{}}
         */
        function parse(formData) {
          var jsonForm = {};

          $.each(decodeURIComponent(formData).split('&'), function (i, value) {
            if (value != null && value.length > 0) {
              var entry = extractOperator(value) || extractFormEntry(value) || extractMatchesEntry(value);
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
                jsonForm[entry.type][entry.aggType][entry.agg] = {'values': [], 'op': 'and'};
              }

              if (entry.hasOwnProperty('op')) {
                jsonForm[entry.type][entry.aggType][entry.agg].op = entry.op;
              } else {
                jsonForm[entry.type][entry.aggType][entry.agg].values.push(entry.aggValue);
              }

            }
          });

          return jsonForm;
        }

        return parse(formData);
      }

      function updateOperator(moniker) {

      }

      $.extend({
        query_serializer: {
          serializeFormAsJson: serializeFormAsJson,
          serializeJsonAsForm: serializeJsonAsForm,
          serializeOperator: updateOperator
        }
      });

    }
  }

}(jQuery));